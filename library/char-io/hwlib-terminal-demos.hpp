// ==========================================================================
//
// File      : hwlib-terminal-demo.hpp
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

/// scrolling text demo
/// 
/// This demo scrolls the text on the first line of the terminal.
/// Thye delays (in ms) are after showing the initial first part 
/// of the text, after scrolling oen character, 
/// and after showing the last part of the texr.
void scrolling_text( 
   terminal & term, 
   const char * text, 
   uint_fast16_t first_ms = 1'000,
   uint_fast16_t step_ms  = 300,
   uint_fast16_t last_ms  = 1'000 
);


// ===========================================================================
//
// implementations
//
// ===========================================================================

#ifdef _HWLIB_ONCE 

uint_fast16_t HWLIB_WEAK strlen( const char * s ){
   uint_fast16_t n = 0;
   while( *s != '\0' ){
      ++s;
      ++n;
   }
   return n;
}

void HWLIB_NORETURN scrolling_text( 
   terminal & term, 
   const char * text, 
   uint_fast16_t first_ms,
   uint_fast16_t step_ms,
   uint_fast16_t last_ms
){
   auto len = strlen( text );
   
   for(;;){
      for( uint_fast16_t i = 0; ( i + term.size.x ) <= len; ++i ){
         term << '\r';
         for( int_fast16_t j = 0; j < term.size.x; ++j ){
			 term << text[ i + j ];
		 }
		 term << flush;
		 wait_ms( i == 0 ? first_ms : step_ms );
      }		 
      wait_ms( last_ms );
   }	   
}

#endif // #ifdef _HWLIB_ONCE


}; // namespace hwlib
