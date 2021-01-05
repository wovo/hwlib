// ==========================================================================
//
// Hello world on DB103 (LPC1114)
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
   
   auto adc = hwlib::target::pin_adc( 1, 0 );
       
   for(;;){       
      hwlib::wait_ms( 500 );
      
      hwlib::cout 
         << "adc = " << hwlib::hex << adc.read()
         << "\n" << hwlib::flush;
   }         
}
