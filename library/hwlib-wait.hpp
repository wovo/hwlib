// ==========================================================================
//
// File      : hwlib-wait.hpp
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

#ifndef HWLIB_WAIT_H
#define HWLIB_WAIT_H

#include <stdint.h>

namespace hwlib {

/// \brief
/// delay n nanoseconds
/// \details
/// A call of this function will take (at least) n nanoseconds.
/// The value of n must be in the range 0 to 999999999 (up to 1 second).
/// For longer delays the function wait_ms() can be used.
///
/// Note that there is no guaranteed upper bound on the delay time.
///
/// When used with an RTOS, this function might switch the CPU 
/// to another task. Use wait_ns_busy() when this is not acceptable.
void wait_ns( int_fast32_t n );

/// \brief
/// delay n nanoseconds, without thread switching
/// \details
/// A call of this function will take (at least) n nanoseconds.
/// The value of n must be in the range 0 to 999999999 (up to 1 second).
/// For longer delays the function wait_ms() can be used.
///
/// Note that there is no guaranteed upper bound on the delay time.
///
/// Use this function only when the delay must be implemented without
/// task switching. In all other cases, use wait_ns().
void wait_ns_busy( int_fast32_t n );

/// \brief
/// delay n microseconds.
/// \details
/// A call of this function will take (at least) n microseconds.
/// The value of n must be in the range 0 to 999999 (up to 1 second).
/// For longer delays the function wait_ms() can be used.
///
/// Note that there is no guaranteed upper bound on the delay time.
///
/// When used with an RTOS, this function might switch the CPU 
/// to another task. Use wait_us_busy() when this is not acceptable.
void wait_us( int_fast32_t n );

/// \brief
/// delay n microseconds.
/// \details
/// A call of this function will take (at least) n microseconds.
/// The value of n must be in the range 0 to 999999 (up to 1 second).
/// For longer delays the function wait_ms() can be used.
///
/// Note that there is no guaranteed upper bound on the delay time.
///
/// Use this function only when the delay must be implemented without
/// task switching. In all other cases, use wait_us().
void wait_us_busy( int_fast32_t n );

/// \brief
/// delay n milliseconds.
/// \details
/// A call of this function will take (at least) n milliseconds.
///
/// Note that there is no guaranteed upper bound on the delay time.
///
/// When used with an RTOS, this function might switch the CPU 
/// to another task. Use wait_ms_busy() when this is not acceptable.
void wait_ms( int_fast32_t n );

/// \brief
/// delay n milliseconds.
/// \details
/// A call of this function will take (at least) n milliseconds.
///
/// Note that there is no guaranteed upper bound on the delay time.
///
/// Use this function only when the delay must be implemented without
/// task switching. In all other cases, use wait_ms().
void wait_ms_busy( int_fast32_t n );

/// \brief
/// current time in microseconds.
/// \details
/// A call of this function returns the number of microseconds since
/// some arbitrary moment (in most cases the first call to this function).
uint_fast64_t now_us();

/// \brief
/// current time in clock ticks.
/// \details
/// A call of this function returns the number of clock ticks since
/// some arbitrary moment (in most cases the first call to this function).
uint_fast64_t now_ticks();

/// \brief
/// clock ticks per microsecond.
/// \details
/// A call of this function returns the number of clock ticks 
/// (as returned by a now_ticks() call) per microsecond.
uint_fast64_t ticks_per_us();

#ifdef HWLIB_ONCE

// The default wait_xx functions call the wait_xx_busy functions.
// An RTOS can override these defaults.`

/* - disabled for emBO
void HWLIB_WEAK wait_ns( int_fast32_t n ){
   wait_ns_busy( n );
}

void HWLIB_WEAK wait_us( int_fast32_t n ){
   wait_us_busy( n );
}

void HWLIB_WEAK wait_ms( int_fast32_t n ){
   wait_ms_busy( n );
}

// The wait_xx_busy functions can be implemented by the targets,
// but only the wait_us_busy() function *must* be implemented.

void HWLIB_WEAK wait_ns_busy( int_fast32_t n ){
   wait_us_busy( ( n + 999 ) / 1000 );
}

void HWLIB_WEAK wait_ms_busy( int_fast32_t n ){
   while( n > 0 ){
      wait_us_busy( 1000 );
      --n;
   }   
}  
*/

#endif

}; // namespace hwlib

#endif // HWLIB_WAIT_H
