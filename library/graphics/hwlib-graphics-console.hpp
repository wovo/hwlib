// ==========================================================================
//
// File      : hwlib-graphics.hpp
// Part of   : C++ hwlib library for close-to-the-hardware OO programming
// Copyright : wouter@voti.nl 2017
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

/// implements a console inside graphic window
class window_ostream : public terminal {
private:
   window & w;
   const font &f;
   location cursor;

   uint_fast16_t x_size( const window & w, const font &f ){
      const image & im = f[ ' ' ];
      return w.size.x / im.size.x;
   }
   uint_fast16_t y_size( const window & w, const font &f ){
      const image & im = f[ ' ' ];
      return w.size.y / im.size.y;
   }

   void goto_xy_implementation( uint_fast16_t x, uint_fast16_t y ) override {
      const image & im = f[ ' ' ];
      cursor.x = x * im.size.x;
      cursor.y = y * im.size.y;
   }

   void putc_implementation( char c ) override {
      const image & im = f[ c ];

      w.write( cursor, im );
      cursor.x += im.size.x;
   }

   void clear() override {
      w.clear();
      goto_xy( 0, 0 );
   }

   void flush() override {
      w.flush();
   }

public:
   /// construct an console from a window and a font
   window_ostream( window & w, const font &f ):
      terminal( x_size( w, f ), y_size( w, f ) ), w( w ), f( f ), cursor( 0, 0 )
   { }
};

}; // namespace hwlib
