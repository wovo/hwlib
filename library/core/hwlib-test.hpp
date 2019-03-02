// ==========================================================================
//
// File      : hwlib-test.hpp
// Part of   : C++ hwlib library for close-to-the-hardware OO programming
// Copyright : wouter@voti.nl 2017-2019
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

// included only via hwlib.hpp, hence no multiple-include guard is needed

// this file contains Doxygen lines
/// @file

namespace hwlib {
	
extern int _equal_calls_count;	
extern int _equal_failures_count;

// called by HWLIB_EQUAL
template< typename A, typename B >
void _equal( 
   const char * f, int n,            // file name and line number
   const char * ta, const char *tb,  // arguments, stringified
   const A & a, const B & b          // arguments, as-is
){
   ++_equal_calls_count;	
   if( a != b ){
	  ++_equal_failures_count;
      hwlib::cout 
         << f << ":" << hwlib::dec << n 
         << " check failed \n" 
         << "   HWLIB_TEST_EQUAL( " << ta << " , " << tb << " )\n"
         << "   left  \"" << ta << "\" = " << a << "\n"
         << "   right \"" << tb << "\" = " << b << "\n\n";
   }
}

/// \brief
/// report whether the HWLIB_TEST_EQUAL calls were successful
/// \details
/// Call test_end() at the end of your test application
/// that uses HWLIB_TEST_EQUAL for its checks.
/// It will print (to hwlib::cout) either the number of 
/// tests (if all were successful), or the number of failures
/// (when not all test were successful).
void test_end();


// ===========================================================================
//
// implementations
//
// ===========================================================================

#ifdef _HWLIB_ONCE 

int _equal_calls_count    = 0;	
int _equal_failures_count = 0;

void test_end(){
   if( _equal_failures_count == 0 ){
      hwlib::cout 
	     << "\nTest success: " 
		 << hwlib::dec << _equal_calls_count
		 << " test were successfull\n";
   } else {	   
      hwlib::cout 
	     << "\nTEST FAILURE: " 
		 << hwlib::dec << _equal_failures_count
		 << " test were NOT successfull\n";
   }	  
}

#endif // _HWLIB_ONCE

}; // namespace hwlib
