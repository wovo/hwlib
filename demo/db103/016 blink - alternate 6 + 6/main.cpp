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
   
   auto p07 = hwlib::target::pin_out( 0, 7 );
   auto p06 = hwlib::target::pin_out( 0, 6 );
   auto sda = hwlib::target::pin_out{ 0, 5 };
   auto scl = hwlib::target::pin_out{ 0, 4 };   

   auto p07i = hwlib::pin_invert_from_out( p07 );
   auto p06i = hwlib::pin_invert_from_out( p06 );
   auto sdai = hwlib::pin_invert_from_out( sda );
   auto scli = hwlib::pin_invert_from_out( scl );
   
   auto leds = hwlib::all(
      p19, p18, p15, p14,
      p07i, p06i, sdai, scli
   );      
   
   hwlib::blink( leds );
}