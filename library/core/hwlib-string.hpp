// ==========================================================================
//
// File      : hwlib-string.hpp
// Part of   : C++ library for close-to-the-hardware OO programming
// Copyright : wouter@voti.nl 2017-2019
//
// This code is partially based on a research project by Martin Broers.
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

/// return the end iterator from an asciz string
constexpr const char * asciz_beyond( const char * p ){
   while( *p != '\0' ){
      ++p;
   }
   return p;
}

  
//============================================================================
//
// string_base
//  
//============================================================================

/// fixed-maximum-length string interface
///  
/// This is a string class template with a fixed maximum length. 
/// The maximum length is the template parameter.
/// All such strings inherit from string_base.
///
/// An attempt to add characters beyond the maximum length will ignore
/// the excess characters.
/// Accessing an invalid character by the operator[] will yield either
/// an undefined character value, or a reference to a (hidden) static
/// character.
///
/// This class was assumed to be part of the the not-time-critical
/// part of an application, hence the implementation leans towards small
/// code size, not maximum speed, and tries to avoid Undefined Behaviour.
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
class string_base {
private:   
   
   // maximum length (maximum number of valid characters) of the string
   const size_t allocated_length;
   
   // current length (number of valid characters) of the string
   size_t current_length;

   // pointer to the array that stores the characters
   char * const content;

   // dummy char returned on out-of-bounds accesses
   static char dummy;
   
   // only string< N > is allowed to construct a string_base
   template< size_t > friend class string;
   
   // return a pointer into the context, clipped to the valid range
   const char * sanitize( size_t n ) const {
      return ( n <= current_length )
         ? content + n
         : content + current_length;
   }
   char * sanitize( size_t n ){
      return ( n <= current_length )
         ? content + n
         : content + current_length;
   }
   
   // object constructor, called by string< N >'s constructors
   template< typename T > 
   constexpr string_base( size_t allocated_length, char * content, const T & x ):
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
   constexpr string_base( char * start, char * beyond ):
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
   static const size_t nsize = 0xFFFF;
     
   /// the maximum number of characters that can be stored
   constexpr size_t max_size() const {
      return allocated_length;
   }   
      
   /// the number of characters that are currently stored
   constexpr size_t length() const {
      return current_length;
   }     
     
   /// check index for validity
   ///
   /// Return whether n is a valid index.
   constexpr bool valid_index( const size_t n ) const {
      return( n < allocated_length );
   }
     
