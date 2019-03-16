// ==========================================================================
//
// File      : hwlib-graphics-window-decorators.hpp
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

/// a window_part (subwindow of a larger window)
/// 
/// A window_part is a rectangular part of a larger window.
class window_part : public window {
private:

   window & w;
   xy start;
   
   void write_implementation( xy pos, color col ) override {
      w.write( start + pos, col );
   }      

   void flush() override {
      w.flush();
   }      
   
public:      

   /// create a window_part from a larger window, its origin and its size
   /// 
   /// This call constructs a subwindow from a window, the start 
   /// (top-left pixel) of the subwindow, and the size of the subwindow.
   /// The foreground and background color are copied from the larger
   /// window.
   window_part( window &w, xy start, xy size ):
      window( size, w.foreground, w.background ),
      w( w ),
      start( start )
   {}   
      
}; // class window_part


// ==========================================================================

/// window_invert (invert writes to a window)
/// 
/// A window_inverts writes inverted to its larger window.
class window_invert : public window {
private:

   window & w;
   
   void write_implementation( 
      xy pos, 
      color col
   ) override {
      w.write( pos, - col );
   }      

   void flush() override {
      w.flush();
   }      
   
public:      

   /// create a window_invert from a window
   /// 
   /// This call constructs a window_invert from a window.
   /// The foreground and background color are the inverse 
   /// of those of the minion window, and writes to the 
   /// window_invert write the inverted
   /// pixel color to the minion window.
   window_invert( window &w ):
      window( w.size, - w.foreground, - w.background ),
      w( w )
   {}   

}; // class class window_invert


}; // namespace hwlib
