// ==========================================================================
//
// blink a LED on pin 1-9
//
// (c) Wouter van Ooijen (wouter@voti.nl) 2017-2019
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt) 
//
// ==========================================================================

#include "hwlib.hpp"

int main( void ){
	
//! [[Doxygen invert example]]

   // the led is connected to ground, hence 
   // its pin must be low to enable the led

   auto pin = hwlib::target::pin_out( 1, 8 );
   auto led = hwlib::invert( pin );
   
   // enable the led
   led.write( 1 );
   led.flush();

//! [[Doxygen invert example]]

}
