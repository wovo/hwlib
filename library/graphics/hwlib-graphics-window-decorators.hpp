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
/// a window_part (subwindow of a larger window)
/// \details
/// A window_part is a rectangular part of a larger window.
class window_part : public window {
private:
   window & w;
   location start;
   
   void write_implementation( location pos, color col ) override {
      w.write( start + pos, col );
   }      

   void flush() override {
      w.flush();
   }      
   
public:      
   /// \brief
   /// create a window_part from a larger window, its origin and its size
   /// \details
   /// This call constructs a subwindow from a window, the start 
   /// (top-left pixel) of the subwindow, and the size of the subwindow.
   /// The foreground and background color are copied from the larger
   /// window.
   window_part( window &w, location start, location size ):
      window( size, w.foreground, w.background ),
      w( w ),
      start( start )
   {}   
      
};


// ==========================================================================

/// \brief
/// window_invert (invert writes to a window)
/// \details
/// A window_inverts writes inverted to its larger window.
class window_invert : public window {
private:
   window & w;
   
   void write_implementation( 
      location pos, 
      color col
   ) override {
      w.write( pos, - col );
   }      

   void flush() override {
      w.flush();
   }      
   
public:      
   /// \brief
   /// create a window_invert from a window
   /// \details
   /// This call constructs a window_invert from a window.
   /// The foreground and background color are copied from the larger
   /// window, but writes to the window_invert write the invert
   /// pixel to the underlying window.
   window_invert( window &w ):
      window( w.size, w.foreground, w.background ),
      w( w )
   {}   

};

}; // namespace hwlib
