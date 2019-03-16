// ==========================================================================
//
// blink the LED on an Arduino Uno
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
   auto led0 = hwlib::target::pin_out( hwlib::target::pins::a0 );
   auto led1 = hwlib::target::pin_out( hwlib::target::pins::a1 );
   auto led2 = hwlib::target::pin_out( hwlib::target::pins::a2 );
   auto led3 = hwlib::target::pin_out( hwlib::target::pins::a3 );
   auto led4 = hwlib::target::pin_out( hwlib::target::pins::a4 );
   auto led5 = hwlib::target::pin_out( hwlib::target::pins::a5 );
   auto leds = hwlib::port_out_from_pins( led0, led1, led2, led3, led4, led5 );
   hwlib::kitt( leds );
}
