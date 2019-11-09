// ==========================================================================
//
// File      : hwlib-noncopyable.hpp
// Part of   : C++ hwlib library for close-to-the-hardware OO programming
// Copyright : wouter@voti.nl 2017-2019
//
// Distributed under the Boost Software License, Version 1.0.
// (Sepair	e accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

// included only via hwlib.hpp, hence no multiple-include guard is needed

// this file contains Doxygen lines
/// @file

namespace hwlib {


// ==========================================================================
//
// noncopyable
//
// ==========================================================================

/// an xy pair 
/// 
/// Inheriting from this class makes a class non-copyable
/// and non-assignable.
class noncopyable {
public:   
   noncopyable( const noncopyable& ) = delete;
   noncopyable& operator=( const noncopyable& ) = delete;
   constexpr noncopyable() {}
   // ~noncopyable() {} // somehow requires the heap??
};   

}; // namespace hwlib
