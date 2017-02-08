// ==========================================================================
//
// File      : hwlib-panic.cpp
// Part of   : C++ hwlib library for close-to-the-hardware OO programming
// Copyright : wouter@voti.nl 2017
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

// this file contains Doxygen lines
/// @file

#include "hwlib-panic.hpp"

namespace hwlib {

// The weak attribute allows an application to specify its own panic function,
// and allows the inclusion of this header in more than one compilation unit.
//
// This function must be in a .cpp because otherwise it would
// (when it is overruled by an application-defined alternative)
// be defined twice *in one compilation unit*.
void  __attribute__ (( weak )) panic( const char * file, uint_fast32_t line ){
   for(;;);
}

}; // namespace hwlib
