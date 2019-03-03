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

   // the leds are connected to ground, hence 
   // each pin must be low to enable its led
   
   auto p10  = hwlib::target::pin_out( 1, 0 );
   auto p11  = hwlib::target::pin_out( 1, 1 );
   auto port = hwlib::port_out_from( p10, p11 );
   auto leds = hwlib::invert( port );
   
   // enable both leds
   leds.write( 0b11 );
   leds.flush();

//! [[Doxygen invert example]]

}
