// ==========================================================================
//
// blink 2 + 2 alternate LEDs
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
   auto p15 = hwlib::target::pin_out( 1, 5 );
   auto p14 = hwlib::target::pin_out( 1, 4 );

   auto p15i = hwlib::invert( p15 );
   auto p14i = hwlib::invert( p14 );
   
   auto leds = hwlib::all( p19, p18, p15i, p14i );
   
   hwlib::blink( leds );
}