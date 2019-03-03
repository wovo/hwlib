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

   // specify a pin by its port name and pin number
   
   auto pin = hwlib::target::pin_out( 1, 5 );
   
//! [[Doxygen pin example]]

   hwlib::blink( pin );
}
