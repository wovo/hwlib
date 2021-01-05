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

int main( void ){
   hwlib::target::board board; 
   
   board.blue.write( 1 );
   board.blue.flush();
   
   auto leds = hwlib::port_out_from(
      board.led1, board.led2, board.led3, board.led6, 
      board.led9, board.led8, board.led7, board.led4 );
   hwlib::snake( leds, 50 );
}