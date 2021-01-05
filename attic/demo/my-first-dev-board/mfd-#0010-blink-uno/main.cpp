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
   auto red = hwlib::target::pin_out( hwlib::target::pins::d11 );
   red.write( 1 );
   red.flush();
   
   auto led = hwlib::target::pin_out( hwlib::target::pins::d2 );
   hwlib::blink( led );
}