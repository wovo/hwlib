// ==========================================================================
//
// File      : hwlib-graphics-font.hpp
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

/// a font
/// 
/// A font provides an image for each supported character
class font : public noncopyable {
public:

   /// get image for a character
   /// 
   /// This function returns the image for the specified character.
   virtual const image & operator[]( char c ) const = 0;
};

}; // namespace hwlib
