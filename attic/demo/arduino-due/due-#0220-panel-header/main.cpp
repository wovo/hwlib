#include "hwlib.hpp"

namespace hwlib {
    
// learn.sparkfun.com/tutorials/rgb-panel-hookup-guide
// https://bikerglen.com/projects/lighting/led-panel-1up/
// https://docs.pixelmatix.com/SmartMatrix/shieldref.html

template< int x_size, int y_size >
class led_panel : public window, public background {
    color buffer[ x_size ][ y_size ];
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
      window( xy( x_size, y_size ) ),
      rgb0( rgb0 ), rgb1( rgb1 ), abcd( abcd ),
      clk( clk ), stb( stb ), oe( oe ),
      next_run( hwlib::now_us() )
   {}
   
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
      next_run += 500;
       
      static int p = 0;
      p = ( p + 1 ) % 16;
      
      for( int i = 0; i < x_size; ++i ){
         clk.write( 0 );
         clk.flush();
         
         rgb0.write( rgb_bits( buffer[ i ][ p ] )); 
         rgb1.write( rgb_bits( buffer[ i ][ 16 + p ] )); 
         rgb0.flush();
         rgb1.flush();
           
         clk.write( 1 );
         clk.flush();
         hwlib::wait_us( 1 );
         
      }
      
      oe.write( 1 );
      hwlib::wait_us( 1 );
      
      abcd.write( p );
      abcd.flush();
      
      stb.write( 1 );
      hwlib::wait_us( 1 );
      stb.write( 0 );
      
      hwlib::wait_us( 1 );
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

class window_combine_x : public window {
private:

   window & w1;
   window & w2;    
   
   void write_implementation( xy pos, color col ) override {
      if( pos.x < w1.size.x ){
         w1.write( pos, col );
      } else {
         w2.write( pos - xy( w1.size.x, 0 ), col );
      }
   }     

public:    

   window_combine_x( window & w1, window & w2 ):
      window( xy( w1.size.x + w2.size.x, w1.size.y ) ),
      w1( w1 ),
      w2( w2 )
   {}

   void flush() override {
      w1.flush();
      w2.flush();
   }  

};

class window_flip : public window {
private:

   window & w;  
   
   void write_implementation( xy pos, color col ) override {
      w.write( xy( pos.y, pos.x ), col );
   }     

public:    

   window_flip( window & w ):
      window( xy( w.size.y, w.size.x ) ),
      w( w )
   {}

   void flush() override {
      w.flush();
   }  

};

class window_mirror_x : public window {
private:

   window & w;  
   
   void write_implementation( xy pos, color col ) override {
      w.write( xy( w.size.x - 1 - pos.x, pos.y ), col );
   }     

public:    

   window_mirror_x( window & w ):
      window( w.size ),
      w( w )
   {}

   void flush() override {
      w.flush();
   }  

};

template< int size_x, int size_y >
class window_buffer : window {
private:

   color buffer[ size_x ][ size_y ];
    
   void write_implementation( xy pos, color col ) override {
       buffer[ pos.x ][ pos.y ] = col;
   }    
   
   
   class box_class : image {
   private:
      window_buffer & b;   
      xy start;
      
   public:
      box_class(  window_buffer & b, xy start, xy size ):
         b( b ), start( start ), image( size )
      {}
         
      color operator[]( xy pos ) const override {
         return b.buffer[ start.x + pos.x ][ start.y + pos.y ];
      }       
   };

public:

   window_buffer():
      window( xy( size_x, size_y ) ),
      image( xy( size_x, size_y ) )
   {}
   
   void flush() override {} 

