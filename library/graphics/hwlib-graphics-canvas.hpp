// ==========================================================================
//
// File      : hwlib-graphics-canvas.hpp
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

template< int size_x, int size_y >
class canvas_color : public window, private image {
private:

   color buffer[ size_x ][ size_y ];
    
   void write_implementation( xy pos, color col ) override {
       buffer[ pos.x ][ pos.y ] = col;
   }    
   
   color get_implementation( xy pos ) const override {
       return buffer[ pos.x ][ pos.y ];
   }
   
public:

   window & as_window;
   image & as_image;

   canvas_color(
      color foreground = white, 
      color background = black 
   ):
      window( xy( size_x, size_y ), foreground, background ),
      image( xy( size_x, size_y ) ),
      as_window( *this ),
      as_image( *this )
   {}
   
   void flush() override {} 

};

template< int size_x, int size_y >
class canvas_bw : public window, private image  {
private:

   uint8_t buffer[ ( size_x + 7 ) / 8 ][ size_y ];
    
   void write_implementation( xy pos, color col ) override {
       uint8_t & b = buffer[ pos.x / 8 ][ pos.y ];
       if( col == foreground ){
          b |= ( 0b1 << pos.y % 8 );
       } else {
          b &= ~ ( 0b1 << pos.y % 8 );
       }          
   }    
   
   color read_implementation( xy pos ) const override {
       return buffer[ pos.x ][ pos.y ]
          ? foreground
          : background;
   }
   
public:

   window & as_window;
   image & as_image;

   canvas_bw(
      color foreground = white, 
      color background = black 
   ):
      window( xy( size_x, size_y ), foreground, background ),
      image( xy( size_x, size_y ) ),
      as_window( *this ),
      as_image( *this )
   {}
   
   void flush() override {} 

};

}; // namespace hwlib
