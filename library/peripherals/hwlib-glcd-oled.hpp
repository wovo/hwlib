// ==========================================================================
//
// File      : hwlib-glcd-oled.hpp
// Part of   : C++ hwlib library for close-to-the-hardware OO programming
// Copyright : wouter@voti.nl 2017
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

// included only via hwlib.hpp, hence no multipl-include guard is needed

// this file contains Doxygen lines
/// @file

namespace hwlib {
   

/// \brief
/// Oled B/W graphics LCD
/// \details
/// This class implements an interface to an 128 x 64 pixel
/// monochrome (on/off) OLED display. These displays are available
/// in various colcors (green, red, white, etc.).
/// The interface is I2C.
/// The driver chip is an SSD1306.
///
/// The interface is buffered: all writes
/// are buffered in memory until flush() is called.
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
/// \image html oled.jpg
///
class glcd_oled : public window {
private:
   i2c_bus & bus;
   
   // the 7-bit i2c address of the controller
   uint8_t address;
   
   // current cursor setting in the controller;
   // used to avoid explicit cursor updates when such are not needed
   uint8_t cursor_x, cursor_y;
   
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
   
   void command( uint8_t d ){
      uint8_t data[] = { 0x80, d };
      bus.write( 
         address, 
         data, 
         sizeof( data ) / sizeof( uint8_t ) 
      );      
   } 
   
   void command( uint8_t d0, uint8_t d1 ){
      uint8_t data[] = { 0x80, d0, 0x80, d1 };
      bus.write( 
         address, 
         data, 
         sizeof( data ) / sizeof( uint8_t ) 
      );    
   } 	
   
   void command( uint8_t d0, uint8_t d1, uint8_t d2 ){
      uint8_t data[] = { 0x80, d0, 0x80, d1, 0x80, d2 };
      bus.write( 
         address, 
         data, 
         sizeof( data ) / sizeof( uint8_t ) 
      );     
   } 	
   
   void pixels( 
      uint8_t x, 
      uint8_t y, 
      uint8_t d 
   ){
      if(( x != cursor_x ) || ( y != cursor_y )){
         command( COLUMNADDR,  x,  127 );
         command( PAGEADDR,    y,    7 );
         cursor_x = x;
         cursor_y = y;
      }   
      uint8_t data[] = { 0x40, d };
      bus.write( 
         address, 
         data, 
         sizeof( data ) / sizeof( uint8_t ) 
      ); 
      cursor_x++;      
   }
   
   uint8_t buffer[ 128 * 64 / 8 ];
   
   void write_implementation( 
      location pos, 
      color col
   ) override {
      int a = pos.x + ( pos.y / 8 ) * size.x;

      if( col == foreground ){ 
         buffer[ a ] |=  ( 0x01 << (pos.y % 8 ));  
      } else {
         buffer[ a ] &= ~( 0x01 << ( pos.y % 8 )); 
      }   
   }
   
public:
   
   glcd_oled( i2c_bus & bus, uint_fast8_t address = 0x3C ):
      window( location( 128, 64 ), black, white ),
      bus( bus ),
      address( address ),
      cursor_x( 255 ), cursor_y( 255 )
   {
      static constexpr const uint8_t init_sequence[] = {
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
         sizeof( init_sequence ) / sizeof( uint8_t ) 
      );     
   }
   
   virtual void clear(){   
      for( int y = 0; y < 64 / 8; y++ ){
         for( int x = 0; x < 128; x++ ){
            buffer[ x + 128 * y ] = 0x00;
         }                 
      }         
   }   
   
   /// write the pixel buffer to the oled
   //
   /// All write (and clear) calls change only the in-memory pixel
   /// buffer. This call writes this pixel buffer to the oled.
   void flush(){
      command( COLUMNADDR,  0,  127 );
      command( PAGEADDR,    0,    7 );   
      for( int y = 0; y < 64 / 8; y++ ){
         for( int x = 0; x < 128; x++ ){
            uint8_t d = buffer[ x + 128 * y ];
            uint8_t data[] = { 0x40, d };
            bus.write( 
               address, 
               data, 
               sizeof( data ) / sizeof( uint8_t ) 
            );
         }   
		 
		 // yield the CPU when this is run with an I2C implementation 
		 // that doesn't ever wait to
		 //    - prevent polling timing from missing an overflow
		 //    - keep other threads in a in a multi-threading context alive
         wait_us( 0 );		 
      }         
   }     
   
}; // class glcd_oled
   
}; // namespace hwlib

