// ==========================================================================
//
// File      : hwlib-console.hpp
// Part of   : C++ hwlib library for close-to-the-hardware OO programming
// Copyright : wouter@voti.nl 2017
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

// this file contains Doxygen lines
/// @file

#ifndef HWLIB_CONSOLE_H
#define HWLIB_CONSOLE_H

#include HWLIB_INCLUDE( hwlib-ostream.hpp )

namespace hwlib {

/// \brief
/// console interface
/// \details
/// This class implements an interface to a character console.
///
/// A console is a rectangular windows of (ASCII) characters.
/// A console implements the ostream interface, but it doesn't scroll:
/// while the cursor is outside the visible character area
/// (beyond the end of the line, or beyond the number of lines)
/// any character writes will be ignored.
/// Some characters are treated special:
///    - '\\n' puts the cursor at the first position of the next line
///    - '\\r' puts the cursor at the start of the current line
///    - '\\f' puts the cursor at the top-left position and clears the console
///    - '\\txxyy' puts the cursor at the position (xx,yy)
///
/// The x and y coordinates are 0-origin and count to the right and down.
/// In other words, the top-left character position is (0,0), and the bottom
/// right character position is (rows - 1, columns - 1).
///
/// \image html console-positions.png
///
class console : public ostream {
private:
   uint_fast8_t goto_xy_state;

protected:

   /// \brief
   /// the actual writing of a character
   /// \details
   /// When this function is called, the the current cursor is
   /// guaranteed to be within the console, and the character is
   /// not one of the special characters (\\n, \\r, \\c)
   virtual void putc_implementation( char c ) = 0;

   /// \brief
   /// change the write location to x, y
   /// \details
   /// This function is called when the write location is
   /// changed *except* when it is changed to the next x
   /// position by a call to putc_implementation.
   ///
   /// The default implementation does nothing.
   virtual void goto_xy_implementation( uint_fast16_t x, uint_fast16_t y ){}

   /// The default implementation of flush does nothing.
   virtual void flush(){}

public:

   /// the number of colums in the console
   const uint_fast16_t  columns;

   /// the number of lines (rows) in the console
   const uint_fast16_t  lines;

   /// the current write column;
   uint_fast16_t  x;

   /// the current write line;
   uint_fast16_t  y;

   /// construct a console from its columns (X size) and lines (Y size)
   console(
      uint_fast16_t  columns,
      uint_fast16_t  lines
   ):
      columns{ columns },
      lines{ lines }
   { }

   /// put the cursor (write location) at x, y
   virtual void goto_xy( uint_fast16_t  new_x, uint_fast16_t  new_y ){
      x = new_x;
      y = new_y;
      goto_xy_implementation( x, y );
   }

   /// write a single character
   void putc( char c ){
      
      //WLIB_TRACE << c << " " << x <<  " " << y << " " << goto_xy_state;

      switch( goto_xy_state ){

         case 0 :
            break;

         case 1 :
            x = 10 * ( c - '0' );
            ++goto_xy_state;
            return;

         case 2 :
            x += c - '0' ;
            ++goto_xy_state;
            return;

         case 3 :
            y = 10 * ( c - '0' );
            ++goto_xy_state;
            return;

         case 4 :
            y += c - '0' ;
            goto_xy_state = 0;
            goto_xy( x, y );
            return;

      }

      if( c == '\n' ){
         goto_xy( 0, y + 1 );

      } else if( c == '\r' ){
         goto_xy( 0, y );

      } else if( c == '\v' ){
         goto_xy( 0, 0 );

      } else if( c == '\f' ){
         clear();

      } else if( c == '\t' ){
         goto_xy_state = 1;

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

   /// \brief
   /// clear the console
   /// \details
   /// This function clears the console and puts the cursor at (0,0).
   /// The default implementation does this by writing spaces to all
   /// locations. A concrete implementation might provide
   /// a better (faster) way.
   virtual void clear(){
      for( uint_fast16_t y = 0; y < lines; ++y ){
         goto_xy( 0, y );
         for( uint_fast16_t x = 0; x < columns; ++x ){
            putc( ' ' );
         }
      }
      goto_xy( 0, 0 );
   }
   
}; // class console

}; // namespace hwlib

#endif // HWLIB_CONSOLE_H