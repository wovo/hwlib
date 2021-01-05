#include "hwlib.hpp"

namespace hwlib {
    
// https://saturn.ffzg.hr/rot13/index.cgi?action=display_html;page_name=hub_08_led_panel

template< int x_size, int y_size >
class led_panel_hub08 : public window, public background {
    bool buffer[ x_size ][ y_size ];
    int row = 0;
    
    port_out & leds;
    port_out & r;
    port_out & g;
    
    pin_out & lat;
    pin_out & clk;
    pin_out & en;
    
    uint_fast64_t next_run;
    
public:

   led_panel_hub08(
      port_out & leds,
      port_out & r,
      port_out & g,
    
      pin_out & lat,
      pin_out & clk,
      pin_out & en
   ):
      window( xy( x_size, y_size ) ),
      leds( leds ), r( r ), g( g ),
      lat( lat ), clk( clk ), en( en ),
      next_run( hwlib::now_us() )
   {
             
   }
   
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
         
         leds.write( buffer[ i ][ p ] ? 0xFF : 0x00 );
         leds.flush();
           
         clk.write( 1 );
         clk.flush();
         //hwlib::wait_us( 1 );
         
      }
      
      en.write( 1 );
      //hwlib::wait_us( 1 );
      
      g.write( p );
      g.flush();
      
      r.write( p );
      r.flush();
      
      lat.write( 1 );
      //hwlib::wait_us( 1 );
      lat.write( 0 );
      
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
    
   auto led   = hwlib::target::pin_out{ hwlib::target::pins::led };
   
   auto gnd1 = hwlib::target::pin_out{ hwlib::target::pins::d22 };
   auto gnd2 = hwlib::target::pin_out{ hwlib::target::pins::d24 };
   auto gnd3 = hwlib::target::pin_out{ hwlib::target::pins::d26 };    
   auto en   = hwlib::target::pin_out{ hwlib::target::pins::d28 };    
   auto r1   = hwlib::target::pin_out{ hwlib::target::pins::d30 };    
   auto r2   = hwlib::target::pin_out{ hwlib::target::pins::d32 };    
   auto gnd4 = hwlib::target::pin_out{ hwlib::target::pins::d34 };
   auto gnd5 = hwlib::target::pin_out{ hwlib::target::pins::d36 };    
   
   auto la   = hwlib::target::pin_out{ hwlib::target::pins::d23 };    
   auto lb   = hwlib::target::pin_out{ hwlib::target::pins::d25 };    
   auto lc   = hwlib::target::pin_out{ hwlib::target::pins::d27 };
   auto ld   = hwlib::target::pin_out{ hwlib::target::pins::d29 };    
   auto g1   = hwlib::target::pin_out{ hwlib::target::pins::d31 };
   auto g2   = hwlib::target::pin_out{ hwlib::target::pins::d33 };    
   auto lat  = hwlib::target::pin_out{ hwlib::target::pins::d35 };    
   auto clk  = hwlib::target::pin_out{ hwlib::target::pins::d37 };    
   
   auto leds = hwlib::port_out_from( la, lb, lc, ld );
   auto r    = hwlib::port_out_from( r1, r2 ); 
   auto g    = hwlib::port_out_from( g1, g2 );
   auto gnd  = hwlib::port_out_from( gnd1, gnd2, gnd3, gnd4, gnd5 );
   gnd.write( 0 ); gnd.flush();
    
   auto w = hwlib::led_panel_hub08< 64, 16 >( leds, r, g, lat, clk, en );
   hwlib::graphics_random_lines( w );
   for(;;){
      led.write( 0 );       
      hwlib::wait_ms( 50 );
      led.write( 1 );
      hwlib::wait_ms( 50 );
   }
}   