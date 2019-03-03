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

   auto raw_pin = hwlib::target::pin_in_out( 1, 8 );
   auto oc_pin  = hwlib::pin_oc_from( raw_pin );
      
   // the pin behaves as an open-collector pin, so making it high 
   // will actually set the pin to input	  
   oc_pin.write( 1 );
   oc_pin.flush();

   oc_pin.refresh();
   if( oc_pin.read() ){ /* do something */ }
   
//! [[Doxygen conversion example]]

}
