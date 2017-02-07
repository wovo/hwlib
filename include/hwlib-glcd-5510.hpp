// ==========================================================================
//
// File      : hwlib-console.hpp
// Part of   : hwlib library for V1OOPC and V1IPAS
// Copyright : wouter@voti.nl 2016
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================
/// @file

#ifndef HWLIB_GLCD_5510_H
#define HWLIB_GLCD_5510_H

#include <hwlib-graphics.hpp>

namespace hwlib {
   
/// Nokia 5510 B/W graphics LCD library
//
/// This class implements an interface to the type of LCD 
/// that was used in older Nokia telephones.
/// It is a 84 columns x 48 lines black-and-white LCD.
///
/// This type of LCD is cheap and available from lots of sources,
/// but the quality is often abominable.
///
/// \image html lcd5510-empty.jpg
///
class glcd_5510 : public window {
private:
   pin_out & sce;
   pin_out & res;
   pin_out & dc;
   pin_out & sdin;
   pin_out & sclk;
	
   void send_byte( unsigned char d ){
      int i;
      for( i = 0; i < 8; i++ ){
         sdin.set( d & 0x80 );
         sclk.set( 1 );
         d = d << 1;
         sclk.set( 0 );
      }
   }    
   
   void command( unsigned char d ){
      dc.set( 0 );
      sce.set( 0 );
      send_byte( d );
      sce.set( 1 );
   } 	

   void data( unsigned char d ){
      dc.set( 1 );
      sce.set( 0 );
      send_byte( d );
      sce.set( 1 );
   } 	
   
   void pixels( 
      unsigned char x, 
      unsigned char y, 
      unsigned char d 
   ){
      command( 0x80 | x );   
      command( 0x40 | y );  
      data( d );
   }

public:
   
   glcd_5510( 
      pin_out & sce,
      pin_out & res,
      pin_out & dc,
      pin_out & sdin,
      pin_out & sclk   
   )
      : window{ location{ 84, 48 }, black, white },
      sce( sce ), res( res ), dc( dc ), sdin( sdin ), sclk( sclk )
   {
   
      sclk.set( 0 );
      wait_ms( 1 );
      sce.set( 1 );
      wait_ms( 1 );
      res.set( 0 );
      wait_ms( 1 );
      res.set( 1 ); 
      wait_ms( 1 );
	  
	      // initialization according to
	      // https://www.sparkfun.com/products/10168 - nee, andere
      command( 0x21 );  // select exteded instructions
      command( 0xC8 );  // Vop = 110000b
      command( 0x06 );  // TCx = 00b
      command( 0x13 );  // BSx = 100b
      command( 0x20 );  // select basic instructions, horizontal addressing
      command( 0x0C );	// normal mode   
   }	
   
private:   

   unsigned char pixel_buffer[ 504 ];

   void write_implementation( location pos, color col ) override {
      unsigned int a = pos.x + ( pos.y / 8 ) * 84;
      unsigned int m = 1 << ( pos.y % 8 );
   
      if( col == black ){
         pixel_buffer[ a ] |= m;
      } else {     
         pixel_buffer[ a ] &= ~m;
      }
   
      pixels( pos.x, pos.y / 8, pixel_buffer[ a ] );         
   }
   
public:   
   
   void clear() override {
      int i;
      unsigned char d = (( background == white ) ? 0 : 0xFF );
      command( 0x80 | 0 );   
      command( 0x40 | 0 );  
      for( i = 0; i < 504; i++ ){
         pixel_buffer[ i ] = d;
         data( d );
      }         
   }
   
}; // class glcd_5510
   
}; // namespace hwlib

#endif // HWLIB_GLCD_5510_H
