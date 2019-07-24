// ==========================================================================
//
// File      : hwlib-graphics-window_demos.hpp
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

/// random lines demo
/// 
/// This functions repeats the following actions:
/// - clears the window
/// - draws a 1-pixel border
/// - draws n random lines (default is 30),
///   of the specified color (default is the window foreground)
/// - waits half a second.
void graphics_random_lines( 
   window & w, 
   uint_fast16_t n = 30,
   const color & c = unspecified      
);

/// random circles demo
/// 
/// This functions repeats the following actions:
/// - clears the window
/// - draws a 1-pixel border
/// - draws n circles (default is 30) random circles 
///      (which might be partially out-of-screen),
///   of the specified color (default is the window foreground)
/// - waits half a second.
void graphics_random_circles( 
   window & w, 
   uint_fast16_t n = 30,
   const color & c = unspecified  
);


// ===========================================================================
//
// implementations
//
// ===========================================================================

#ifdef _HWLIB_ONCE

void HWLIB_NORETURN graphics_random_lines( 
   window & w, 
   uint_fast16_t n_lines,
   const color & c   
){
   for(;;){
      w.clear();			
      for( 
         int_fast16_t n = 0; 
         n < static_cast< int_fast16_t >( n_lines ); 
         n++ 
      ){
         line( 
            random_in( w.size ),
            random_in( w.size ),
            c
         ).draw( w );
         w.flush();			
         wait_ms( 500 );
      }
   }  
}

void HWLIB_NORETURN graphics_random_circles( 
   window & w, 
   uint_fast16_t n_circles,
   const color & c    
){
   for(;;){
      w.clear();
      w.flush();		  
      for( uint_fast16_t n = 0; n < n_circles; n++ ){
         circle( 
            random_in( w.size ),
            random_in(  0, w.size.y / 4 ),
            c
         ).draw( w );
         w.flush();
         wait_ms( 500 );
      }
   }  
}

#endif // #ifdef _HWLIB_ONCE

}; // namespace hwlib
