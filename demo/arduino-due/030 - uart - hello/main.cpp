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
   
   // wait for the terminal emulator to start up
   hwlib::wait_ms( 1'000 );
       
   hwlib::cout 
      << "Hello world!\n" 
      << hwlib::flush;
}
