// ==========================================================================
//
// File      : hwlib-console.hpp
// Part of   : hwlib library for V1OOPC and V1IPAS
// Copyright : wouter@voti.nl 2016
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================
/// @file

#ifndef HWLIB_CONSOLE_H
#define HWLIB_CONSOLE_H

#include <hwlib-ostream.hpp>

namespace hwlib {
   
/// console interface 
//
/// This class implements an interface to a character console.  
///
/// A console is a rectangular windows of (ASCII) characters.
/// A console implements the ostream interface, but it doesn't scroll:
/// while the cursor is outside the visible character area 
/// (beyond the end of the line, or beyond the number of lines) 
/// any character writes will be ignored.
/// Some characters are treated special:
///    - '\n' clears the rest of the line, and then 
///      moves to the first position of the next line
///    - '\r' puts the cursor at the start of the current line
///    - '\c' moves the cursor to the top-left position 
/// 
/// The x and y coordinates are 0-origin and count to the right and down.
/// In other words, the top-left character position is (0,0), and the bottom
/// right character position is (rows - 1, columns - 1).
///
/// \image html console-positions.png
///
class console : public ostream {  
protected:

   /// the actual writing of a character
   //
   /// When this function is called, the the current cursor is 
   /// guaranteed to be within the console, and the character is
   /// not one of the special characters (\n, \r, \c)
   virtual void putc_implementation( char c ) = 0;
   
   /// change the write location to x, y
   //
   /// This function is called when the write location is 
   /// changed *except* when it is changed to the next x
   /// position by a call to putc_implementation.
   ///
   /// The default implementation does nothing.
   virtual void goto_xy_implementation( int x, int y ){}
   
  
public:

   /// the number of colums in the console
   const int columns;
   
   /// the number of lines (rows) in the console
   const int lines;

   /// the current write column;
   int x;
   
   /// the current write line;
   int y;
   
   /// construct a console from its columns (X size) and lines (Y size)
   console( 
      int columns, 
      int lines 
   ): 
      columns{ columns }, 
      lines{ lines }
   {}

   /// put the cursor (write location) at x, y
   virtual void goto_xy( int new_x, int new_y ){
      x = new_x;
      y = new_y;      
   }
   
   /// write a single character
   void putc( char c ) override {
      if( c == '\n' ){
         goto_xy( 0, y + 1 );
         
      } else if( c == '\r' ){
         goto_xy( 0, y );
         
      } else if( c == '\v' ){
         goto_xy( 0, 0 );
         
      } else if(
         ( x >= 0 )
         && ( x < columns )
         && ( y >= 0 )
         && ( y < lines )
      ){
          putc_implementation( c );
          ++x;
      } 
   }
   
   /// clear the console
   //
   /// This function clears the console and puts the cursor at (0,0).
   /// The default implementation does this by writing spaces to all
   /// locations. A concrete implementation might provide
   /// a better (faster) way.
   virtual void clear(){
      for( int y = 0; y < lines; ++y ){
         goto_xy( 0, y );
         for( int x = 0; x < columns; ++x ){
            putc( ' ' );                        
         }
      }
      goto_xy( 0, 0 );
   }
      
}; // class console
   
}; // namespace hwlib

#endif // HWLIB_CONSOLE_H