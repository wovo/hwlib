// ==========================================================================
//
// File      : hwlib-stm32f103c8.hpp
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

#ifndef HWLIB_BLUE_PILL_H
#define HWLIB_BLUE_PILL_H

#include HWLIB_INCLUDE(../hwlib-all.hpp)

namespace stm32f1xx {
   
/// GPIO pin names
   enum class pins {
      a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15,
      b0, b1, b2, b3, b4, b5, b6, b7, b8, b9, b10, b11, b12, b13, b14, b15,
      c0, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12, c13, c14, c15,
      led,
/// \cond INTERNAL    
      SIZE_THIS_IS_NOT_A_PIN
/// \endcond   
   };

/// \cond INTERNAL    
   struct pin_info_type {
      uint8_t port;
      uint8_t pin;
   };

    const HWLIB_WEAK pin_info_type &pin_info(pins name) {

      static const pin_info_type pin_info_array[ (int) pins::SIZE_THIS_IS_NOT_A_PIN ] = {
         { 0,  0 },  // a0
         { 0,  1 },  // a1
         { 0,  2 },  // a2
         { 0,  3 },  // a3
         { 0,  4 },  // a4
         { 0,  5 },  // a5
         { 0,  6 },  // a6
         { 0,  7 },  // a7

         { 0,  8 },  // a8
         { 0,  9 },  // a9
         { 0, 10 },  // a10
         { 0, 11 },  // a11
         { 0, 12 },  // a12
         { 0, 13 },  // a13
         { 0, 14 },  // a14
         { 0, 15 },  // a15

         { 1,  0 },  // b0
         { 1,  1 },  // b1
         { 1,  2 },  // b2
         { 1,  3 },  // b3
         { 1,  4 },  // b4
         { 1,  5 },  // b5
         { 1,  6 },  // b6
         { 1,  7 },  // b7
 
         { 1,  8 },  // b8
         { 1,  9 },  // b9
         { 1, 10 },  // b10
         { 1, 11 },  // b11
         { 1, 12 },  // b12
         { 1, 13 },  // b13
         { 1, 14 },  // b14
         { 1, 15 },  // b15

         { 2,  0 },  // c0
         { 2,  1 },  // c1
         { 2,  2 },  // c2
         { 2,  3 },  // c3
         { 2,  4 },  // c4
         { 2,  5 },  // c5
         { 2,  6 },  // c6
         { 2,  7 },  // c7

         { 2,  8 },  // c8
         { 2,  9 },  // c9
         { 2, 10 },  // c10
         { 2, 11 },  // c11
         { 2, 12 },  // c12
         { 2, 13 },  // c13
         { 2, 14 },  // c14
         { 2, 15 },  // c15

         { 2, 13 }   // led

      };

      uint_fast8_t n = static_cast< uint_fast8_t>( name );
      if (n >= static_cast< uint_fast8_t>( pins::SIZE_THIS_IS_NOT_A_PIN )) {
          HWLIB_PANIC_WITH_LOCATION;
      }
      return pin_info_array[ n ];

   }
    
/// \endcond      

}; // end namespace stm32f1xx 

#include HWLIB_INCLUDE( hwlib-stm32f1xx.hpp )

namespace stm32f103c8 = ::stm32f1xx;   

namespace hwlib {

   namespace target = ::stm32f103c8;
   const auto target_chip = target_chips::stm32f103c8;
   const auto target_board = target_boards::blue_pill;
    
};    

#endif // #ifdef HWLIB_BLUE_PILL_H
