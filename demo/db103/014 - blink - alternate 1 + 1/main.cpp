// ==========================================================================
//
// blink 2 alternate LEDs
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
    
   auto p19 = hwlib::target::pin_out( 1, 9 );
   auto p18 = hwlib::target::pin_out( 1, 8 );

   auto p18i = hwlib::invert( p18 );
   
   auto leds = hwlib::all( p19, p18i );
   
   hwlib::blink( leds );
}
