// ==========================================================================
//
// File      : hwlib-adc.hpp
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

/// A/D input interface
///
/// This class abstracts the interface to an ADC (Analog to Digital Converter).
class adc : public noncopyable {
public:

   /// the number of bits in the result returned by read()
   const uint_fast8_t adc_n_bits;
   
   /// the type of the result returned by read()
   typedef uint_fast32_t adc_value_type; 
   
   /// the maximum value that can be meaningfully written using write())
   const adc_value_type adc_max_value;   

   /// do an A/D conversion and return the result
   /// 
   /// This function performs an A/D conversion and returns the result.
   /// The lower n_bits of the result are the conversion result,
   /// the remaining higher bits are 0.
   virtual adc_value_type read() = 0;
   
   /// specify the number of bits
   adc( uint_fast8_t n_bits ): 
      adc_n_bits{ n_bits },
      adc_max_value( ( static_cast< adc_value_type >( 1 ) << n_bits ) - 1 )
   {
      if( n_bits > static_cast<int>( 8 * sizeof( adc_value_type ))){
         // the number of bits won't fit in the return type of read()
         HWLIB_PANIC_WITH_LOCATION;
      }
   }
   
   /// refresh the adc value
   /// 
   /// This function refreshes the contents of the read buffer that might
   /// be used by a buffered read().
   ///
   /// That buffer might also be refreshed as a side-effect of other
   /// operations.  
   virtual void refresh() = 0;
   
}; // class adc

}; // namespace hwlib
