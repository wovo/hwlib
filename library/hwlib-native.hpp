// ==========================================================================
//
// File      : hwlib-natuve.hpp
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

#ifndef HWLIB_NATIVE_H
#define HWLIB_NATIVE_H

#include "hwlib-all.hpp"
#include <Windows.h>

namespace hwlib {

#ifdef HWLIB_ONCE 

uint64_t now_ticks(){
   // https://stackoverflow.com/questions/1695288/getting-the-current-time-in-milliseconds-from-the-system-clock-in-windows	 
   FILETIME ft_now;
   GetSystemTimeAsFileTime( &ft_now );
   uint64_t ll_now = (LONGLONG)ft_now.dwLowDateTime + ((LONGLONG)(ft_now.dwHighDateTime) << 32LL);   
   return ll_now / 10;
}   

uint64_t ticks_per_us(){
   return 1;
}   

uint64_t now_us(){
   return now_ticks() / ticks_per_us();
}   

void wait_us_busy( int_fast32_t n ){
   auto end = now_us() + n;
   while( now_us() < end ){}
}

void wait_ns( int_fast32_t n ){ 
   wait_us_busy( 1 + n / 1'000 );
}

void wait_us( int_fast32_t n ){ 
   wait_us_busy( n );
}

void wait_ms( int_fast32_t n ){
   wait_us( 1'000 * n );
// why doesn't this work (asny more)??
/*
   while( n > 0 ){
      wait_us( 1'000 );
      --n;
   }
*/
}  

/*

void wait_ns( int_fast32_t n ){
   wait_us( n / 1'000 );
}

void wait_us( int_fast32_t n ){
   
}

void wait_ms( int_fast32_t n ){
   wait_us( n * 1'000 );
}

uint_fast64_t now_us(){
   return 0;
}   
 
*/

void uart_putc( char c ){}

char uart_getc(){
   return '?';   
}

bool HWLIB_WEAK uart_char_available(){
   return 0;
}



#endif // #ifdef HBLIB_ONCE

}; // namespace hwlib

#endif // HWLIB_NATIVE_H