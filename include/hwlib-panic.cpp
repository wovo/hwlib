// ==========================================================================
//
// File      : hwlib-panic.cpp
// Part of   : hwlib library for V1OOPC and V1IPAS
// Copyright : wouter@voti.nl 2016
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#include "hwlib-panic.hpp"

namespace hwlib {

// The weak attribute allows an application to specify its own panic function,
// and allows the inclusion of this header in more than one compilation unit.
//
// This function must be in a .cpp because otherwise it would
// (when it is overruled by an application-defined alternative)
// be defined twice *in one compilation unit*.
void  __attribute__ (( weak )) panic( const char * file, int line ){
   for(;;);
}

}; // namespace hwlib
