// ==========================================================================
//
// File      : hwlib-graphics.hpp
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


/// a graphics window
/// 
/// This class abstracts the interface to a graphic window.
///
/// Window operations (clear, write) can be buffered.
/// A flush() call is required to make sure that all previous operations
/// take effect.
class window {
private:

   /// write a pixel - implementation
   /// 
   /// This NVI function writes a the color col to the pixel at location loc.
   /// Loc is guaranteed to be within the window, and the color
   /// is guranteed to be not transparent.
   virtual void write_implementation( 
      xy pos, 
      color col
   ) = 0;      
   
public:

   /// the size of the window
   /// 
   /// This is the size of the window: the number of pixels
   /// in the x and y direction.
   const xy size;
   
   /// the background color of the window
   /// 
   /// This is the color use by the clear() function.
   color background;
   
   /// the foreground color of the window
   /// 
   /// This color could be used to draw monochrome graphics.
   color foreground;
   
   /// construct a window by specifying its size and foreground and background colors.
   ///
   /// The default is white foreground on black background
   window( xy size, color foreground = white, color background = black )
      : size{ size }, background{ background }, foreground{ foreground }
   {}
   
   /// write a pixel
   /// 
   /// This function writes a the color col to the pixel at location pos.
   /// If either the color is transparent, or the location is outside the window 
   /// the call has no effect. When no color is specified, the window's
   /// foreground color is used.  
   ///@{
   void write( 
      xy pos, 
      color col 
   ){
      if(  ( ! col.is_transparent )
        && ( pos.x >= 0 ) && ( pos.x < size.x ) 
        && ( pos.y >= 0 ) && ( pos.y < size.y ) 
      ){
         write_implementation( pos, col );
      }   
   }
   void write( 
      xy pos 
   ){
      write( pos, foreground );
   }
   ///@}

   /// flush the pixel buffer
   ///
   /// This function fluhses the pixel buffer: it writes pixels that
   /// have not yet been written.
   /// Flushing might occur as a side-effect of other operations.
   virtual void flush() = 0;
   
   /// write a rectangle of pixels
   /// 
   /// This function writes a rectangle of pixels, as specified by img,
   /// at location pos.        
   void write( 
      xy pos, 
      const image & img
   ){                 
      for( uint_fast16_t x = 0; x < img.size.x; ++x ){
         for( uint_fast16_t y = 0; y < img.size.y; ++y ){
            auto loc = hwlib::xy( x, y );
            write( pos + loc, img[ loc ] );
         }
      }
   }
   
   /// clear the window
   /// 
   /// This function clears the windows by writing the background
   /// color to all pixels.
   /// The default implementation writes to all pixels in sequence.
   /// A concrete window can probably provide a faster implementation.    
   virtual void clear( ){
      for( uint_fast16_t x = 0; x < size.x; ++x ){
         for( uint_fast16_t y = 0; y < size.y; ++y ){
            write( xy{ x, y }, background );    
         }                 
      }        
   }
   
}; // class window

}; // namespace hwlib
