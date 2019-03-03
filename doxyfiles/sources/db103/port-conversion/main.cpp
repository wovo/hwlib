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
	
//! [[Doxygen conversion example]]

   auto p10  = hwlib::target::pin_in_out( 1, 0 );
   auto p11  = hwlib::target::pin_in_out( 1, 1 );
   auto pins = hwlib::port_in_out_from( p10, p11 );

      
   // construct an output version	  
   auto port = hwlib::port_out_from( pins );
   
   // now we can write without setting the direction
   port.write( 0b11 );
   port.flush();

   
//! [[Doxygen conversion example]]
}
