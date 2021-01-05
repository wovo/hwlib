// ==========================================================================
//
// blink a LED on DB103 (LPC1114)
//
// (c) Wouter van Ooijen (wouter@voti.nl) 2017
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt) 
//
// ==========================================================================

// ==========================================================================
//
// kitt on all 12 available pins
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
   
   auto g1 = hwlib::all( scl, p10, p14 );
   auto g2 = hwlib::all( sda, p11, p15 );
   auto g3 = hwlib::all( p06, p12, p18 );
   auto g4 = hwlib::all( p07, p13, p19 );
   
   auto leds = hwlib::port_out_from( g1, g2, g3, g4 );
   
   hwlib::snake( leds );
}
