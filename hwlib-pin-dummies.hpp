// ==========================================================================
//
// File      : hwlib-pin-dummies.hpp
// Part of   : hwlib library for V1OOPC and V1IPAS
// Copyright : wouter@voti.nl 2016
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================
/// @file

#ifndef HWLIB_PIN_DUMMIES_H
#define HWLIB_PIN_DUMMIES_H

#include "hwlib-pin.hpp"

namespace hwlib {

/// a dummy (do-nothing) pin_in
class _pin_in_dummy_class : public pin_in {
public:
   bool get() override { return 0; }
};   
_pin_in_dummy_class HWLIB_WEAK pin_in_dummy;


/// a dummy (do-nothing) pin_out
class _pin_out_dummy_class : public pin_out {
public:
   void set( bool v ) override {}
};   
HWLIB_WEAK _pin_out_dummy_class pin_out_dummy;


/// a dummy (do-nothing) pin_in_out
class _pin_in_out_dummy_class : public pin_in_out {
public:
   void set( bool v ) override {}
   bool get() override { return 0; }
   void direction_set_input() override {}
   void direction_set_output() override{}
};   
HWLIB_WEAK _pin_in_out_dummy_class pin_in_out_dummy;


/// a dummy (do-nothing) pin_oc
class _pin_oc_dummy_class : public pin_oc {
public:
   void set( bool v ) override {}
   bool get() override { return 0; }
};   
HWLIB_WEAK _pin_oc_dummy_class pin_oc_dummy;

}; // namespace hwlib

#endif // HWLIB_PIN_DUMMIES_H