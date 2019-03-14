// ==========================================================================
//
// blink 4 + 4 alternate LEDs
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
   
   auto p07 = hwlib::target::pin_out( 1, 3 );
   auto p06 = hwlib::target::pin_out( 1, 2 );
   auto sda = hwlib::target::pin_out{ 1, 1 };
   auto scl = hwlib::target::pin_out{ 1, 0 };  

   auto leds1 = hwlib::all( p19, p18, p15, p14 );
   auto leds2 = hwlib::all( p07, p06, sda, scl );
   auto leds2i = invert( leds2 );
   
   auto leds = hwlib::all( leds1, leds2i );  
   
   hwlib::blink( leds );
}