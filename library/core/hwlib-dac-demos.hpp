// ==========================================================================
//
// File      : hwlib-demo.hpp
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

/// \brief
/// dac triangle waveform demo
/// \details
/// This functions outputs a triangle waveform on the DAC outpout,
/// with step_ms milliseconds between each step.
void dac_triangle( dac & d, uint_fast16_t step_ms = 10 );


// ===========================================================================
//
// implementations
//
// ===========================================================================

#ifdef _HWLIB_ONCE 

void HWLIB_NORETURN dac_triangle( dac & d, uint_fast16_t step_ms ){
   for(;;){
      for( dac::dac_value_type i = 0; i <= d.dac_max_value; ++i ){
          d.write( i );
          wait_ms( step_ms );
      }
      for( dac::dac_value_type i = d.dac_max_value; i >= 0; --i ){
          d.write( i );
          wait_ms( step_ms );
      }
   }
}   

#endif // #ifdef _HWLIB_ONCE

}; // namespace hwlib
