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

   auto p10  = hwlib::target::pin_in_out( 1, 0 );
   auto p11  = hwlib::target::pin_in_out( 1, 1 );
   auto port = hwlib::port_in_out_from( p10, p11 );
   
   // direction is changed to input before a read
   port.direction_set_input();
   port.direction_flush();
   
   port.refresh();
   uint8_t v = port.read();
  
   // direction is changed to output before a write
   port.direction_set_output();
   port.direction_flush();
   
   port.write( 0b01 );
   port.flush();

//! [[Doxygen direction example]]

   (void) v;

}
