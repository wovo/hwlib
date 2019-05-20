// ==========================================================================
//
// empty project
//
// (c) Wouter van Ooijen (wouter@voti.nl) 2017
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt) 
//
// ==========================================================================

#include "hwlib.hpp"

#include "hwlib.hpp"

int main( void ){
   hwlib::target::board board; 
   
   auto leds = hwlib::all(
      board.led1, board.led2, board.led3, board.led4, 
      board.led5, board.led6, board.led7, board.led8, board.led9 );
   leds.write( 1 );
   leds.flush();
   
   auto colors = hwlib::port_out_from(
      board.red, board.green, board.blue );
   hwlib::snake( colors, 1'000 );
}