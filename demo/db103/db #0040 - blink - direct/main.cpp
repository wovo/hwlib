// ==========================================================================
//
// blink a LED on pin 1-9
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
   auto pin = hwlib::target::pin_out( 1, 9 );
   auto led = hwlib::direct( pin );
   
   for(;;){
      led.write( 1 );
      hwlib::wait_ms( 200 );   
      led.write( 0 );
      hwlib::wait_ms( 200 );   
   }
}
