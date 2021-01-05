// ==========================================================================
//
// blink the LED on an Arduino Uno
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
   DDRB |= ( 0b01 << 5 );
   for(;;){
      PORTB &= ~( 0b01 << 5 );
      for( volatile uint32_t i = 0; i < 50'000; ++i );
      PORTB |= ( 0b01 << 5 );
      for( volatile uint32_t i = 0; i < 50'000; ++i );
   }      
}
