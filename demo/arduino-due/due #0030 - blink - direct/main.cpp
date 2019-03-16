// ==========================================================================
//
// blink the LED on an Arduino Due
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
   
   // make the GPIO pin an output   
   PIOB->PIO_OER = { 0x1U << 27 };
   
   for(;;){
      
      // make the GPIO pin high
      PIOB->PIO_SODR = 0x01 << 27;

      // wait some time
      for( volatile uint32_t i = 0; i < 100'000; i++ ){}

      // make the GPIO pin low
      PIOB->PIO_CODR = 0x01 << 27;

      // again, wait some time
      for( volatile uint32_t i = 0; i < 100'000; i++ ){}

   }      
}

