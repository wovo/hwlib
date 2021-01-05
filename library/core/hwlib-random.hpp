// ==========================================================================
//
// File      : hwlib-random.hpp
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

/// random chain value
/// 
/// This value is used to derive the next random value.
/// It is initially 0, so each run of an application
/// will get the same sequence of 'random' numbers.
///
/// To get a random chain of random numbers, set this variable
/// to a random number, for instance from an A/D converter, or
/// from timing a user action.
extern uint_fast32_t random_chain_value;

/// 32-bit random value
/// 
/// This functions returns a 32 bit (pseudo-) random
/// value, derived from random_chain_value.
uint_fast32_t HWLIB_WEAK rand();

/// random value in a range
/// 
/// This functions returns a random value in the specified range,
/// which includes the specified min and max values.
///
/// The value is derived from rand() by modulo calculation,
/// so the randomness will be somewhat skewed.
uint_fast32_t HWLIB_WEAK random_in( 
   uint_fast32_t min, 
   uint_fast32_t max 
);

/// random location in an xy range
/// 
/// This functions returns a random value within the specified xy range,
/// which excludes the xy.x and xy.y values.
///
/// The values are derived from rand() by modulo calculation,
/// so the randomness will be somewhat skewed.
xy HWLIB_WEAK random_in( 
   const xy & limit
);


// ===========================================================================
//
// implementations
//
// ===========================================================================

#ifdef _HWLIB_ONCE

uint_fast32_t random_chain_value = 0;

uint_fast32_t rand(){ 
   return random_chain_value = 1103515245L * random_chain_value + 12345L;
}

uint_fast32_t random_in( 
   uint_fast32_t min, 
   uint_fast32_t max 
){
   return min + ( rand() % ( max - min + 1 ) ); 
}

xy HWLIB_WEAK random_in( 
   const xy & limit
){
   return xy( 
      random_in( 0, limit.x - 1 ),
      random_in( 0, limit.y - 1 )  
   );      
}

#endif // #ifdef _HWLIB_ONCE

}; // namespace hwlib
