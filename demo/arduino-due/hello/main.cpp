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
    
   // kill the watchdog
   WDT->WDT_MR = WDT_MR_WDDIS;
   
   // wait for the terminal to start on the PC side
   hwlib::wait_ms( 500 );
   
   hwlib::cout 
      << "Hello world!\n" 
      << "please type something " 
      << hwlib::flush;
      
   for(;;){
       char c;
       hwlib::cin >> c;
       hwlib::cout << "[" << c << "]" << hwlib::flush;
   }      
}
