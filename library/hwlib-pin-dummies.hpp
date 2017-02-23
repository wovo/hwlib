// ==========================================================================
//
// File      : hwlib-pin-dummies.hpp
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

#ifndef HWLIB_PIN_DUMMIES_H
#define HWLIB_PIN_DUMMIES_H

#include "hwlib-pin.hpp"

namespace hwlib {
    
/// a dummy (do-nothing) pin_in_out class
class _pin_in_out_dummy_class : public pin_in_out {
public:
   void set( bool v, buffering buf = buffering::unbuffered ) override {}
   bool get( buffering buf = buffering::unbuffered ) override { return 0; }
   void direction_set_input() override {}
   void direction_set_output() override{}
};  

/// a dummy (do-nothing) pin_in class
class _pin_in_dummy_class : public pin_in {
public:
   bool get( buffering buf = buffering::unbuffered ) override { return 0; }
};   

/// a dummy (do-nothing) pin_out class
class _pin_out_dummy_class : public pin_out {
public:
   void set( bool v, buffering buf = buffering::unbuffered  ) override {}
};   

/// a d/ a dummy (do-nothing) pin_oc class
class _pin_oc_dummy_class : public pin_oc {
public:
   void set( bool v, buffering buf = buffering::unbuffered ) override {}
   bool get( buffering buf = buffering::unbuffered ) override { return 0; }
   
};   

/// a dummy (do-nothing) pin_in_out 
extern _pin_in_out_dummy_class  pin_in_out_dummy;

/// a dummy (do-nothing) pin_in 
extern _pin_in_dummy_class      pin_in_dummy;

/// a dummy (do-nothing) pin_out
extern _pin_out_dummy_class     pin_out_dummy;

/// a d/ a dummy (do-nothing) pin_oc
extern _pin_oc_dummy_class      pin_oc_dummy;

#ifdef HWLIB_ONCE

_pin_in_out_dummy_class  pin_in_out_dummy;
_pin_in_dummy_class      pin_in_dummy;
_pin_out_dummy_class     pin_out_dummy;
_pin_oc_dummy_class      pin_oc_dummy;

#endif // HWLIB_ONCE

}; // namespace hwlib

#endif // HWLIB_PIN_DUMMIES_H