// ==========================================================================
//
// unit tests for hwlib::string
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

// needed to get Catch working with MinGW
#define TWOBLUECUBES_CATCH_REPORTER_JUNIT_HPP_INCLUDED
namespace Catch{ class JunitReporter{ ~JunitReporter(); }; };

#include "catch_with_main.hpp"

TEST_CASE( "fixed_string, constructor_char" ){
	// ctor char
	const hwlib::string< 5 > s( '1' );
	REQUIRE( 5u == s.get_allocated_length() );
	REQUIRE( 1u == s.get_current_length() );
	REQUIRE( s == "1" );
	REQUIRE( "1" == s );
}

