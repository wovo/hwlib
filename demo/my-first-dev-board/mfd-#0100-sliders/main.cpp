// ==========================================================================
//
// empty project
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
   hwlib::target::board board;   
   for(;;){   
      hwlib::cout 
         << "adc: " 
         << hwlib::setw( 4 ) << board.adc.read() 
         << "\n";
      hwlib::wait_ms( 500 );
   }
}