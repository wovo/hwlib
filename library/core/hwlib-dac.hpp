// ==========================================================================
//
// File      : hwlib-dac.hpp
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

/// D/A output interface
///
/// This class abstracts the interface to a DAC (Digital to Analog Converter).
class dac : public noncopyable {
public:

   /// the number of bits in the result returned by write()
   const uint_fast8_t dac_n_bits;
   
   /// the maximum value that can be returned by write()
   const uint_fast8_t dac_max_value;
   
   /// the type of the result returned by write()
   typedef uint_fast32_t dac_value_type; 
    
   /// write a value to the D/A output 
   /// 
   /// This writes a digital value to the D/A converter, which causes
   /// the corresponding analog value to appear on the output pin.
   ///
   /// The actual effect on the pin might be postponed until the
   /// next flush() call.   
   virtual void write( dac_value_type x ) = 0;
 
   /// flush the write buffer
   /// 
   /// This function flushes the write buffer: if the buffered value
   /// has not yet been written it is written to the pin.
   /// When the value has been written, it might be written again.
   ///
   /// The pin write buffer might also be flushed as a side-effect of 
   /// other operations.    
   virtual void flush() = 0;
   
   /// specify the number of bits
   dac( uint_fast8_t n_bits ): \
      dac_n_bits{ n_bits },
      dac_max_value( static_cast< dac_value_type >( ( 1 << n_bits ) - 1 ))
   {
      if( dac_n_bits > static_cast<int>( 8 * sizeof( dac_value_type ))){
         // the number of bits won't fit in the return type of read()
         HWLIB_PANIC_WITH_LOCATION;
      }
   }

}; // class dac

}; // namespace hwlib
