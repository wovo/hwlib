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
   for(int i = 1;; ++ i){   
      hwlib::cout << "Hello world for the " << i << "th time!\n";
      hwlib::wait_ms( 1'000 );
   }
}      
 