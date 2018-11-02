// ==========================================================================
//
// File      : hwlib-string.hpp
// Part of   : C++ library for close-to-the-hardware OO programming
// Copyright : wouter@voti.nl 2017
//
// This code is partially based on a research project by Martin Broers.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

// this file contains Doxygen lines
/// @file

//#define HWLIB_STRING_H

#ifndef HWLIB_STRING_H
#define HWLIB_STRING_H

#include <stddef.h>
#include <type_traits>

namespace hwlib {

// forward declaration of the class template   
template< size_t maximum_length > class string;

// return the end iterator from an asciz string
constexpr const char * asciz_beyond( const char * p ){
   while( *p != '\0' ){
      ++p;
   }
   return p;
}

  
//============================================================================
//
// string< 0 >
//  
//============================================================================

/// \brief
/// abstract fixed-maximum-length string
/// \details  
/// This is a string class template with a fixed maximum length. 
/// The maximum length is the template parameter.
/// All such strings inherit from string< 0 >.
///
/// An attempt to add characters beyond the maximum length will ignore
/// the excess characters.
/// Accessing an invalid character by the operator[] will yield
/// an undefined character value, or a reference to a (hidden) static
/// character.
///
/// This string is meant for small micro-controller applications.
/// It doesn't use the heap, RTTI, exceptions, virtuals or recursion.
/// It was assumed that this class will be used in the not-time-critical
/// part of the application, hence the implementation leans towards small
/// code size, not maximum speed.
///
/// For assignment, appending, and comparison the following types are
/// supported for the other side: 
///    - char
///    - asciz const char pointer (C-style string)
///    - types that provide begin() and end() iterators (which includes
///      string< N > and std::string).
///
/// The fixed maximum size makes it impractical to have string expressions
/// (what would the size of the result be?). So instead of
///
///     std::string s = "[" + text + "]";
///
/// you will have to write 
///
///     hwlib::string< 20 > s; 
///     s.clear() << "[" << text << "]";
/// 
/// (The .clear() is not strictly needed because the default constructor
/// creates an empty string, but it improves readability).
//
template<>
class string< 0 > {
private:   
   
   // maximum length (maximum number of valid characters) of the string
   const size_t allocated_length;
   
   // current length (number of valid characters) of the string
   size_t current_length;

   // pointer to the array that stores the characters
   char * const content;

   // dummy char used for out-of-bounds accesses
   static char dummy; 
   
   // only string< N > is allowed to construct a string< 0 >
   template< size_t > friend class string;
   
   // return a pointer into the context, clipped to the valid range
   const char * sanitize( size_t n ){
      return ( n <= current_length )
         ? content + n
         : content + current_length;
   }
   
   // object constructor, called by string< N >'s constructors
   template< typename T > 
   constexpr string( size_t allocated_length, char * content, const T & x ):
      allocated_length{ allocated_length }, 
      current_length{ 0 },
      content{ content }
   {
      for( char c : iterate( x ) ){
         if( current_length < allocated_length ){
            content[ current_length++ ] = c;
         }
      }
   }     
   
   // range constructor, called by range()
   // not used directly, because the result must be a const
   constexpr string( char * start, char * beyond ):
      allocated_length( beyond - start ),
      current_length( beyond - start ),
      content( start )
   {}      
   
   //=========================================================================
   //
   // iterator(s) for char sources
   //
   //=========================================================================
   
   class iterate {
       
   public:
    
      // iterate over a single char
      constexpr iterate( char ch ) :
         c( ch ), start( &c ), beyond( &this->c + 1) 
      {}
       
      // iterate over an asciz string       
      constexpr iterate( const char *p ) :
         c( 0 ), start( p ), beyond( asciz_beyond( p )) {
      }
 
      // iterate over anything that has begin() and end() 
      template< typename T >
      constexpr iterate( const T & s ) :
         c( 0 ), start( s.begin() ), beyond( s.end() )
      {}   

      constexpr const char * begin() const {
         return start;
      }
        
      constexpr const char * end() const {
         return beyond;
      }

