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
/// random lines demo
/// \details
/// This functions repeats the following actions:
/// - clears the window
/// - draws a border
/// - draws 30 random lines,
/// - waits half a second.
void graphics_random_lines( 
   window & w, 
   uint_fast16_t n_lines = 30
);

/// \brief
/// random circles demo
/// \details
/// This functions repeats the following actions:
/// - clears the window
/// - draws n_circles (default is 30) random circles 
///      (which might be partially out-of-screen),
/// - waits half a second.
void graphics_random_circles( 
   window & w, 
   uint_fast16_t n_circles = 30 
);

#ifdef HWLIB_ONCE 

// hide from Doxygen
#ifndef DOXYGEN

uint_fast32_t HWLIB_WEAK rand(){ 
   static uint_fast32_t n = 0;
   n = n * 214013L + 2531011L; 
   return ( n >> 16) & 0x7fff; 
}

uint_fast32_t HWLIB_WEAK random_in_range( 
   uint_fast32_t min, 
   uint_fast32_t max 
){
   auto x = rand();
   x = x % ( max - min + 1 ); 
   return min + x;
}

#endif

void HWLIB_NORETURN graphics_random_lines( 
   window & w, 
   uint_fast16_t n_lines 
){
   for(;;){
      w.clear();
      for( uint_fast16_t x = 0; x < w.size.x; x++ ){
         w.write( hwlib::location{ 
            x,            
            0 } );
         w.write( hwlib::location{ 
            x, 
            static_cast< uint_fast16_t >( w.size.y - 1 ) } );
      }   
      for( uint_fast16_t y = 0; y < w.size.y; y++ ){
         w.write( hwlib::location{            
            0, 
            y } );
         w.write( hwlib::location{ 
            static_cast< uint_fast16_t >( w.size.x - 1 ), 
            y } );
      }   
      w.flush();			
      for( uint_fast16_t n = 0; n < n_lines; n++ ){
         const uint_fast16_t x  = random_in_range( 0, w.size.y );
         const uint_fast16_t x1 = random_in_range( 0, w.size.x );
         const uint_fast16_t y  = random_in_range( 0, w.size.y );
         const uint_fast16_t y1 = random_in_range( 0, w.size.y );
         auto line = hwlib::line( 
            hwlib::location{  x,  y },
            hwlib::location{ x1, y1 }, 
            w.foreground 
         );
         line.draw( w );
         w.flush();			
         hwlib::wait_ms( 500 );
      }
   }  
}

void HWLIB_NORETURN graphics_random_circles( 
   window & w, 
   uint_fast16_t n_circles 
){
   for(;;){
      w.clear();
      w.flush();		  
      for( uint_fast16_t n = 0; n < n_circles; n++ ){
         const uint_fast16_t x  = random_in_range( 10, w.size.x - 10 );
         const uint_fast16_t y  = random_in_range( 10, w.size.y - 10 );
         const uint_fast16_t s  = random_in_range(  0, w.size.y / 4 );
         auto circle = hwlib::circle( 
            hwlib::location{  x,  y },
            s,
            w.foreground 
         );
         circle.draw( w );
         w.flush();
         hwlib::wait_ms( 500 );
      }
   }  
}

#endif // #ifdef HWLIB_ONCE

}; // namespace hwlib
