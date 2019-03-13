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
    
   auto sw_black = hwlib::target::pin_in_out( hwlib::target::pins::a1 );
   //auto sw_black = hwlib::target::pin_adc( 1 );
   auto adc_pin = hwlib::target::pin_adc( 0 );
   auto sw5 = hwlib::target::pin_adc( 7 );
   auto sw6 = hwlib::target::pin_adc( 6 );
   
   sw_black.direction_set_input();
   sw_black.write(1);
   
   // wait for the terminal emulator to start up
   hwlib::wait_ms( 1'000 );   
       
   hwlib::cout 
      << "input demo \n";
         
   for(;;){       
      
      hwlib::cout 
         << "B = "
         << sw_black.read()
         << "   "
         << "sw5 = "
         << (( sw5.read() > 512 ) ? "H" : "L" )
         << "   "
         << "sw6 = "
         << (( sw6.read() > 512 ) ? "H" : "L" )
         << "   "
         << "adc = "
         << adc_pin.read()
         << "\n";
   }         
}
