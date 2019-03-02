// ==========================================================================
//
// File      : hwlib-demos.hpp
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

/// blink function
/// 
/// This function blinks the pin: ms milliseconds on, and
/// ms milliseconds off. It never returns.
void blink( pin_out & pin, uint_fast16_t  ms = 200 );

/// @copydoc blink( pin_out & pin, uint_fast16_t  ms = 200 );
void blink( pin_oc & pin, uint_fast16_t  ms = 200 );

/// @copydoc blink( pin_out & pin, uint_fast16_t  ms = 200 );
void blink( pin_in_out & pin, uint_fast16_t  ms = 200 );


// ===========================================================================
//
// implementations
//
// ===========================================================================

#ifdef _HWLIB_ONCE 

void HWLIB_NORETURN blink( pin_out & pin, uint_fast16_t ms ){
   for(;;){
      pin.write( 1 );
	  pin.flush();
      wait_ms( ms );   
	  
      pin.write( 0 );
	  pin.flush();
      wait_ms( ms );      
   }      
}

void HWLIB_NORETURN blink( pin_in_out & pin, uint_fast16_t ms ){
   auto p = pin_out_from( pin );
   blink( p, ms );   
}

void HWLIB_NORETURN blink( pin_oc & pin, uint_fast16_t ms ){
   auto p = pin_out_from( pin );
   blink( p, ms );   
}

#endif // #ifdef _HWLIB_ONCE

}; // namespace hwlib
