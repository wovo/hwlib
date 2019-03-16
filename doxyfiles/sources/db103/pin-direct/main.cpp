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
	
//! [[Doxygen direct example]]

   // a direct pin requires no refresh() or flush() calls

   auto raw_pin = hwlib::target::pin_in_out( 1, 8 );
   auto pin = hwlib::direct( raw_pin );
   
   pin.direction_set_input();
   if( pin.read() ){ /* do something */ }
  
   pin.direction_set_output();
   pin.write( 1 );
   
//! [[Doxygen direct example]]

}
