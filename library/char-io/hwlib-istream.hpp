// ==========================================================================
//
// File      : hwlib-istream.hpp
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

/// character input interface
///
/// This class is a minimal std::istream work-alike for small embedded systems.
/// (as yet, only reading a single character is supported)
/// 
/// This class is abstract: a concrete subclass must implement getc().  
class istream : public noncopyable {     
public:        

   /// reports whether a character is available
   virtual bool char_available(){ return true; }
   
   /// read and return a single character or '\0'
   ///
   /// This function reads and returns a single character. 
   /// When no character is available it waits for one.
   virtual char getc() = 0;
	  

   /// read and return a single character or '\0'
   ///
   /// This function reads and returns a single character when one is available,
   /// otherwise it returns '\0'.
   virtual char getc_nowait(){
      if( char_available() ){		  
         return getc();
	  } else {
         return '\0';
      }			
   }
        
   /// input operator for char
   ///
   /// This function reads and 'returns' a single character. 
   /// When no character is available it waits for one.   
   friend istream & operator>>( istream & stream, char & x ){
      x = stream.getc();            
      return stream;   
   }           
   
}; // class istream

/*
 * class stream_demux : public istream {
   istream & left;
   istream & right;
public:

};
*/
   
}; // namespace hwlib
