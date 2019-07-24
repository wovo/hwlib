// ==========================================================================
//
// File      : hwlib-wait.hpp
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


/// delay n nanoseconds
///
/// A call of this function will take (at least) n nanoseconds.
/// The value of n must be in the range 0 to 999999999 (up to 1 second).
/// For longer delays the function wait_ms() can be used.
///
/// Note that there is no guaranteed upper bound on the delay time.
///
/// When used with an RTOS, this function might switch the CPU 
/// to another task. Use wait_ns_busy() when this is not acceptable.
void wait_ns( int_fast32_t n );


/// delay n nanoseconds, without thread switching
///
/// A call of this function will take (at least) n nanoseconds.
/// The value of n must be in the range 0 to 999999999 (up to 1 second).
/// For longer delays the function wait_ms() can be used.
///
/// Note that there is no guaranteed upper bound on the delay time.
///
/// Use this function only when the delay must be implemented without
/// task switching. In all other cases, use wait_ns().
void wait_ns_busy( int_fast32_t n );


/// delay n microseconds
///
/// A call of this function will take (at least) n microseconds.
/// The value of n must be in the range 0 to 999999 (up to 1 second).
/// For longer delays the function wait_ms() can be used.
///
/// Note that there is no guaranteed upper bound on the delay time.
///
/// When used with an RTOS, this function might switch the CPU 
/// to another task. Use wait_us_busy() when this is not acceptable.
void wait_us( int_fast32_t n );


/// delay n microseconds, without thread switching
///
/// A call of this function will take (at least) n microseconds.
/// The value of n must be in the range 0 to 999999 (up to 1 second).
/// For longer delays the function wait_ms() can be used.
///
/// Note that there is no guaranteed upper bound on the delay time.
///
/// Use this function only when the delay must be implemented without
/// task switching. In all other cases, use wait_us().
void wait_us_busy( int_fast32_t n );


/// delay n milliseconds
///
/// A call of this function will take (at least) n milliseconds.
///
/// Note that there is no guaranteed upper bound on the delay time.
///
/// When used with an RTOS, this function might switch the CPU 
/// to another task. Use wait_ms_busy() when this is not acceptable.
void wait_ms( int_fast32_t n );


/// delay n milliseconds, without thread switching
///
/// A call of this function will take (at least) n milliseconds.
///
/// Note that there is no guaranteed upper bound on the delay time.
///
/// Use this function only when the delay must be implemented without
/// task switching. In all other cases, use wait_ms().
void wait_ms_busy( int_fast32_t n );


/// \brief
/// current time in microseconds
///
/// A call of this function returns the number of microseconds since
/// some arbitrary moment (in most cases the first call to this function).
uint_fast64_t now_us();


/// current time in clock ticks
///
/// A call of this function returns the number of clock ticks since
/// some arbitrary moment (in most cases the first call to this function).
uint_fast64_t now_ticks();


/// clock ticks per microsecond
///
/// A call of this function returns the number of clock ticks 
/// (as returned by a now_ticks() call) per microsecond.
uint_fast64_t ticks_per_us();


// ===========================================================================
//
// implementations
//
// ===========================================================================

// must be provided by the target implementation

}; // namespace hwlib
