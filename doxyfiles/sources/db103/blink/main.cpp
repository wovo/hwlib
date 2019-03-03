// ==========================================================================
//
// blink a single LED on pin 1-9
//
// (c) Wouter van Ooijen (wouter@voti.nl) 2017-2019
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt) 
//
// ==========================================================================

//! [[Doxygen blink example]]

#include "hwlib.hpp"

// blink example (using an explicit loop and explicit flush calls)

int main( void ){
   auto led = hwlib::target::pin_out( 1, 9 );
   
   for(;;){
      led.write( 1 );
      led.flush();
      hwlib::wait_ms( 200 );   
      
      led.write( 0 );
      led.flush();
      hwlib::wait_ms( 200 );   
   }
}

//! [[Doxygen blink example]]

