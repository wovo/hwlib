// ==========================================================================
//
// File      : hwlib-ratio.hpp
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
   
/// ratio ADT
template< typename T = int_fast32_t >
class ratio {
public:	

   /// multiplier
   T m;
   
   /// divisor
   T d;
   
   /// reduce the ratio
   ///
   /// Calling this function reduces the ration
   /// to its canonical form by eliminiating
   /// the common divisors.
   ///
   /// A ratio is always assumed to be in its canonical form.
   /// The ratio member functions call this function when needed.
   /// As a user, you must call this function after writing to the 
   /// m and/or n members.
   void reduce(){
      auto g = std::gcd( m, d );
      m = m / g;
      d = d / g;
   }
   
   /// construct a ratio
   constexpr ratio( int m = 0, int d = 1 ): 
      m( m ), d( d )
   {
      reduce();
   }
   
   /// multiply by a value, yields a value
   ///
   /// Multiplying a ration by a value yields
   /// the ratio of the value.
   ///
   /// For intance: ratio( 1, 4 ) * 5.0 yields 1.25
   template< typename U >
   constexpr U operator*( const U & rhs ) const {
      return ( rhs * m ) / d;
   }
   
   /// add two ratio's
   constexpr ratio operator+( const ratio & rhs ) const {
      return ratio( ( m * rhs.d ) + ( rhs.m * d ), d * rhs.d );
   }
         
   /// subtract two ratio's
   constexpr ratio operator-( const ratio & rhs ) const {
      return ratio( ( m * rhs.d ) - ( rhs.m * d ), d * rhs.d ); 
   }
         
};

/// multiply a value by a ratio, yeilds a ration
///
/// Multiplying a ration by a value yields
/// the ratio of the value.
///
/// For intance: 3 * ratio( 1, 4 ) yields ratio( 3, 4 )
template< typename T, typename U >
constexpr ratio< U > operator*( const T & lhs, const ratio< U > & rhs ){
   return ratio( lhs.m * rhs, lhs.d );
}

/// print a ratio
template< typename T, typename U >
T & operator<< ( const T & lhs, const ratio< U > & rhs ){
   lhs << "(" << rhs.m << "/" << rhs.d << ")";
   return lhs;
}

}; // namespace hwlib
