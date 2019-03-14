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

int main(){
   
   // wait for the terminal emulator to start up
   hwlib::wait_ms( 1'000 );
   
   hwlib::cout << "all( xy ) iterator demo " << "\n";       
   
   hwlib::xy r( 2, 3 );
   for( auto v : all( r ) ){
      hwlib::cout << v.x << " " << v.y << "\n";       
   }
}   

