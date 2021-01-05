#include "hwlib.hpp"

namespace hwlib {
    
// learn.sparkfun.com/tutorials/rgb-panel-hookup-guide
// https://bikerglen.com/projects/lighting/led-panel-1up/
// https://docs.pixelmatix.com/SmartMatrix/shieldref.html

class led_panel : public window, public background {
    color buffer[ 64 ][ 32 ];
    int row = 0;
    
    port_out & rgb0;
    port_out & rgb1;
    port_out & abcd;
    
    pin_out & clk;
    pin_out & stb;
    pin_out & oe;
    
    uint_fast64_t next_run;
    
public:

   led_panel(
      port_out & rgb0,
      port_out & rgb1,
      port_out & abcd,
    
      pin_out & clk,
      pin_out & stb,
      pin_out & oe
   ):
      window( xy( 64, 32 ) ),
      rgb0( rgb0 ), rgb1( rgb1 ), abcd( abcd ),
      clk( clk ), stb( stb ), oe( oe ),
      next_run( hwlib::now_us() )
   {
             
   }
   
   void write_implementation( xy pos, color col ) override {
       buffer[ pos.x ][ pos.y ] = col;
   }
   
   void flush() override {}
           
   
   static uint8_t rgb_bits( const color c ){
      return 
           (( c.red   > 127 ) ? 0b0001 : 0b0000 )
         | (( c.green > 127 ) ? 0b0010 : 0b0000 )
         | (( c.blue  > 127 ) ? 0b0100 : 0b0000 );
   }
   
   void work() override {
      if( hwlib::now_us() < next_run ){
         return;
      }       
      next_run += 1'000;
       
      static int p = 0;
      p = ( p + 1 ) % 16;
      
      for( int i = 0; i < 64; ++i ){
         clk.write( 0 );
         clk.flush();
         
         rgb0.write( rgb_bits( buffer[ i ][ p ] )); 
         rgb1.write( rgb_bits( buffer[ i ][ 16 + p ] )); 
         rgb0.flush();
         rgb1.flush();
           
         clk.write( 1 );
         clk.flush();
         //hwlib::wait_us( 1 );
         
      }
      
      oe.write( 1 );
      //hwlib::wait_us( 1 );
      
      abcd.write( p );
      abcd.flush();
      
      stb.write( 1 );
      //hwlib::wait_us( 1 );
      stb.write( 0 );
      
      //hwlib::wait_us( 1 );
      oe.write( 0 );
   
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
   
   auto r0   = hwlib::target::pin_out{ hwlib::target::pins::d23 };
   auto b0   = hwlib::target::pin_out{ hwlib::target::pins::d25 };
   auto r1   = hwlib::target::pin_out{ hwlib::target::pins::d27 };    
   auto b1   = hwlib::target::pin_out{ hwlib::target::pins::d29 };    
   auto a    = hwlib::target::pin_out{ hwlib::target::pins::d31 };    
   auto c    = hwlib::target::pin_out{ hwlib::target::pins::d33 };    
   auto clk  = hwlib::target::pin_out{ hwlib::target::pins::d35 };
   auto oe   = hwlib::target::pin_out{ hwlib::target::pins::d37 };    
   
   auto g0   = hwlib::target::pin_out{ hwlib::target::pins::d22 };    
   // gnd
   auto g1   = hwlib::target::pin_out{ hwlib::target::pins::d26 };
   // gnd
   auto b    = hwlib::target::pin_out{ hwlib::target::pins::d30 };
   auto d    = hwlib::target::pin_out{ hwlib::target::pins::d32 };    
   auto stb  = hwlib::target::pin_out{ hwlib::target::pins::d34 };    
   // gnd
   
   auto rgb0 = hwlib::port_out_from( r0, g0, b0 );
   auto rgb1 = hwlib::port_out_from( r1, g1, b1 );
   auto abcd = hwlib::port_out_from( a, b, c, d );
    
   auto w1 = hwlib::led_panel( rgb0, rgb1, abcd, clk, stb, oe );
   auto w = hwlib::window_with_frame( w1, 2, hwlib::blue );
   hwlib::graphics_random_lines( w, 30, hwlib::red );
   for(;;){
      led.write( 0 );       
      hwlib::wait_ms( 50 );
      led.write( 1 );
      hwlib::wait_ms( 50 );
   }
}   