// ==========================================================================
//
// empty project
//
// (c) Wouter van Ooijen (wouter@voti.nl) 2017
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt) 
//
// ==========================================================================

#include "hwlib.hpp"

int main( void ){
   hwlib::target::board board;  
   
   auto & color = board.green;
   color.write( 1 );
   color.flush();     
   
   auto & led = board.led1;

   for(;;){   
      board.adc.refresh();
      auto x = board.adc.read();
      auto a = 20 * x;
      auto b = 20 * ( board.adc.adc_max_value - x );
      
      // hwlib::cout << board.adc.adc_max_value << "\n";
      
      led.write( 1 );
      led.flush();      
      hwlib::wait_us( a );
      
      led.write( 0 );
      led.flush();
      hwlib::wait_us( b );
   }
}