   private:
      const char c;
      const char * const start;
      const char * const beyond;
   };
   
public:

   //=========================================================================
   //
   // miscellaneous
   //
   //=========================================================================
   
   /// special value for beyond-end or not-found
   static const size_t nsize = 1;
   
   /// \brief   
   /// the maximum number of characters that can be stored
   constexpr size_t max_size() const {
      return allocated_length;
   }   
    
   /// \brief   
   /// the number of characters that are currently stored
   constexpr size_t length() const {
      return current_length;
   }     
   
   /// \brief   
   /// check index for validity
   /// \details
   /// Return whether n is a valid index.
   constexpr bool valid_index( const size_t n ) const {
      return( n < allocated_length );
   }
   
   /// \brief   
   /// output to any target that supports operator<< for a char *
   template< typename T >
   friend T & operator<< ( T & lhs, const string< 0 > & rhs ){
      for( char c : rhs ){
         lhs << c;
      }   
      return lhs;
   }     
   
   
   //=========================================================================
   //
   // append
   //
   //=========================================================================

   /// \brief   
   /// append the char if possible, otherwise ignore it  
   string & append( char c ){
      if( current_length < allocated_length ){
         content[ current_length++ ] = c;
      }   
      return *this;
   }
   
   /// \brief   
   /// append a char if possible, otherwise ignore it 
   string & operator+=( char c ){
      return append( c );
   }
   
   /// \brief   
   /// append a char if possible, otherwise ignore it    
   string & operator<<( char c ){
      return append( c );
   }
   
   /// \brief   
   /// append something (as far as possible, ignore the excess)
   template< typename T >
   string & operator+=( const T & rhs ){
      for( char c : iterate( rhs ) ){
         append( c );
      }
      return *this;
   }
   
   /// \brief   
   /// append something (as far as possible, ignore the excess)   
   template< typename T >
   string & operator<<( const T & rhs ){
      return operator+=( rhs );
   }
   
   
   //=========================================================================
   //
   // assign
   //
   //=========================================================================   
   
   /// \brief   
   /// set to ""
   string & clear(){
      current_length = 0;
      return *this;
   } 
   
   /// \brief   
   /// assign something
   template< typename T >
   string & operator=( const T & rhs ){
      return clear() += rhs;
   }   
   
   
   //=========================================================================
   //
   // iterate
   //
   //=========================================================================       
   
   /// \brief   
   /// start iterator
   char * begin() {
      return content;
   }

   /// \brief   
   /// end iterator
   char * end() {
      return content + current_length;
   }   
   
   /// \brief   
   /// start const iterator
   const char * begin() const {
      return content;
   }

   /// \brief   
   /// end const iterator
   const char * end() const {
      return content + current_length;
   }   
   
   
   //=========================================================================
   //
   // range
   //
   //=========================================================================

   /// \brief
   /// non-owning string (sub)range from two iterators 
   /// \details
   /// This function returns a const string object that appears to contains 
   /// the characters range pointed to by the start parameter up to 
   /// (but excluding) the character pointed to by the end parameter.
   /// 
   /// The object is a non-owning range: it doesn't make a copy.
   /// Hence any change to the characters will be reflected in the range.
   static constexpr const string< 0 > range( 
      const char * start, 
      const char * beyond 
   ){
      // Casting the const away is OK because the returned range object is
      // returned as const, so the stored char pointers are const again.
      // Blame C++ for not having a const constructor :(
      return string( 
         const_cast< char * >( start ), 
         const_cast< char * >( beyond )
      );
   }      
   
   /// \brief
   /// non-owning string (sub)range from an asciz string
   /// \details
   /// This function returns a const string object that appears to contains 
   /// the characters in the asciz string pointed to by the start parameter.
   /// 
   /// The object is a non-owning range: it doesn't make a copy.
   /// Hence any change to the characters will be reflected in the range.
   static constexpr const string< 0 > range(
      const char * start
   ){
      // see above
      return string( 
         const_cast< char * >( start ), 
         const_cast< char * >( asciz_beyond( start ) )
      );
   }  


