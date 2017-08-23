// ==========================================================================
//
// hwlib::string demo
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

int main( void ){
   hwlib::string< 100 > t( "Hello brave new world!\n" );
   t[ 3 ] = t[ 4 ];
   std::cout << t;
   
   constexpr auto x = hwlib::string<0>::range( "hello\n" );
   std::cout << x;
   
   //auto r = t.range_start_end( 2, 5 );
   //hwlib::string< 100 > rr = r;
   //std::cout << "[" << rr << "]\n";
   
   //std::cout << "[" << t.range_start_length( 3, 9 ) << "]\n";
}
