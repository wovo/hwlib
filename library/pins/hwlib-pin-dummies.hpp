// ==========================================================================
//
// File      : hwlib-pin-dummies.hpp
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
    
	
/// a dummy (do-nothing) pin_in_out class
class pin_in_out_dummy_t : public pin_in_out {
public:
   void write( bool v ) override {}
   bool read() override { return 0; }
   void direction_set_input() override {}
   void direction_set_output() override {}
   void flush() override {}
   void refresh() override {}
   void direction_flush() override {}
};  


/// a dummy (do-nothing) pin_in class
class pin_in_dummy_t : public pin_in {
public:
   bool read() override { return 0; }
   void refresh() override {}
};   


/// a dummy (do-nothing) pin_out class
class pin_out_dummy_t : public pin_out {
public:
   void write( bool v ) override {}
   void flush() override {}
};   


/// a dummy (do-nothing) pin_oc class
class pin_oc_dummy_t : public pin_oc {
public:
   void write( bool v ) override {}
   bool read() override { return 0; }
   void flush() override {}
   void refresh() override {}   
};   


/// a dummy (do-nothing) pin_in_out object
extern pin_in_out_dummy_t  pin_in_out_dummy;

/// a dummy (do-nothing) pin_in object
extern pin_in_dummy_t      pin_in_dummy;

/// a dummy (do-nothing) pin_out object
extern pin_out_dummy_t     pin_out_dummy;

/// a dummy (do-nothing) pin_oc object
extern pin_oc_dummy_t      pin_oc_dummy;


// ===========================================================================
//
// implementations
//
// ===========================================================================

#ifdef _HWLIB_ONCE

pin_in_out_dummy_t  pin_in_out_dummy;
pin_in_dummy_t      pin_in_dummy;
pin_out_dummy_t     pin_out_dummy;
pin_oc_dummy_t      pin_oc_dummy;

#endif // _HWLIB_ONCE

}; // namespace hwlib