   box_class box( xy start, xy size ){
      return box_class( *this, start, size );       
   }
};

}

/*
class hoover : public hwlib::background {
private:
    hwlib::window_buffer & b;
    hwlib::window & w;
public:    
   hoover( hwlib::window_buffer & b ), hwlib::window & w ):
      b( b ), w( w )
   {}       
   
   void work() override {
      if( hwlib::now_us() < next_run ){
         return;
      }       
      next_run += 10'000;   
      
      buffer.part( xy( 0, 0), xy( 20, 20 ) ).write( w );
      w.flush();
   }      
};
*/

int main( void ){
    
   auto led1   = hwlib::target::pin_out{ hwlib::target::pins::d6  };
   auto led2   = hwlib::target::pin_out{ hwlib::target::pins::d7  };
   auto led3   = hwlib::target::pin_out{ hwlib::target::pins::d8  };
   auto led4   = hwlib::target::pin_out{ hwlib::target::pins::d9  };
   auto led5   = hwlib::target::pin_out{ hwlib::target::pins::d10 };
   auto led6   = hwlib::target::pin_out{ hwlib::target::pins::d11 };
   auto led7   = hwlib::target::pin_out{ hwlib::target::pins::d12 };
   auto led8   = hwlib::target::pin_out{ hwlib::target::pins::d13 };
   auto leds   = hwlib::port_out_from( led1, led2, led3, led4, led5, led6, led7, led8 );
    
   auto led   = hwlib::target::pin_out{ hwlib::target::pins::led };
   
   auto r0   = hwlib::target::pin_out{ hwlib::target::pins::d22 };
   auto b0   = hwlib::target::pin_out{ hwlib::target::pins::d24 };
   auto r1   = hwlib::target::pin_out{ hwlib::target::pins::d26 };    
   auto b1   = hwlib::target::pin_out{ hwlib::target::pins::d28 };    
   auto a    = hwlib::target::pin_out{ hwlib::target::pins::d30 };    
   auto c    = hwlib::target::pin_out{ hwlib::target::pins::d32 };    
   auto clk  = hwlib::target::pin_out{ hwlib::target::pins::d34 };
   auto oe   = hwlib::target::pin_out{ hwlib::target::pins::d36 };    
   
   auto g0   = hwlib::target::pin_out{ hwlib::target::pins::d23 };    
   auto gnd1 = hwlib::target::pin_out{ hwlib::target::pins::d25 };    
   auto g1   = hwlib::target::pin_out{ hwlib::target::pins::d27 };
   auto gnd2 = hwlib::target::pin_out{ hwlib::target::pins::d29 };    
   auto b    = hwlib::target::pin_out{ hwlib::target::pins::d31 };
   auto d    = hwlib::target::pin_out{ hwlib::target::pins::d33 };    
   auto stb  = hwlib::target::pin_out{ hwlib::target::pins::d35 };    
   auto gnd3 = hwlib::target::pin_out{ hwlib::target::pins::d37 };    
   
   auto rgb0 = hwlib::port_out_from( r0, g0, b0 );
   auto rgb1 = hwlib::port_out_from( r1, g1, b1 );
   auto abcd = hwlib::port_out_from( a, b, c, d );
   auto gnd  = hwlib::port_out_from( gnd1, gnd2, gnd3 );
   gnd.write( 0 ); gnd.flush();
    
   auto w1 = hwlib::led_panel< 64, 32 >( rgb0, rgb1, abcd, clk, stb, oe );
      hwlib::blinker( led1, 200 );    

   
   auto w1a = hwlib::part( w1, hwlib::xy(  0, 0 ), hwlib::xy( 32, 32 ) );
   auto w1b = hwlib::part( w1, hwlib::xy( 32, 0 ), hwlib::xy( 32, 32 ) );
   
   auto w1af = hwlib::window_mirror_x( w1a );
   auto w1bf = hwlib::window_flip( w1b );
   
   auto w12 = hwlib::window_combine_x( w1af, w1b );
   
   auto w = hwlib::window_with_frame( w12, 2, hwlib::blue );
   
//   auto large = hwlib::window_buffer< 100, 100 >();
//   auto h = hoover( large, w );
   hwlib::graphics_random_lines( w, 30, hwlib::red );
   for(;;){
      led2.write( 0 );       
      hwlib::wait_ms( 50 );
      led2.write( 1 );
      hwlib::wait_ms( 50 );
   }
}   