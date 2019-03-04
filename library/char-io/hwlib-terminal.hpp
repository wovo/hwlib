// ==========================================================================
//
// File      : hwlib-terminal.hpp
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

/// terminal interface
/// 
/// This class implements an interface to a character terminal.
///
/// A terminal is a rectangular windows of (ASCII) characters.
///
/// A terminal implements the ostream interface, but it doesn't scroll:
/// while the cursor is outside the visible character area
/// (beyond the end of the line, or beyond the number of lines)
/// any character writes will be ignored.
///
/// Some characters are treated special:
///    - '\\n' puts the cursor at the first position of the next line
///    - '\\r' puts the cursor at the start of the current line
///    - '\\f' puts the cursor at the top-left position and clears the terminal
///    - '\\txxyy' puts the cursor at the position (xx,yy)
///
/// The x and y coordinates are 0-origin and count to the right and down.
/// In other words, the top-left character position is (0,0), and the bottom
/// right character position is size - (1,1).
///
/// \image html terminal-positions.png
///
class terminal : public ostream {
private:

   uint_fast8_t goto_state;

protected:

   /// the actual writing of a character
   /// 
   /// When this function is called, the the current cursor is
   /// guaranteed to be within the terminal, and the character is
   /// not one of the special characters (\\n, \\r, \\c)
   virtual void putc_implementation( char c ) = 0;

   /// change the write location 
   /// 
   /// This function is called when the write location is
   /// changed *except* when it is changed to the next x
   /// position by a call to putc_implementation.
   ///
   /// The default implementation does nothing.
   virtual void cursor_set_implementation( xy target ){}

   /// The default implementation of flush does nothing.
   virtual void flush(){}

public:

   /// the size of the terminal in characters in x and y direction
   const xy size;
   
   /// the current cursor location
   ///
   /// Don't write to this attribute, use cursor_set().
   xy cursor;

   /// construct a terminal from its size in characters in x and y direction
   terminal( xy size ): size( size ){}

   /// put the cursor (write location) at x, y
   virtual void cursor_set( xy target ){
      cursor = target;
      cursor_set_implementation( target );
   }

   /// write a single character
   void putc( char c ){
      
      //WLIB_TRACE << c << " " << x <<  " " << y << " " << goto_xy_state;

      switch( goto_state ){

         case 0 :
            break;

         case 1 :
            cursor.x = 10 * ( c - '0' );
            ++goto_state;
            return;

         case 2 :
            cursor.x += c - '0' ;
            ++goto_state;
            return;

         case 3 :
            cursor.y = 10 * ( c - '0' );
            ++goto_state;
            return;

         case 4 :
            cursor.y += c - '0' ;
            goto_state = 0;
            cursor_set( cursor );
            return;

      }

      if( c == '\n' ){
         cursor_set( xy( 0, cursor.y + 1 ) );

      } else if( c == '\r' ){
         cursor_set( xy( 0, cursor.y ) );

      } else if( c == '\v' ){
         cursor_set( xy( 0, 0 ) );

      } else if( c == '\f' ){
         clear();

      } else if( c == '\t' ){
         goto_state = 1;

      } else if(
         ( cursor.x >= 0 )
         && ( cursor.x < size.x )
         && ( cursor.y >= 0 )
         && ( cursor.y < size.y )
      ){
          putc_implementation( c );
          ++cursor.x;
      }
   }

   /// clear the terminal
   /// 
   /// This function clears the terminal and puts the cursor at (0,0).
   /// The default implementation does this by writing spaces to all
   /// locations. A concrete implementation might provide
   /// a better (faster) way.
   virtual void clear(){
      for( int_fast16_t y = 0; y < size.y; ++y ){
         cursor_set( xy( 0, y ) );
         for( int_fast16_t x = 0; x < size.x; ++x ){
            putc( ' ' );
         }
      }
      cursor_set( xy( 0, 0 ) ) ;
   }
   
}; // class terminal

}; // namespace hwlib
