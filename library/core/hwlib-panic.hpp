// ==========================================================================
//
// File      : hwlib-panic.hpp
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


/// panic function for irrecoverable runtime errors
/// 
/// This function is called by hwlib functions when an irrecoverable error
/// is encountered (for instance an invalid pin or port number).
///
/// The default panic() enters a never-ending loop. 
///
/// An application can define its own panic() function, which
/// overrides the default implementation. It must not return.
///
/// The following fragment is an example of an application-defined
/// panic function:
/// \snippet "db103\panic\main.cpp" [Doxygen panic example]
///
void HWLIB_NORETURN panic( 
   const char * file, 
   const uint_fast16_t line 
);


/// panic-with-location macro 
/// 
/// This macro calls panic( __FILE__, __LINE__ ).
#define HWLIB_PANIC_WITH_LOCATION ::hwlib::panic( __FILE__, __LINE__ )


// ===========================================================================
//
// implementations
//
// ===========================================================================

#ifdef _HWLIB_ONCE 

// The weak attribute allows an application 
// to specify its own panic function
void HWLIB_NORETURN HWLIB_WEAK panic( 
   const char * file, 
   const uint_fast16_t line 
){
   for(;;);
}

#endif // #ifdef _HWLIB_ONCE

}; // namespace hwlib
