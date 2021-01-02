// ==========================================================================
//
// blink a LED on pin 1-9
//
// (c) Wouter van Ooijen (wouter@voti.nl) 2017
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt) 
//
// ==========================================================================

#include "hwlib.hpp"

const auto port  = 1;
const auto pin   = 9;
const auto mask  = 0x01U << pin;

volatile uint32_t *gpioreg( uint32_t port, uint32_t offset ){
   return (volatile uint32_t *)( 0x50000000 + port * 0x10000 + offset );
}

int main( void ){

   *gpioreg( port, 0x8000 ) |= mask;    
   
   for(;;){
      *gpioreg( port, 0x04 << pin ) = -1;
      
      for( volatile int i = 0; i < 200'000; ++i ){}

      *gpioreg( port, 0x04 << pin ) = 0; 

      for( volatile int i = 0; i < 200'000; ++i ){}
   }
}