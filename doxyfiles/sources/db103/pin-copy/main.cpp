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

void flush(){

//! [[Doxygen flush example]]

   // copying an input to an output, with explcit refersh() and flush()
   
   auto sw   = hwlib::target::pin_in( 1, 8 );
   auto led  = hwlib::target::pin_out( 1, 9 );
   for(;;){
      sw.refresh();       
      auto v = sw.read();
      
      led.write( v );
      led.flush();
   }
   
//! [[Doxygen flush example]]

}

void direct(){
   
//! [[Doxygen direct example]]

   // copying an input to an output, using direct()
   
   auto sw_pin   = hwlib::target::pin_in( 1, 8 );
   auto led_pin  = hwlib::target::pin_out( 1, 9 );
   auto sw       = hwlib::direct( sw_pin );;
   auto led      = hwlib::direct( led_pin );
   for(;;){
      auto v = sw.read();
      led.write( v );
   }
   
///! [[Doxygen direct example]]

}

int main( void ){
   flush();
   direct();
}
