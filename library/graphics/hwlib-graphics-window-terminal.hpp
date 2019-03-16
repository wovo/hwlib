// ==========================================================================
//
// File      : hwlib-graphics-window_terminal.hpp
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

/// implements a character terminal inside a graphic window
class terminal_from : public terminal {
private:

   window & w;
   const font &f;
   xy cursor;
   
   xy size_in_chars( const window & w, const font &f ){
      const image & im = f[ ' ' ];
      return xy(
         w.size.x / im.size.x,
         w.size.y / im.size.y
      );         
   }

   void cursor_set_implementation( xy target ) override {
      const image & im = f[ ' ' ];
      cursor = xy( target.x * im.size.x, target.y * im.size.y );
   }

   void putc_implementation( char c ) override {
      auto & image_raw = f[ c ];
      auto image = invert( image_raw );
      w.write( cursor, image );
      cursor.x += image.size.x;
   }

   void clear() override {
      w.clear();
      cursor_set( xy( 0, 0 ) );
   }

   void flush() override {
      w.flush();
   }

public:

   /// construct a terminal from a window and a font
   terminal_from( window & w, const font &f ):
      terminal( size_in_chars( w, f ) ), 
      w( w ), 
      f( f ), 
      cursor( xy( 0, 0 ) )
   { }

}; // class terminal_from

}; // namespace hwlib
