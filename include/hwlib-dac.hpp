// ==========================================================================
//
// File      : hwlib-dac.hpp
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

#ifndef HWLIB_DAC_H
#define HWLIB_DAC_H

#include "hwlib-panic.hpp"

namespace hwlib {

/// \brief
/// D/A output interface
/// \details
/// This class abstracts the interface to a DAC (Digital to Analog Converter).
class dac {
public:

   /// the number of bits in the result returned by get()
   const uint_fast8_t dac_n_bits;
   
   /// the maximum value that can be returned by get()
   const uint_fast8_t dac_max_value;
   
   /// the type of the result returned by get()
   typedef uint_fast32_t dac_value_type; 
    
   /// \brief
   /// write a value to the D/A output 
   /// \details
   /// This writes a digital value to the D/A converter, which causes
   /// the corresponding analog value to appear on the output pin.
   virtual void set( dac_value_type x ) = 0;
   
   /// specify the number of bits
   dac( uint_fast8_t n_bits ): \
      dac_n_bits{ n_bits },
      dac_max_value( static_cast< dac_value_type >( ( 1 << n_bits ) - 1 ))
   {
      if( dac_n_bits > static_cast<int>( 8 * sizeof( dac_value_type ))){
         // the number of bits won't fit in the return type of get()
         HWLIB_PANIC_WITH_LOCATION;
      }
   }

};

}; // namespace hwlib

#endif // HWLIB_DAC_H