   /// output to any target that supports operator<< for a char *
   template< typename T >
   friend T & operator<< ( T & lhs, const string_base & rhs ){
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
 
   /// append the char if possible, otherwise ignore it  
   string_base & append( char c ){
      if( current_length < allocated_length ){
         content[ current_length++ ] = c;
      }   
      return *this;
   }
   
   /// append a char if possible, otherwise ignore it 
   string_base & operator+=( char c ){
      return append( c );
   }
     
   /// append a char if possible, otherwise ignore it    
   string_base & operator<<( char c ){
      return append( c );
   }
     
   /// append something (as far as possible, ignore the excess)
   template< typename T >
   string_base & operator+=( const T & rhs ){
      for( char c : iterate( rhs ) ){
         append( c );
      }
      return *this;
   }
    
   /// append something (as far as possible, ignore the excess)   
   template< typename T >
   string_base & operator<<( const T & rhs ){
      return operator+=( rhs );
   }
   
   
   //=========================================================================
   //
   // assign
   //
   //=========================================================================   
     
   /// set to ""
   string_base & clear(){
      current_length = 0;
      return *this;
   } 
   
   /// assign something
   template< typename T >
   string_base & operator=( const T & rhs ){
      return clear() += rhs;
   }   
   
   
   //=========================================================================
   //
   // iterate
   //
   //=========================================================================       
     
   /// start iterator
   char * begin() {
      return content;
   }
  
   /// end iterator
   char * end() {
      return content + current_length;
   }   
     
   /// start const iterator
   const char * begin() const {
      return content;
   }
 
   /// end const iterator
   const char * end() const {
      return content + current_length;
   }   
   
   
   //=========================================================================
   //
   // range
   //
   //=========================================================================

   /// non-owning string (sub)range from two iterators 
   ///
   /// This function returns a const string object that appears to contains 
   /// the characters range pointed to by the start parameter up to 
   /// (but excluding) the character pointed to by the end parameter.
   /// 
   /// The object is a non-owning range: it doesn't make a copy.
   /// Hence any change to the characters will be reflected in the range.
   static constexpr const string_base range( 
      const char * start, 
      const char * beyond 
   ){
      // Casting the const away is OK because the returned range object is
      // returned as const, so the stored char pointers are const again.
      // Blame C++ for not having a const constructor :(
      return string_base( 
         const_cast< char * >( start ), 
         const_cast< char * >( beyond )
      );
   }      
   
   /// non-owning string (sub)range from an asciz string
   ///
   /// This function returns a const string object that appears to contains 
   /// the characters in the asciz string pointed to by the start parameter.
   /// 
   /// The object is a non-owning range: it doesn't make a copy.
   /// Hence any change to the characters will be reflected in the range.
   static constexpr const string_base range(
      const char * start
   ){
      // see above
      return string_base( 
         const_cast< char * >( start ), 
         const_cast< char * >( asciz_beyond( start ) )
      );
   }  


   //=========================================================================
   //
   // erase & replace:
   // remove a substring
   //
   // replace_inplace
   // inplace_replace
   // inplace_erase   
   //
   //=========================================================================
  
   // TBW
   
   
   //=========================================================================
   //
   // find
   //
   //=========================================================================
       
   /// check whether a substring occurs in a string at a given position
   ///
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
        
   /// find a substring in a string
   ///
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
        
   /// find a substring in a string
   ///
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
     
   /// return n'th character reference
   ///
   /// Return a reference to the n'th character if the index is valid,
   /// otherwise return the dummy character.
   char & operator[]( int n ){
      return valid_index( n ) ? content[ n ] : dummy;
   }
      
   /// return n'th character value
   ///
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
   
   /// subrange based on start index and length
   string_base range_start_length( size_t a, size_t b ){
      return string_base( sanitize( a ), sanitize( a + b ) );   
   }
   
   /// subrange based on start index and end index
   string_base range_start_end( size_t a, size_t b ){
      return string_base( sanitize( a ), sanitize( b ) );   
   }
   
   /// subrange based on substring start and length
   template< typename T >
   string_base range_find_length( const T & a, size_t b ){
      return string_base( sanitize( a ), sanitize( a + b ) );   
   }
  
   /// subrange based on first substring start and second substring start
   template< typename T, typename Q >
   string_base range_find_find( const T & a, const Q & b ){
      return string_base( sanitize( a ), sanitize( a + b ) );   
   }

   
   //=========================================================================
   //
   // compare 
   //
   //=========================================================================        
     
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
 
   /// compare for inequality
   template< typename T >
   bool operator!=( const T & rhs ) const {   
      return ! ( *this == rhs );
   }   
    
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

//#ifdef HWLIB_ONCE 
//char string<0>::dummy; 
//#endif

//============================================================================
//
// reverse compare
//  
//============================================================================

#ifndef BMPTK_CHIP_atmega328
 
/// compare for equality
template< typename T >   
typename std::enable_if < 
   ! std::is_base_of< string_base, T >::value, bool >::type    
operator==( const T & lhs, const string_base & rhs ){
   return rhs.operator==( lhs );
}
   
/// compare for inequality
template< typename T >   
typename std::enable_if < 
   ! std::is_base_of< string_base, T >::value, bool >::type    
operator!=( const T & lhs, const string_base & rhs ){
   return rhs.operator!=( lhs );
}
   
/// compare for large than
template< typename T >   
typename std::enable_if < 
   ! std::is_base_of< string_base, T >::value, bool >::type    
operator>( const T & lhs, const string_base & rhs ){
   return ! rhs.operator<=( lhs );
}
   
/// compare for large than or equal
template< typename T >   
typename std::enable_if < 
   ! std::is_base_of< string_base, T >::value, bool >::type    
operator>=( const T & lhs, const string_base & rhs ){
   return ! rhs.operator<( lhs );
}
   
/// compare for smaller than
template< typename T >   
typename std::enable_if < 
   ! std::is_base_of< string_base, T >::value, bool >::type    
operator<( const T & lhs, const string_base & rhs ){
   return ! rhs.operator>=( lhs );
}
   
/// compare for smaller than or equal
template< typename T >   
typename std::enable_if < 
   ! std::is_base_of< string_base, T >::value, bool >::type    
operator<=( const T & lhs, const string_base & rhs ){
   return ! rhs.operator>( lhs );
}

#endif
 
//============================================================================
//
// template< size_t N >
// string< N >
//  
//============================================================================

/// concrete fixed-maximum-length string
///
/// This is the concrete string class template. Use it to declare
/// a variable of a known (maximum) size. 
/// Use string_base for references, parameters, ranges, etc.
template< size_t maximum_length >
class string: public string_base {
private:

   // the store for the characters
   char content[ maximum_length ];
   
public:
  
   /// create fixed-maximum-size string, initially empty
   string():
      string_base( maximum_length, content, "" )
   {}      
         
   /// create fixed-maximum-size string, with an initial value
   template< typename T > 
   string( const T & x ):
      string_base( maximum_length, content, x )
   {}      
   
   
   /// \cond INTERNAL 
   // needed to avoid ambiguity
   string & operator=( const string & rhs ){
       string_base::operator=( rhs );
       return *this;
   }
   /// \endcond    
};

#ifdef _HWLIB_ONCE 

char string_base::dummy = '\0';

#endif

}; // namespace hwlib
