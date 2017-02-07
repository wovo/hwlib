// ==========================================================================
//
// File      : hwlib-dac.hpp
// Part of   : hwlib library for V1OOPC and V1IPAS
// Copyright : wouter@voti.nl 2016
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================
/// @file

#ifndef HWLIB_DAC_H
#define HWLIB_DAC_H

#include "hwlib-panic.hpp"

namespace hwlib {

/// D/A output interface
//
/// This class abstracts the interface to a DAC (Digital to Analog Converter).
class dac {
public:

   /// the number of bits in the result returned by get()
   const int dac_n_bits;
   
   /// the type of the result returned by get()
   typedef unsigned int dac_value_type; 
    
   /// write a value to the D/A output 
   //
   /// This writes a digital value to the D/A converter, which causes
   /// the corresponding analog value to appear on the output pin.
   virtual void set( dac_value_type x ) = 0;
   
   /// specify the number of bits
   dac( int n_bits ): dac_n_bits{ n_bits }{
      if( dac_n_bits > static_cast<int>( 8 * sizeof( dac_value_type ))){
         // the number of bits won't fit in the return type of get()
         HWLIB_PANIC_WITH_LOCATION;
      }
   }

};

}; // namespace hwlib

#endif // HWLIB_DAC_H