// ==========================================================================
//
// Test whether a project can contain two source files.
//
// This causes some trouble with the MingW linker, because it doesn't
// handle weak definitions. Hence being weak is sufficient for an embedded
// build, but not for a windows-hosted build.
//
// (c) Wouter van Ooijen (wouter@voti.nl) 2017
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt) 
//
// ==========================================================================

#include "hwlib.hpp"
#include <iostream>

int main(){
   hwlib::cout << "'empty' main test\n";
   hwlib::test_end();
}   

