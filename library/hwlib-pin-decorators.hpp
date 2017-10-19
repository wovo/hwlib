// ==========================================================================
//
// File      : hwlib-pin-decorators.hpp
// Part of   : C++ hwlib library for close-to-the-hardware OO programming
// Copyright : wouter@voti.nl 2017
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

// this file contains Doxygen linesd
/// @file

#ifndef HWLIB_PIN_DECORATORS_H
#define HWLIB_PIN_DECORATORS_H

#include "hwlib-pin.hpp"

namespace hwlib {
	
class pin_out_from_oc : public pin_out {
   pin_oc & slave;
   
public:
   pin_out_from_oc( pin_oc & slave ): slave( slave ){}
   
   void set( 
      bool x, 
      buffering buf = buffering::unbuffered 
   ){
      slave.set( x, buf );
   }	  
};	

}; // namespace hwlib

#endif // HWLIB_PIN_DECORATORS_H