   //=========================================================================
   //
   // erase & replace
   //
   //=========================================================================
   
   /// \brief     
   /// remove a substring
   /// \details
   ///
   
   
   
   // replace_inplace
   // inplace_replace
   // inplace_erase   
   
   
   
   //=========================================================================
   //
   // find
   //
   //=========================================================================
   
   /// \brief     
   /// check whether a substring occurs in a string at a given position
   /// \details
   /// Searches the string for the first occurrence of the 
   /// sequence specified by its arguments.
   /// 
   /// When pos is specified, the search only includes characters 
   /// at or after position pos, ignoring any possible occurrences 
   /// that include characters before pos.
   template< typename T >
   bool find_at( const T & s, size_t pos = 0 ) const {
      for( char c : iterate( s ) ){
         if( ( pos >= current_length ) || ( content[ pos++ ] != c ) ){ 
            return false;            
         }            
      }   
      return true;
   }
   
   /// \brief     
   /// find a substring in a string
   /// \details
   /// Searches the string for the first occurrence of the 
   /// sequence specified by its arguments.
   /// 
   /// When pos is specified, the search only includes characters 
   /// at or after position pos, ignoring any possible occurrences 
   /// that include characters before pos.
   ///
   /// When no match is found, nsize is returned.
   template< typename T >
   size_t find( const T & s, size_t pos = 0 ) const {
      while( pos < current_length ){
         if( find_at( s, pos ) ){
            return pos;
         }
         pos++;
      }     
      return nsize;
   }      
   
   /// \brief     
   /// find a substring in a string
   /// \details
   /// Searches the string for the last occurrence of the 
   /// sequence specified by its arguments.
   /// 
   /// When pos is specified, the search only includes characters 
   /// at or after position pos, ignoring any possible occurrences 
   /// that include characters before pos.
   ///
   /// When no match is found, nsize is returned.   
   template< typename T >
   size_t rfind( const T & s, size_t pos = 0 ) const {
      size_t i = current_length;
      while( pos < i ){
         if( find_at( s, i ) ){
            return i;
         }
         i--;
      }     
      return nsize;
   }   
   
   
   //=========================================================================
   //
   // operator[]
   //
   //=========================================================================
   
   /// \brief   
   /// return n'th character reference
   /// \details
   /// Return a reference to the n'th character if the index is valid,
   /// otherwise return the dummy character.
   char & operator[]( int n ){
      return valid_index( n ) ? content[ n ] : dummy;
   }

   /// \brief      
   /// return n'th character value
   /// \details
   /// Return the value of the n'th character if the index is valid,
   /// otherwise return the dummy character value.
   char operator[]( int n ) const {
      return valid_index( n ) ? content[ n ] : '?';
   }
   
   
   //=========================================================================
   //
   // ranges
   //
   //=========================================================================   
   
   /*
   string_range range_start_length( size_t a, size_t b ){
      return string_range( sanitize( a ), sanitize( a + b ) );   
   }
   
   string_range range_start_end( size_t a, size_t b ){
      return string_range( sanitize( a ), sanitize( b ) );   
   }
   
   template< typename T >
   string_range range_find_length( const T & a, size_t b ){
      return string_range( sanitize( a ), sanitize( a + b ) );   
   }
  
   template< typename T, typename Q >
   string_range range_find_find( const T & a, const Q & b ){
      return string_range( sanitize( a ), sanitize( a + b ) );   
   }
   */
   
   //=========================================================================
   //
   // compare 
   //
   //=========================================================================        
   
   /// \brief   
   /// compare for equality
   template< typename T >
   bool operator==( const T & rhs ) const {         
      const char * p = content;       
      for( const char c : iterate( rhs ) ){       
          if( p == end() ){
             return false;
          }
          if( c != *p++ ){
             return false;
          }
      }
      return p == end();
   }    

   /// \brief   
   /// compare for inequality
   template< typename T >
   bool operator!=( const T & rhs ) const {   
      return ! ( *this == rhs );
   }   
   
