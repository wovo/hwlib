// ==========================================================================
//
// OLED demo on DB103 (LPC1114)
//
// (c) Wouter van Ooijen (wouter@voti.nl) 2019
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt) 
//
// ==========================================================================

// ==========================================================================
//
// OLED demo on DB103 (LPC1114)
//
// (c) Wouter van Ooijen (wouter@voti.nl) 2019
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt) 
//
// ==========================================================================

#include "hwlib.hpp"

namespace hwlib {
    
template< int x_size, int y_size >    
class neopixels : public window {
private:

   std::array< std::array<  color, y_size >, x_size > buffer;
   
   pin_out & pin;
   
   void send_bit( bool b ){
      if( b ){
         pin.write( 1 );
         pin.write( 1 );
         //pin.flush();             
         pin.write( 0 );
         //pin.flush();             
      } else {
         pin.write( 1 );
         //pin.flush();             
         pin.write( 0 );
         //pin.flush();             
      }       
   }
   
   void send_byte( uint8_t b ){  
      for( int i=0; i<8; ++i ){
         send_bit( b & 0b1000'0000 ) ;
         b = b << 1;
      }    
   }
   
   void write_implementation( xy pos, color col ) override {
       buffer[ pos.x ][ pos.y ] = col;
   }

public:    

   neopixels( pin_out & pin ): 
      window( xy( x_size, y_size )), pin( pin )
   {
      wait_us( 1 );       
   }
   
   void flush() override {
      wait_us( 10 );       
      for( int y = 0; y < size.y; ++y ){         
         for( int x = 0; x < size.x; ++x ){
            auto pixel = buffer[ x ][ y ];             
            send_byte( pixel.green );
            send_byte( pixel.red );
            send_byte( pixel.blue );
         }
      }       
   }
};

class pin_out_from_window_t : public pin_out {
private:

   window & w;
   color on, off;
   
public:

   pin_out_from_window_t( window & w, color on, color off ):
      w( w ), on( on ), off( off )
   {}
      
   void write( bool b ) override {
      w.clear( b ? on : off );
   }   
   
   void flush() override {
      w.flush();
   }
       
};

class port_out_from_window_t : public port_out {
private:

   int y;
   window & w;
   color on, off;
   
public:

   port_out_from_window_t( window & w, color on, color off, int y = 0 ):
      y( y ), w( w ), on( on ), off( off )
   {}
   
   uint_fast8_t number_of_pins(){
      return std::min( 16, w.size.x );
   }
      
   void write( uint_fast16_t b ) override {
      for( int x = 0; x < (int) number_of_pins(); ++x ){
         w.write( xy( x, y ), ( b & 0b01 )  ? on : off );
         b = b >> 1;
      }         
   }   
   
   void flush() override {
      w.flush();
   }
       
};

} // hwlib

int main( void ){
     
   namespace target = hwlib::target;
   
   auto d2 = hwlib::target::pin_out{ hwlib::target::pins::d2 };
   auto w = hwlib::neopixels< 16, 1 >( d2 );
   auto pin = hwlib::pin_out_from_window_t( w, hwlib::blue, hwlib::red );
   auto port = hwlib::port_out_from_window_t( w, hwlib::yellow / 8, hwlib::blue / 32 );
   
   hwlib::kitt( port, 50 );
   hwlib::blink( pin );
}