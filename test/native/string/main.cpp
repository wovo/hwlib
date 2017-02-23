// ==========================================================================
//
// Catch unit tests for hwlib::string
//
// (c) Wouter van Ooijen (wouter@voti.nl) 2017
//
// Based on the test of his string class by Martin Broers.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt) 
//
// ==========================================================================

#include "hwlib.hpp"
#include <iostream>

// needed to get Catch working with MinGW
#define TWOBLUECUBES_CATCH_REPORTER_JUNIT_HPP_INCLUDED
namespace Catch{ class JunitReporter{ ~JunitReporter(); }; };

#include "catch_with_main.hpp"

constexpr cstrlen( const char * s ){
    return *s == '\0' ? 0 : 1 + cstrlen( s + 1 );
}

TEST_CASE( "fixed_string, defalt constructor" ){
   // default ctor 
   const hwlib::string< 5 > s;
   REQUIRE( 5u == s.max_size() );
   REQUIRE( 0u == s.length() );
   REQUIRE( s == "" );
   REQUIRE( "" == s );
}

TEST_CASE( "fixed_string, constructor_char" ){
   // ctor char
   const hwlib::string< 5 > s( '1' );
   REQUIRE( 5u == s.max_size() );
   REQUIRE( 1u == s.length() );
   REQUIRE( s == "1" );
   REQUIRE( "1" == s );
}

TEST_CASE( "fixed_string, constructor_char_array" ){
   // ctor char array - same length
    const char t[] = "char_array";
   hwlib::string< strlen( "char_array" ) > s( t );
   REQUIRE( t == s );
   REQUIRE( strlen( t ) == s.max_size() );
   REQUIRE( strlen( t ) == s.length() );
}

TEST_CASE( "fixed_string, constructor_fixed_string" ){
   constexpr char t[] = "fixed_string";
   const hwlib::string< cstrlen( t ) > original( t );
   REQUIRE( original == t );
   REQUIRE( t == original );

   // constructor same size
   const hwlib::string< cstrlen( t )> same( original );
   REQUIRE( t                               == same );
   REQUIRE( original                        == same );
   REQUIRE( original                        == same.c_str() );
   REQUIRE( original.max_size()  == same.max_size() );
   REQUIRE( original.length()    == same.length()   );

   // ctor larger < N >
   const hwlib::string< 15 > larger( original );
   REQUIRE( t                         ==   larger );
   REQUIRE( original.c_str()          ==   larger );
   REQUIRE( 15                        ==   larger.max_size() );
   REQUIRE( cstrlen( t )              ==  larger.length());

   // ctor smaller <N>
    const hwlib::string< 5 > smaller( original );
   REQUIRE( "fixed"                   ==            smaller );
   // expect greater than (val1 > val2)
   //REQUIRE( original                       >             smaller );
   REQUIRE( 5                        ==             smaller.max_size() );
   REQUIRE( 5                      ==            smaller.length() );
}

TEST_CASE( "fixed_string, chained append" ){
   hwlib::string< 20 > s ( "bla bla" );
   hwlib::string< 20 > t = "foo";
   
   s.clear() << "[" << t << "]";
   REQUIRE( s == "[foo]" );
   
   t = "world";
   ( s = "x" ) << "[" << t << "]";
   REQUIRE( s == "x[world]" );
}