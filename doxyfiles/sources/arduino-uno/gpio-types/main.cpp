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
    
//! [[Doxygen pin example]]

   // constructing four types of pins   
   
   auto in      = hwlib::target::pin_in( 1, 0 );
   auto out     = hwlib::target::pin_out( 1, 1 );
   auto in_out  = hwlib::target::pin_in_out( 1, 2 );
   auto oc      = hwlib::target::pin_oc( 1, 3 );
   
//! [[Doxygen pin example]]

   (void) in;
   (void) out;
   (void) in_out;
   (void) oc;
}
