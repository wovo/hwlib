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

/// \brief
/// a graphics window
/// \details
/// This class abstracts the interface to a graphic window.
class window {
private:

   /// \brief
   /// write a pixel - implementation
   /// \details
   /// This NVI function writes a the color col to the pixel at location loc.
   /// Loc is guaranteed to be within the window, and the color
   /// is guranteed to be not transparent.
   ///
   /// When buffering is specified ( buf == buffered ) the actual writing
   /// can be delayed until the next flush() call.
   virtual void write_implementation( 
      location pos, 
      color col
   ) = 0;      
   
public:
   /// \brief
   /// the size of the window
   /// \details
   /// This is the size of the window: the number of pixels
   /// in the x and y direction.
   const location size;
   
   /// \brief
   /// the foreground color of the window
   /// \details
   /// This color could be used to draw graphics.
   color foreground;
   
   /// \brief
   /// the background color of the window
   /// \details
   /// This is the color use by the clear() function.
   color background;
   
   /// construct a window by specifying its size and foreground and background colors.
   window( location size, color foreground, color background )
      : size{ size }, foreground{ foreground }, background{ background }
   {}
   
   /// \brief
   /// write a pixel
   /// \details
   /// This function writes a the color col to the pixel at location loc.
   /// If either the color is transparent, or the location is outside the window 
   /// the call has no effect. When no color is specificied, the window's
   /// foreground color is used.
   ///
   /// When buffering is specified ( buf == buffered ) the actual writing
   /// can be delayed until the next flush() call.   
   void write( 
      location pos, 
      color col 
   ){
      if(  ( ! col.is_transparent )
        && ( pos.x >= 0 ) && ( pos.x < size.x ) 
        && ( pos.y >= 0 ) && ( pos.y < size.y ) 
      ){
         write_implementation( pos, col );
      }   
   }
   
   /// \brief
   /// flush the pixel buffer
   /// \details
   /// This function fluhses the pixel buffer: it writes pixels that
   /// have not yet been written.
   /// Flushing might occur as a side-effect of other operations.
   virtual void flush(){ }
   
   /// \brief
   /// write a rectangle of pixels
   /// \details
   /// This function writes a rectangle of pixels, as specified by img,
   /// at location pos.        
   ///
   /// When buffering is specified ( buf == buffered ) the actual writing
   /// can be delayed until the next flush() call.   
   void write( 
      location pos, 
      const image & img
   ){                 
      for( uint_fast16_t x = 0; x < img.size.x; ++x ){
         for( uint_fast16_t y = 0; y < img.size.y; ++y ){
            auto loc = hwlib::location( x, y );
            write( pos + loc, img[ loc ] );
         }
      }
   }

   #ifndef DOXYGEN // hide from doxygen
   void write( location pos ){
      write( pos, foreground );
   }   
   #endif 
   
   /// \brief
   /// clear the window
   /// \details
   /// This function clears the windows by writing the background
   /// color to all pixels.
   /// The default implementation writes to all pixels in sequence.
   /// A concrete window can probably provide a faster implementation.
   ///
   /// When buffering is specified ( buf == buffered ) the actual clearing
   /// can be delayed until the next flush() call.    
   virtual void clear( ){
      for( uint_fast16_t x = 0; x < size.x; ++x ){
         for( uint_fast16_t y = 0; y < size.y; ++y ){
            write( location{ x, y }, background );    
         }                 
      }        
   }
   
};

}; // namespace hwlib
