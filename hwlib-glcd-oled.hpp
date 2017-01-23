// ==========================================================================
//
// File      : hwlib-glcd-oled.hpp
// Part of   : hwlib library for V1OOPC and V1IPAS
// Copyright : wouter@voti.nl 2016
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================
/// @file

#ifndef HWLIB_GLCD_OLED_H
#define HWLIB_GLCD_OLED_H

#include <hwlib-graphics.hpp>

namespace hwlib {
   
/// Oled B/W graphics LCD
//
/// This class implements an interface to an 128 x 64 pixel
/// monochrome (on/off) OLED display. These displays are available
/// in various colcors (green, red, white, etc.).
/// The interface is I2C.
/// The driver chip is an SSD1306.
///
/// When the PCB has regulator (3-legged component) the power can be 3 - 5V. 
/// If it hasn't, you can use only 3.3V.
///
/// There are variations of this display with more pins, which 
/// have more interface options (SPI as alternative interface).
///
/// This type of display is reasonably priced 
/// and available from lots of sources.
///
/// \image html lcdoled-empty.jpg
///
class glcd_oled : public window {
private:
   i2c_bus & bus;
   
   // the 7-bit i2c address of the controller
   fast_byte address;
   
   // current cursor setting in the controller;
   // used to avoid explicit cursor updates when such are not needed
   fast_byte cursor_x, cursor_y;
   
   // SSD1306 commands
   static constexpr const uint8_t SETCONTRAST                           = 0x81;
   static constexpr const uint8_t DISPLAYALLON_RESUME                   = 0xA4;
   static constexpr const uint8_t DISPLAYALLON                          = 0xA5;
   static constexpr const uint8_t NORMALDISPLAY                         = 0xA6;
   static constexpr const uint8_t INVERTDISPLAY                         = 0xA7;
   static constexpr const uint8_t DISPLAYOFF                            = 0xAE;
   static constexpr const uint8_t DISPLAYON                             = 0xAF;
   static constexpr const uint8_t SETDISPLAYOFFSET                      = 0xD3;
   static constexpr const uint8_t SETCOMPINS                            = 0xDA;
   static constexpr const uint8_t SETVCOMDETECT                         = 0xDB;
   static constexpr const uint8_t SETDISPLAYCLOCKDIV                    = 0xD5;
   static constexpr const uint8_t SETPRECHARGE                          = 0xD9;
   static constexpr const uint8_t SETMULTIPLEX                          = 0xA8;
   static constexpr const uint8_t SETLOWCOLUMN                          = 0x00;
   static constexpr const uint8_t SETHIGHCOLUMN                         = 0x10;
   static constexpr const uint8_t SETSTARTLINE                          = 0x40;
   static constexpr const uint8_t MEMORYMODE                            = 0x20;
   static constexpr const uint8_t COLUMNADDR                            = 0x21;
   static constexpr const uint8_t PAGEADDR                              = 0x22;
   static constexpr const uint8_t COMSCANINC                            = 0xC0;
   static constexpr const uint8_t COMSCANDEC                            = 0xC8;
   static constexpr const uint8_t SEGREMAP                              = 0xA0;
   static constexpr const uint8_t CHARGEPUMP                            = 0x8D;
   static constexpr const uint8_t EXTERNALVCC                           = 0x01;
   static constexpr const uint8_t SWITCHCAPVCC                          = 0x02;
   static constexpr const uint8_t ACTIVATE_SCROLL                       = 0x2F;
   static constexpr const uint8_t DEACTIVATE_SCROLL                     = 0x2E;
   static constexpr const uint8_t SET_VERTICAL_SCROLL_AREA              = 0xA3;
   static constexpr const uint8_t RIGHT_HORIZONTAL_SCROLL               = 0x26;
   static constexpr const uint8_t LEFT_HORIZONTAL_SCROLL                = 0x27;
   static constexpr const uint8_t VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL  = 0x29;
   static constexpr const uint8_t VERTICAL_AND_LEFT_HORIZONTAL_SCROLL   = 0x2A;   
   
   void command( byte d ){
      byte data[] = { 0x80, d };
      bus.write( 
         address, 
         data, 
         sizeof( data ) / sizeof( byte ) 
      );      
   } 	
   
   void command( byte d0, byte d1 ){
      byte data[] = { 0x80, d0, 0x80, d1 };
      bus.write( 
         address, 
         data, 
         sizeof( data ) / sizeof( byte ) 
      );    
   } 	
   
   void command( byte d0, byte d1, byte d2 ){
      byte data[] = { 0x80, d0, 0x80, d1, 0x80, d2 };
      bus.write( 
         address, 
         data, 
         sizeof( data ) / sizeof( byte ) 
      );     
   } 	
   
   void pixels( 
      byte x, 
      byte y, 
      byte d 
   ){
      if(( x != cursor_x ) || ( y != cursor_y )){
         command( COLUMNADDR,  x,  127 );
         command( PAGEADDR,    y,    7 );
         cursor_x = x;
         cursor_y = y;
      }   
      byte data[] = { 0x40, d };
      bus.write( 
         address, 
         data, 
         sizeof( data ) / sizeof( byte ) 
      ); 
      cursor_x++;      
   }
   
   uint8_t buffer[ 128 * 64 / 8 ];

   void write_implementation( location pos, color col ) override {
      int a = pos.x + ( pos.y / 8 ) * size.x;

      if( col == foreground ){ 
         buffer[ a ] |=  ( 0x01 << (pos.y % 8 ));  
      } else {
         buffer[ a ] &= ~( 0x01 << ( pos.y % 8 )); 
      }   
      pixels( pos.x, pos.y / 8, buffer[ a ] );      
   }
   
public:
   
   glcd_oled( i2c_bus & bus, fast_byte address = 0x3C ):
      window( location( 128, 64 ), black, white ),
      bus( bus ),
      address( address ),
      cursor_x( 255 ), cursor_y( 255 )
   {
      static constexpr const byte init_sequence[] = {
         0x80,  DISPLAYOFF,                   
         0x80,  SETDISPLAYCLOCKDIV,   0x80,   
         0x80,  SETMULTIPLEX,         0x3F,   
         0x80,  SETDISPLAYOFFSET,     0x00,   
         0x80,  SETSTARTLINE        | 0x00,  
         0x80,  CHARGEPUMP,           0x14,   
         0x80,  MEMORYMODE,           0x00,   
         0x80,  SEGREMAP            | 0x01,
         0x80,  COMSCANDEC,
         0x80,  SETCOMPINS,           0x12,   
         0x80,  SETCONTRAST,          0xCF,   
         0x80,  SETPRECHARGE,         0xF1,  
         0x80,  SETVCOMDETECT,        0x40,   
         0x80,  DISPLAYALLON_RESUME,          
         0x80,  NORMALDISPLAY,                
         0x80,  DISPLAYON                     
      };
      wait_ms( 20 );
      bus.write( 
         address, 
         init_sequence, 
         sizeof( init_sequence ) / sizeof( byte ) 
      );     
   }
   
   // can be done 3 times faster ...
   virtual void clear(){
      command( COLUMNADDR,  0,  127 );
      command( PAGEADDR,    0,    7 );   
      for( int y = 0; y < 64 / 8; y++ ){
         for( int x = 0; x < 128; x++ ){
            buffer[ x + 128 * y ] = 0x00;
            byte data[] = { 0x40, 0x00 };
            bus.write( 
               address, 
               data, 
               sizeof( data ) / sizeof( byte ) 
            );
         }                 
      }         
   }   
   
}; // class glcd_oled
   
}; // namespace hwlib

#endif // HWLIB_GLCD_OLED_H
