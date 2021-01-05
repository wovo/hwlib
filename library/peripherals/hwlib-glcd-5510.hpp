// ==========================================================================
//
// File      : hwlib-console.hpp
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
   
/// Nokia 5510 B/W graphics LCD
/// 
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
      for( uint_fast8_t i = 0; i < 8; i++ ){
         sdin.write( d & 0x80 );
         sclk.write( 1 );
         d = d << 1;
         sclk.write( 0 );
      }
   }    
   
   void command( unsigned char d ){
      dc.write( 0 );
      sce.write( 0 );
      send_byte( d );
      sce.write( 1 );
   }    

   void data( unsigned char d ){
      dc.write( 1 );
      sce.write( 0 );
      send_byte( d );
      sce.write( 1 );
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
   
   /// create a 5510 LCD
   /// 
   /// This constructor creates a 5510 LCD from its interface pins.
   glcd_5510( 
      pin_out & sce,
      pin_out & res,
      pin_out & dc,
      pin_out & sdin,
      pin_out & sclk   
   )
      : window{ xy{ 84, 48 }, black, white },
      sce( sce ), res( res ), dc( dc ), sdin( sdin ), sclk( sclk )
   {
   
      sclk.write( 0 );
      wait_ms( 1 );
      sce.write( 1 );
      wait_ms( 1 );
      res.write( 0 );
      wait_ms( 1 );
      res.write( 1 ); 
      wait_ms( 1 );
     
         // initialization according to
         // https://www.sparkfun.com/products/10168 - nee, andere
      command( 0x21 );  // select exteded instructions
      command( 0xC8 );  // Vop = 110000b
      command( 0x06 );  // TCx = 00b
      command( 0x13 );  // BSx = 100b
      command( 0x20 );  // select basic instructions, horizontal addressing
      command( 0x0C );  // normal mode   
   }   
   
private:   

   unsigned char pixel_buffer[ 504 ];

   void write_implementation( 
      xy pos, 
      color col
   ) override {
      uint_fast8_t a = pos.x + ( pos.y / 8 ) * 84;
      uint_fast8_t m = 1 << ( pos.y % 8 );
   
      if( col == black ){
         pixel_buffer[ a ] |= m;
      } else {     
         pixel_buffer[ a ] &= ~m;   
      }
   }
   
public:   
   
   void clear_implementation( color c ) override {
      unsigned char d = (( c == white ) ? 0 : 0xFF );
      command( 0x80 | 0 );   
      command( 0x40 | 0 );  
      for( uint_fast16_t i = 0; i < 504; i++ ){
         pixel_buffer[ i ] = d;
      }         
   }
   
   void flush() override {
      command( 0x80 | 0 );   
      command( 0x40 | 0 );  
      for( uint_fast16_t i = 0; i < 504; i++ ){
         data( pixel_buffer[ i ] );
      }         
   }
   
}; // class glcd_5510
   
}; // namespace hwlib
