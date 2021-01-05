// ==========================================================================
//
// File      : hwlib-graphics-image.hpp
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


// ==========================================================================
//
// image
//
// ==========================================================================

/// an image
/// 
/// An image abstracts a rectangular set of pixel values (colors).
class image { // : public noncopyable { // gives problems
private:

   virtual color read_implementation( xy pos ) const = 0;

public:

   /// the size of the image
   /// 
   /// This is the size of the image: the number of pixels
   /// in the x and y direction.
   const xy size;

   /// construct an image by specifying its size.
   constexpr image( xy size )
      : size{ size }
   {}

   /// the color at the specified location
   
   color read( xy pos ) const {
      return (
               ( pos.x >= 0 ) && ( pos.x < size.x )
            && ( pos.y >= 0 ) && ( pos.y < size.y )
         )
            ? read_implementation( pos )
            : transparent;
   }

   /// the color at the specified location
   color operator[]( xy pos ) const {
      return read( pos );
   }
};


// ==========================================================================
//
// image_8x8
//
// ==========================================================================

/// an 8x8 pixel image that contains its pixels
class image_8x8 : public image {
private:
   unsigned char data[ 8 ];

   color read_implementation( xy pos ) const override {
      return
         ( data[ pos.y ] & ( 0x01 << pos.x )) == 0
            ? white
            : black;
   }

public:

   /// create the image_8x8 by supplying the pixels
   /// 
   /// The d0 argument contains the top row, bit 0 is the leftmost pixel.
   constexpr image_8x8(
      unsigned char d0, unsigned char d1,
      unsigned char d2, unsigned char d3,
      unsigned char d4, unsigned char d5,
      unsigned char d6, unsigned char d7
   ):
      image( xy( 8, 8 ) ),
      data{ d0, d1, d2, d3, d4, d5, d6, d7 }
   {}
};


}; // namespace hwlib
