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
	
//! [[Doxygen direction example]]

   auto pin = hwlib::target::pin_in_out( 1, 8 );
   
   // direction is changed to input before a read
   pin.direction_set_input();
   pin.direction_flush();
   
   pin.refresh();
   if( pin.read() ){ /* do something */ }
  
   // direction is changed to output before a write
   pin.direction_set_output();
   pin.direction_flush();
   
   pin.write( 1 );
   pin.flush();

//! [[Doxygen direction example]]

}
