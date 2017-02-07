// ==========================================================================
//
// File      : hwlib-panic.hpp
// Part of   : hwlib library for V1OOPC and V1IPAS
// Copyright : wouter@voti.nl 2016
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================
/// @file

#ifndef HWLIB_PANIC_H
#define HWLIB_PANIC_H

#include "hwlib-defines.hpp"

namespace hwlib {

/// panic function for irrecoverable errors
//
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
/// \snippet "due\panic\main.cpp" [Doxygen panic example]
///
void HWLIB_NORETURN HWLIB_WEAK panic( const char * file, int line );

/// convenience panic macro 
//
/// This macro calls panic( __FILE__, __LINE__ ).
#define HWLIB_PANIC_WITH_LOCATION ::hwlib::panic( __FILE__, __LINE__ )

}; // namespace hwlib

#endif // HWLIB_PANIC_H