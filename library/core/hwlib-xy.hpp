// ==========================================================================
//
// File      : hwlib-graphics-xy.hpp
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
// xy
//
// ==========================================================================

/// an xy pair 
/// 
/// This class abstracts an (at least 16 bit) integer pair.
/// It is used for instance for the size of a graphics or character screen,
/// and to identify a single pixel location,
/// or the distance between two pixel locations.
class xy final {
public:

   /// x value of the pair
   int_fast16_t x;
   
   /// y value of the pair
   int_fast16_t y;
   
   /// construct from its x and y values
   constexpr xy( int_fast16_t x, int_fast16_t y ): x{ x }, y{ y }{}
   
   /// default constructor, zero's the x and y
   constexpr xy():x{0}, y{0}{}

   /// add two 
   constexpr xy operator+( const xy rhs ) const {
      return xy{ 
          static_cast< int_fast16_t >( x + rhs.x ),
          static_cast< int_fast16_t >( y + rhs.y )
      };      
   }      
   
   /// subtract two 
   constexpr xy operator-( const xy rhs ) const {
      return xy{ 
          static_cast< int_fast16_t >( x - rhs.x ),
          static_cast< int_fast16_t >( y - rhs.y )
      };         
   }      

   /// divide by an integer
   constexpr xy operator/( const int_fast16_t rhs ) const {
      return xy{ 
          static_cast< int_fast16_t >( x / rhs ),
          static_cast< int_fast16_t >( y / rhs )
      };         
   }    

   /// multiply by an integer
   constexpr xy operator*( const int_fast16_t rhs ) const {
      return xy{ 
          static_cast< int_fast16_t >( x * rhs ),
          static_cast< int_fast16_t >( y * rhs )
      };         
   }    

   /// reverse multiply by an integer
   friend constexpr xy operator*( int n, const xy & rhs ){
      return rhs * n;
   }    

   /// test whether two xy values are equal
   constexpr bool operator==( const xy & rhs ) const {
      return ( x == rhs.x ) && ( y == rhs.y );
   }

   /// test whether two xy values are unequal
   constexpr bool operator!=( const xy & rhs ) const {
      return ! ( *this == rhs );
   }
   
   friend constexpr xy transpose( const xy & rhs ){
      return xy( rhs.y, rhs.x );      
   }      

}; 


// ==========================================================================
//
// iterator
//
// ==========================================================================

/// \cond INTERNAL

class xy_iterator_t {
private:

   xy limits;
   xy current;

public:

   xy_iterator_t( xy limits, xy current ): 
      limits( limits ), 
      current( current )
   {}

   xy operator*() const {
      return current;
   }

   void operator++(){
      ++current.x;
      if( current.x == limits.x ){
         current.x = 0;
         ++current.y;
      }
   }

   bool operator==( const xy_iterator_t rhs ) const {
      return current == rhs.current;
   }

   bool operator!=( const xy_iterator_t rhs ) const {
      return current != rhs.current;
   }
      
};

class xy_all_t {
private:

   xy limits;

public:

   xy_all_t( xy limits ):
      limits( limits )
   {}

   xy_iterator_t begin() const {
      return xy_iterator_t( limits, xy( 0 , 0 ) );
   }

   xy_iterator_t end() const {
      return xy_iterator_t( limits, xy( 0, limits.y ) );
   }

};

/// \endcond 

/// iterate over all values in an xy range
///
/// This function returns an object that can be used to iterate over
/// all values in the range [ 0 ... x-1 ] * [ 0 ... y-1 ].
///
/// \relates xy
class xy_all_t all( xy v );

/// print an xy pair
///
/// An xy pair is printed in [x,y] format
///
/// \relates xy
template< typename T >
T & operator<<( T & lhs, xy rhs ){
   return lhs << "[" << rhs.x << ":" << rhs.y << "]";
}


// ===========================================================================
//
// implementations
//
// ===========================================================================

#ifdef _HWLIB_ONCE

class xy_all_t all( xy v ){
   return xy_all_t( v );
}

#endif // #ifdef _HWLIB_ONCE

}; // namespace hwlib
