// ==========================================================================
//
// File      : hwlib-demo.hpp
// Part of   : hwlib library for V1OOPC and V1IPAS
// Copyright : wouter@voti.nl 2016
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================
/// @file

#ifndef HWLIB_DEMO_H
#define HWLIB_DEMO_H

#include "hwlib-pin.hpp"
#include "hwlib-port.hpp"
#include "hwlib-wait.hpp"

namespace hwlib {

/// blink function
//
/// This function blinks the pin: ms milliseconds on, and
/// ms milliseconds off. It never returns.
void HWLIB_WEAK HWLIB_NORETURN blink( pin_out & pin, uint_fast16_t  ms = 200 ){
   for(;;){
      pin.set( 1 );
      wait_ms( ms );      
      pin.set( 0 );
      wait_ms( ms );      
   }      
}

/// kitt function
//
/// This function shows a kitt display on the pins of a port.
/// Each LED is on for m milliseconds. It never returns.
void HWLIB_WEAK HWLIB_NORETURN kitt( port_in_out & port, uint_fast16_t  ms = 100 ){
   port.direction_set_output();
   for(;;){
      for( uint_fast8_t  i = 0; i < port.number_of_pins(); ++i ){
         port.set( 0x01 << i );      
         wait_ms( ms );
      }
      for( uint_fast8_t  i = port.number_of_pins() - 2; i > 0; --i ){
         port.set( 0x01 << i );      
         wait_ms( ms );
      }
   }      
}
void HWLIB_WEAK HWLIB_NORETURN kitt( port_out & port, uint_fast16_t ms = 100 ){
   for(;;){
      for( uint_fast8_t  i = 0; i < port.number_of_pins(); ++i ){
         port.set( 0x01 << i );      
         wait_ms( ms );
      }
      for( uint_fast8_t  i = port.number_of_pins() - 2; i > 0; --i ){
         port.set( 0x01 << i );      
         wait_ms( ms );
      }
   }      
}
void HWLIB_WEAK HWLIB_NORETURN kitt( port_oc & port, uint_fast16_t ms = 100 ){
   for(;;){
      for( uint_fast8_t  i = 0; i < port.number_of_pins(); ++i ){
         port.set( 0x01 << i );      
         wait_ms( ms );
      }
      for( uint_fast8_t  i = port.number_of_pins() - 2; i > 0; --i ){
         port.set( 0x01 << i );      
         wait_ms( ms );
      }
   }      
}

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

/// random lines demo
//
/// This functions repeats the following actions:
/// - clears the window
/// - draws a border
/// - draws 30 random lines,
/// - waits half a second.
void HWLIB_WEAK HWLIB_NORETURN graphics_random_lines( 
   window & w, 
   uint_fast16_t n_lines = 30 
){
   for(;;){
      w.clear();
      for( uint_fast16_t x = 0; x < w.size.x; x++ ){
         w.write( hwlib::location{ x,            0 } );
         w.write( hwlib::location{ x, w.size.y - 1 } );
      }   
      for( uint_fast16_t y = 0; y < w.size.y; y++ ){
         w.write( hwlib::location{            0, y } );
         w.write( hwlib::location{ w.size.x - 1, y } );
      }   
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
         hwlib::wait_ms( 500 );
      }
   }  
}

/// random circles demo
//
/// This functions repeats the following actions:
/// - clears the window
/// - draws n_circles (default is 30) random circles 
///      (which might be partially out-of-screen),
/// - waits half a second.
void HWLIB_WEAK HWLIB_NORETURN graphics_random_circles( 
   window & w, 
   uint_fast16_t n_circles = 30 
){
   for(;;){
      w.clear();
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
         hwlib::wait_ms( 500 );
      }
   }  
}

}; // namespace hwlib

#endif // HWLIB_PIN_H