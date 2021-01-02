#include "hwlib.hpp"

namespace hwlib {
    
// https://saturn.ffzg.hr/rot13/index.cgi?action=display_html;page_name=hub_08_led_panel

template< int x_size, int y_size >
class led_panel_hub08 : public window, public background {
    bool buffer[ x_size ][ y_size ];
    int row = 0;
    
    port_out & abcd;
    port_out & rg;
    
    pin_out & clk;
    pin_out & sclk;
    pin_out & en;
    
    uint_fast64_t next_run;
    
    public:

// abcd, rg, clk, sclk, en );

   led_panel_hub08(
      port_out & abcd,
      port_out & rg,
    
      pin_out & clk,
      pin_out & sclk,
      pin_out & en
   ):
      window( xy( x_size, y_size ) ),
      abcd( abcd ), rg( rg ),
      clk( clk ), sclk( sclk ), en( en ),
      next_run( hwlib::now_us() )
   {}
   
   void write_implementation( xy pos, color col ) override {
       buffer[ pos.x ][ pos.y ] = ( col == hwlib::white );
   }
   
   void flush() override {}
   
   void work() override {
      if( hwlib::now_us() < next_run ){
         return;
      }       
      next_run += 500;
       
      static int p = 0;
      p = ( p + 1 ) % 4;
      
      for( int i = 0; i < x_size; ++i ){
         clk.write( 0 );
         clk.flush();
         
         rg.write( buffer[ i ][ p ] ? 0xFF : 0x00 );
         rg.write( 0xFF );
         rg.flush();
           
         clk.write( 1 );
         clk.flush();
         //hwlib::wait_us( 1 );
         
      }
      
      en.write( 1 );
      //hwlib::wait_us( 1 );
      
      abcd.write( p );
      abcd.flush();
      
      sclk.write( 1 );
      //hwlib::wait_us( 1 );
      sclk.write( 0 );
      
      //hwlib::wait_us( 1 );
      en.write( 0 );
   
   }

};

class window_with_frame : public window {
private:

   window & w;
   xy start;
   uint_fast8_t border;
   color( c );
   
   void write_implementation( xy pos, color col ) override {
      w.write( start + pos, col );
   }      

public:    

   window_with_frame( window & w, uint_fast8_t border = 1, const color & c = transparent ):
      window( w.size - 2 * xy( border, border ) ),
      w( w ),
      start( border, border ),
      border( border) ,
      c( c == transparent ? w.foreground : c )
   {}

   void flush() override {
      for( uint_fast8_t n = 0; n < border; ++n ){
         rectangle( 
            xy( 0, 0 ) + n * xy( 1, 1 ), 
            w.size - ( n + 1 ) * xy( 1, 1 ), c 
         ).draw( w );
      }
      w.flush();
   }  

};

};

int main( void ){
   
   auto oe   = hwlib::target::pin_out{ hwlib::target::pins::d22 };
   auto gnd1 = hwlib::target::pin_out{ hwlib::target::pins::d24 };
   auto gnd2 = hwlib::target::pin_out{ hwlib::target::pins::d26 };    
   auto gnd3 = hwlib::target::pin_out{ hwlib::target::pins::d28 };    
   auto gnd4 = hwlib::target::pin_out{ hwlib::target::pins::d30 };    
   auto gnd5 = hwlib::target::pin_out{ hwlib::target::pins::d32 };    
   auto gnd6 = hwlib::target::pin_out{ hwlib::target::pins::d34 };
   auto gnd7 = hwlib::target::pin_out{ hwlib::target::pins::d36 };    
   
   auto a    = hwlib::target::pin_out{ hwlib::target::pins::d23 };    
   auto b    = hwlib::target::pin_out{ hwlib::target::pins::d25 };    
   auto c    = hwlib::target::pin_out{ hwlib::target::pins::d27 };
   auto clk  = hwlib::target::pin_out{ hwlib::target::pins::d29 };    
   auto sclk = hwlib::target::pin_out{ hwlib::target::pins::d31 };
   auto r    = hwlib::target::pin_out{ hwlib::target::pins::d33 };    
   auto g    = hwlib::target::pin_out{ hwlib::target::pins::d35 };    
   auto d    = hwlib::target::pin_out{ hwlib::target::pins::d37 };    
   
   auto abcd = hwlib::port_out_from( a, b, c, d );
   auto rg   = hwlib::port_out_from( r, g ); 
   auto gnd  = hwlib::port_out_from( gnd1, gnd2, gnd3, gnd4, gnd5, gnd6, gnd7 );
   gnd.write( 0 ); gnd.flush();
    
   auto w = hwlib::led_panel_hub08< 64, 32 >( abcd, rg, clk, sclk, oe );
   hwlib::graphics_random_lines( w );
}   