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
	
//! [[Doxygen port-from example]]
   
   // create a port-out from four pin-out's
   
   auto p10 = hwlib::target::pin_out( 1, 0 );
   auto p11 = hwlib::target::pin_out( 1, 1 );
   auto p12 = hwlib::target::pin_out( 1, 2 );
   auto p13 = hwlib::target::pin_out( 1, 3 );
   auto port = hwlib::port_out_from( p10, p11, p12, p13 );  

//! [[Doxygen port-from example]]

}
