// ==========================================================================
//
// blink a LED on pin 1-9
//
// (c) Wouter van Ooijen (wouter@voti.nl) 2017-2019
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt) 
//
// ==========================================================================

#include "hwlib.hpp"

int main( void ){

//! [[Doxygen read example]]

   // read returns a bool
   
   auto sw_pin = hwlib::target::pin_in( 1, 8 );
   sw_pin.refresh();
   if( sw_pin.read() ){
      // do something if the pin was high	   
   }	   

//! [[Doxygen read example]]

//! [[Doxygen write example]]

   // write takes a bool
   
   auto led_pin = hwlib::target::pin_out( 1, 9 );
   led_pin.write( 1 );
   led_pin.flush();

//! [[Doxygen write example]]

}
