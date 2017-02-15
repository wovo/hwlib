// ==========================================================================
//
// File      : hwlib-adc.hpp
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

#ifndef HWLIB_ADC_H
#define HWLIB_ADC_H

#include "hwlib-panic.hpp"

namespace hwlib {

/// \brief
/// A/D input interface
/// \details
/// This class abstracts the interface to an ADC (Analog to Digital Converter).
class adc {
public:

   /// the number of bits in the result returned by get()
   const uint_fast8_t adc_n_bits;
   
   /// the type of the result returned by get()
   typedef uint_fast32_t adc_value_type; 
    
   /// \brief
   /// do an A/D conversion and return the result
   /// \details
   /// This function performs an A/D conversion and returns the result.
   /// The lower n_bits of the result are the conversion result,
   /// the remaining higher bits are 0.
   virtual adc_value_type get() = 0;
   
   /// specify the number of bits
   adc( uint_fast8_t n_bits ): adc_n_bits{ n_bits }{
      if( n_bits > static_cast<int>( 8 * sizeof( adc_value_type ))){
         // the number of bits won't fit in the return type of get()
         HWLIB_PANIC_WITH_LOCATION;
      }
   }

};

}; // namespace hwlib

#endif // HWLIB_ADC_H