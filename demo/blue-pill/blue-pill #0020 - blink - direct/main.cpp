// ==========================================================================
//
// blink the LED on a blue-pill board
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
  
   GPIOB->CRH &= ~( 0xF << ( 5 * 4 ));
   GPIOB->CRH |= 0x03 << ( 5 * 4 );
   
   for(;;){
      GPIOB->BSRR |= ( 0x01 << 13 );

      // wait some time
      for( volatile uint32_t i = 0; i < 10'000; i++ ){}
	  
      GPIOB->BSRR |= ( 0x01 << ( 13 + 16 ));
	  
      // wait some time
      for( volatile uint32_t i = 0; i < 10'000; i++ ){}
	  
   }	  
}

