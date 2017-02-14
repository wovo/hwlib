// ==========================================================================
//
// File      : hwlib-string.hpp
// Part of   : C++ hwlib library for close-to-the-hardware OO programming
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

#ifndef HWLIB_STRING_H
#define HWLIB_STRING_H

#include <stddef.h>

namespace hwlib {

// forward declaration of the class template   
template< size_t maximum_length > class string;
  
//============================================================================
//
// string< 0 >
//  
//============================================================================

/// abstract fixed-maximum-length string
//  
/// This is a string class template with a fixed maximum length. 
/// The maximum length is the template parameter.
/// All such strings inherit from the base class string<>.
///
/// An attempt to add characters beyond the maximum length will ignore
/// the excess characters.
/// Accessing an invalid character by the operator[] will yield
/// an undefined character value, or a reference to a (hidden) static
/// character.
//
template<>
class string< 0 > {
private:   
   
   // maximum length of the string
   const size_t allocated_length;
   
   // maximum length of the string
   size_t current_length;

   // pointer to the array that stores the characters
   char * const content;

   // dummy char used for out-of-bounds accesses
   static char dummy; 
    
    static const char * beyond( const char * p ){
       while( *p != '\0' ){
           ++p;
       }
       return p;
    }
    
   // iterate over a char source
   class iterate {
    public:
    
      iterate( char ch ) :
           c( ch ), start( &c ), last( &this->c + 1) 
        {}
        
      iterate( const char *p ) :
           c( 0 ), start( p ), last( beyond( p )) {
      }

      iterate( string<0> f ) :
           iterate( f.c_str() )
      {}   

      const char * begin() const {
         return start;
      }
        
      const char * end() const {
         return last;
      }

   private:
      const char c;
      const char * const start, * const last;
   };
   
protected:

   // only string< N > is allowed to construct a string< 0 >
   string( size_t allocated_length, char * content ):
      allocated_length{ allocated_length }, 
      content{ content }
   {
       clear();
   }    

   template< typename T > 
   string( size_t allocated_length, char * content, const T & x ):
      allocated_length{ allocated_length }, 
      content{ content }
   {
       operator=( x );
   }     
   
public:
   
   // pointer to the 0-terminated content
   const char * c_str() const {
      return content;
   }

   /// the maximum number of characters that can be stored
   size_t max_size() const {
      return allocated_length;
   }   
    
   /// the number of characters that are currently stored
   size_t length() const {
      return current_length;
   }  
    
   /// sets to ""
   void clear(){
      current_length = 0;
      content[ 0 ] = '\0';
   } 

   /// append the char if possible, otherwise ignore it   
   void append( char c ){
      if( current_length < allocated_length ){
         content[ current_length++ ] = c;
         content[ current_length ] = '\0';
      }   
   }
   
   /// append a char if possible, otherwise ignore it 
   string< 0 > & operator+=( char c ){
      append( c );
      return *this;
   }
   string< 0 > & operator<<( char c ){
      append( c );
      return *this;
   }
   
   /// append something else (as far as possible, ignore the excess)
   template< typename T >
   string< 0 > & operator+=( const T & rhs ){
      for( char c : iterate( rhs ) ){
         append( c );
      }
      return *this;
   }
   template< typename T >
   string< 0 > & operator<<( const T & rhs ){
      return operator+=( rhs );
   }
   
   /// assign something
   template< typename T >
   string< 0 > & operator=( const T & rhs ){
      clear(); 
      return *this += rhs;
   }   
   
   /// compare to something
   template< typename T >
   bool operator==( const T & rhs ) const {
      const char * p = content;       
      for( char c : iterate( rhs ) ){
          if( c != *p++ ){
              return false;
          }
      }
      return( *p == '\0' );
   }    
   
   // to resolve ambiguity
//   friend bool operator==( const string< 0 > & lhs, const string< 0 > & rhs ){
//      return lhs.operator==( rhs );
//   }
   
    /// output to any target that supports operator<< for a char *
   template< typename T >
   friend T & operator<< ( T & lhs, const string< 0 > & rhs ){
      lhs << rhs.c_str();
      return lhs;
   }

   // operator[]
   // valid_indexd
   // compare
   
};

/*
/// reverse-compare to something   
template< typename T >
bool operator==( const T & lhs, const string< 0 > & rhs ){
   return rhs == lhs;
}   

// to resolve ambiguity
template<>
bool operator==( const string< 0 > & lhs, const string< 0 > & rhs ){
   return lhs.operator==( rhs );
}
*/


//============================================================================
//
// template< size_t N >
// string< N >
//  
//============================================================================


/// abstract fixed-maximum-length string
template< size_t template_allocated_length >
class string: public string< 0 > {
private:

   // the store for the characters
   // must be +1 to store the /0 needed by c_str()
   char content[ template_allocated_length + 1 ];
   
public:

   /// create fixed-maximum-size string, initially empty
   string():
      string< 0 >( template_allocated_length, content )
   {}      
   
   /// create fixed-maximum-size string, with an initial value
   template< typename T > 
   string( const T & x ):
      string< 0 >( template_allocated_length, content, x )
   {}      
   
};

}; // namespace hwlib

#endif // HWLIB_STRING_H