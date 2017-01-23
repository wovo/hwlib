// ==========================================================================
//
// File      : hwlib-wait.hpp
// Part of   : hwlib library for V1OOPC and V1IPAS
// Copyright : wouter@voti.nl 2016
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================
/// @file

#ifndef HWLIB_WAIT_H
#define HWLIB_WAIT_H

#include <stdint.h>

namespace hwlib {

/// delay n nanoseconds
//
/// A call of this function will take (at least) n nanoseconds.
/// The value of n must be in the range 0 to 999999999 (up to 1 second).
/// For longer delays the function wait_ms() can be used.
///
/// Note that there is no guaranteed upper bound on the delay time.
void wait_ns( int_fast32_t n );

/// delay n microseconds.
//
/// A call of this function will take (at least) n microseconds.
/// The value of n must be in the range 0 to 999999 (up to 1 second).
/// For longer delays the function wait_ms() can be used.
///
/// Note that there is no guaranteed upper bound on the delay time.
void wait_us( int_fast32_t n );

/// delay n milliseconds.
//
/// A call of this function will take (at least) n milliseconds.
///
/// Note that there is no guaranteed upper bound on the delay time.
void wait_ms( int_fast32_t n );

/// current time in microseconds.
//
/// A call of this function returns the number of microseconds since
/// some arbitrary moment (in most cases the first call to this function).
long long int now_us();

}; // namespace hwlib

#endif // HWLIB_WAIT_H
