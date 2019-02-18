// ==========================================================================
//
// Test whether a project can contain two source files.
//
// (c) Wouter van Ooijen (wouter@voti.nl) 2017
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt) 
//
// ==========================================================================

#include "hwlib.hpp"

void test(){
   std::cout << "Test function called\n";
   HWLIB_TEST_EQUAL( 0, 0 );
}
