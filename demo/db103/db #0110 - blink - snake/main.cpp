// ==========================================================================
//
// blink LEDs 'snake'-wise
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

   auto p13 = hwlib::target::pin_out( 1, 3 );
   auto p12 = hwlib::target::pin_out( 1, 2 );
   auto p11 = hwlib::target::pin_out( 1, 1 );
   auto p10 = hwlib::target::pin_out( 1, 0 );

   auto p07 = hwlib::target::pin_out( 0, 7 );
   auto p06 = hwlib::target::pin_out( 0, 6 );
   auto sda = hwlib::target::pin_out{ 0, 5 };
   auto scl = hwlib::target::pin_out{ 0, 4 };
   
   auto p18i = hwlib::invert( p18 );
   auto p14i = hwlib::invert( p14 );
   auto p12i = hwlib::invert( p12 );
   auto p10i = hwlib::invert( p10 );
   auto p06i = hwlib::invert( p06 );
   auto scli = hwlib::invert( scl );   
   
   auto leds = hwlib::all( 
      p19, p18i, p15, p14i,
      p13, p12i, p11, p10i,
      p07, p06i, sda, scli   
   );
   
   hwlib::blink( leds );
}