   /// \brief   
   /// compare for larger than 
   template< typename T >
   bool operator>( const T & rhs ) const {
      const char * p = content;       
      for( const char c : iterate( rhs ) ){
          if( p == end() ){
             return false;             
          }   
          if( *p++ <= c ){
             return false;
          }
      }
      return true;
   }    

   /// \brief   
   /// compare for larger than or equal
   template< typename T >
   bool operator>=( const T & rhs ) const {
      const char * p = content;       
      for( const char c : iterate( rhs ) ){
          if( p == end() ){
             return false;             
          }   
          if( *p++ < c ){
             return false;
          }
      }
      return true;
   }    

   /// \brief   
   /// compare for smaller than 
   template< typename T >
   bool operator<( const T & rhs ) const {
      const char * p = content;       
      for( const char c : iterate( rhs ) ){
          if( p == end() ){
             return true;             
          }   
          if( *p++ >= c ){
             return false;
          }
      }
      return false;
   }    

   /// \brief   
   /// compare for smaller than or equal
   template< typename T >
   bool operator<=( const T & rhs ) const {
      const char * p = content;       
      for( const char c : iterate( rhs ) ){
          if( p == end() ){
             return true;             
          }   
          if( *p++ > c ){
             return false;
          }
      }
      return false;
   }    

};

//============================================================================
//
// static dummy
//  
//============================================================================

#ifdef HWLIB_ONCE 
char string<0>::dummy; 
#endif

//============================================================================
//
// reverse compare
//  
//============================================================================

/// \brief   
/// compare for equality
template< typename T >   
typename std::enable_if < 
   ! std::is_base_of< string< 0 >, T >::value, bool >::type    
operator==( const T & lhs, const string< 0 > & rhs ){
   return rhs.operator==( lhs );
}

/// \brief   
/// compare for inequality
template< typename T >   
typename std::enable_if < 
   ! std::is_base_of< string< 0 >, T >::value, bool >::type    
operator!=( const T & lhs, const string< 0 > & rhs ){
   return rhs.operator!=( lhs );
}

/// \brief   
/// compare for large than
template< typename T >   
typename std::enable_if < 
   ! std::is_base_of< string< 0 >, T >::value, bool >::type    
operator>( const T & lhs, const string< 0 > & rhs ){
   return ! rhs.operator<=( lhs );
}

/// \brief   
/// compare for large than or equal
template< typename T >   
typename std::enable_if < 
   ! std::is_base_of< string< 0 >, T >::value, bool >::type    
operator>=( const T & lhs, const string< 0 > & rhs ){
   return ! rhs.operator<( lhs );
}

/// \brief   
/// compare for smaller than
template< typename T >   
typename std::enable_if < 
   ! std::is_base_of< string< 0 >, T >::value, bool >::type    
operator<( const T & lhs, const string< 0 > & rhs ){
   return ! rhs.operator>=( lhs );
}

/// \brief   
/// compare for smaller than or equal
template< typename T >   
typename std::enable_if < 
   ! std::is_base_of< string< 0 >, T >::value, bool >::type    
operator<=( const T & lhs, const string< 0 > & rhs ){
   return ! rhs.operator>( lhs );
}


//============================================================================
//
// template< size_t N >
// string< N >
//  
//============================================================================

/// \brief   
/// concrete fixed-maximum-length string
/// \details
/// This is the concrete string class template. Use it to declare
/// a variable of a known (maximum) size. 
/// Use string< 0 > for references, parameters, ranges, etc.
template< size_t maximum_length >
class string: public string< 0 > {
private:

   // the store for the characters
   char content[ maximum_length ];
   
public:

   /// \brief   
   /// create fixed-maximum-size string, initially empty
   string():
      string< 0 >( maximum_length, content, "" )
   {}      
   
   /// \brief      
   /// create fixed-maximum-size string, with an initial value
   template< typename T > 
   string( const T & x ):
      string< 0 >( maximum_length, content, x )
   {}      

   // avoid ambiguity
   string & operator=( const string & rhs ){
       string< 0 >::operator=( rhs );
       return *this;
   }
   
};

}; // namespace hwlib

#endif // HWLIB_STRING_H
