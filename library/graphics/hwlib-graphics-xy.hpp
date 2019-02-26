// ==========================================================================
//
// File      : hwlib-graphics-xy.hpp
// Part of   : C++ hwlib library for close-to-the-hardware OO programming
// Copyright : wouter@voti.nl 2017
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

/// an xy pair 
/// 
/// This class abstracts an (at least 16 bit) integer pair.
/// It is used for instance for the size of a graphics screeen, and
/// to identify a single pixel location,
/// or the distance between two locations.
class location final {
public:
   /// x value of the location
   uint_fast16_t x;
   
   /// y value of the location
   uint_fast16_t y;
   
   /// construct from its x and y values
   constexpr location( uint_fast16_t x, uint_fast16_t y ): x{ x }, y{ y }{}
   
   /// default constructor, zero's the x and y
   constexpr location():x{0}, y{0}{}

   /// add two 
   constexpr location operator+( const location rhs ) const {
      return location{ 
          static_cast< uint_fast16_t >( x + rhs.x ),
          static_cast< uint_fast16_t >( y + rhs.y )
      };      
   }      
   
   /// subtract two 
   constexpr location operator-( const location rhs ) const {
      return location{ 
          static_cast< uint_fast16_t >( x - rhs.x ),
          static_cast< uint_fast16_t >( y - rhs.y )
      };         
   }      

   /// divide by an integer
   constexpr location operator/( const uint_fast16_t rhs ) const {
      return location{ 
          static_cast< uint_fast16_t >( x / rhs ),
          static_cast< uint_fast16_t >( y / rhs )
      };         
   }      

}; 

/// print an xy pair
///
/// An xy pair is printed in [x,y] format
ostream & operator<<( ostream & lhs, location rhs );
#ifdef HWLIB_ONCE
ostream & operator<<( ostream & lhs, location rhs ){
   return lhs << "[" << rhs.x << ":" << rhs.y << "]";
}
#endif

}; // namespace hwlib
