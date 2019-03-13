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
    
   if constexpr ( hwlib::target_board == hwlib::target_boards::arduino_uno ){

      DDRB |= ( 0b01 << 5 );
      for(;;){
         PORTB &= ~( 0b01 << 5 );
         for( volatile uint32_t i = 0; i < 50'000; ++i );
         PORTB |= ( 0b01 << 5 );
         for( volatile uint32_t i = 0; i < 50'000; ++i );
      }      
   
   } else if constexpr ( hwlib::target_board == hwlib::target_boards::arduino_due ){

      PIOB->PIO_OER = 0x01 << 27;
      for(;;){
         PIOB->PIO_SODR = 0x01 << 27;
         for( volatile int i = 0; i < 100'000; i++ ){}
         IOB->PIO_CODR = 0x01 << 27;
         for( volatile int i = 0; i < 100'000; i++ ){}
      }    

   } else {
       
       void no_blink_variation_for_this_target();
       no_blink_variation_for_this_target();
       
   }

}

