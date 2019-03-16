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

   // a direct port requires no refresh() or flush() calls
   
   auto p10 = hwlib::target::pin_in_out( 1, 0 );
   auto p11 = hwlib::target::pin_in_out( 1, 1 );
   auto raw_port = hwlib::port_in_out_from( p10, p11 );   

   auto port = hwlib::direct( raw_port );
   
   port.direction_set_input();
   auto d = port.read();
  
   port.direction_set_output();
   port.write( d | 0b0011 );
   
//! [[Doxygen direct example]]

   (void) d;

}
