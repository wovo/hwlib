// ==========================================================================
//
// File      : hwlib-hd44780.hpp
// Part of   : hwlib library for V1OOPC and V1IPAS
// Copyright : wouter@voti.nl 2016
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================
/// @file

#ifndef HWLIB_HD44780_H
#define HWLIB_HD44780_H

#include "hwlib-pin.hpp"
#include "hwlib-console.hpp"

namespace hwlib {
   
/// hd44780 character LCD interface 
//
/// This class implements an interface to an hd44780 character LCD.  
///
/// \image html hd44780-picture.jpg
///
/// The hd44780 is the standard chip for interfacing small dot-character 
/// LCD interfaces.
/// It can display the ASCII table characters, 8 characters (0..7) 
/// that can be user-defined as 5x7 pixels, and a an upper 128 characters
/// (128...255) that vary with the chip variant, often Japanese characters.
///
/// The chip and its digital pins run at 5V. 
/// The contrast input can in most cases be connected to 0V (ground), but
/// better is to use a 10k potentiometer between 0V and 5V. Some
/// displays (mostly extended-temperature-range types) need the lower 
/// size of this potentiometer tied to a negative voltage, for instance -5V.
///
/// The digital interface to the chip has 8 data lines, but the chip can be
/// configured to use only 4. This adds some complexity to the driver 
/// software and slows it down a little, but the saving of 4 micro-controller
/// more than compensates for this, hence nearly all software 
/// (including this driver) for is for the 4-bit interface.
/// Note for the 4-bit interface the 4 highest data pins (D4..D7) are used.
/// The lower 4 can be left unconnected.
///
/// The chip has some locations that can be writen and also read back, 
/// but this offers little advantage, so most software (including this driver)
/// only writes to the chip, thus saving another pin.
/// Hence 6 pins (+ ground and 5V) 
/// are needed to interface to an hd44780 display:
/// 4 data lines, the R/S line (selects between command and data), 
/// and the E line (a strobe for the command).
///
/// \image html hd44780-connection.png
///
/// (Some larger displays use not one but two hd44780 chips. 
/// This interface is not compatible with such LCDs.)
///
/// Most hd44780 LCDs have a single row of connections,
/// with the following pinout:
///
/// \image html hd44780-pinout.jpg
///
/// But as always, check the datasheet (in this case of the LCD) to be sure!
///
/// The hd44780 implements the ostream interface, but it doesn't scroll:
/// while the cursor is outside the visible characters (beyond the end of the line,
/// or beyond the number of lines) any character writes will be ignored.
/// Some characters are treated special:
///    - '\n' clears the rest of the line, and then 
///      moves to the first position of the next line
///    - '\r' puts the cursor at the start of the current line
///    - '\c' moves the cursor to the top-left position 
///
/// The best way to get a flicker-free display is to overwite 
/// instead of clear-and-then-write:
/// use '\c' to got to the 'origin', then rewrite the whole display, 
/// using '\n' to go to a next line (because it clears the remainder of the line).
///
/// references:
///    - <A HREF="https://en.wikipedia.org/wiki/Hitachi_HD44780_LCD_controller">
///       Hitachi HD44780 LCD controller</A> (wikipedia)
///    - <A HREF="https://www.sparkfun.com/datasheets/LCD/HD44780.pdf">
///       HD44780U data sheet</A> (pdf)
/// 
class hd44780 : public console {
private:
   pin_out & pin_e;
   pin_out & pin_rs;
   port_out & port_data;
   
   void write4( unsigned char n ){
      wait_us( 10 );
      port_data.set( n );
      wait_us( 20 );
      pin_e.set( 1 );
      wait_us( 20 );
      pin_e.set( 0 );
      wait_us( 100 );  // enough for most instructions
   }

   void write8( bool is_data, unsigned char b ){
      pin_rs.set( is_data );
      write4( b >> 4 );
      write4( b );
   }      
           
public:

   /// construct an interface to an hd44780 chip
   //
   /// This constructor creates an interface to 
   /// an hd44780 LCD controller from the RS and E pins, and the 4-bit port
   /// to the D4..D8 pins, and the number of lines and characters per line,
   /// and initializes the controller.
   hd44780( 
      pin_out & rs, 
      pin_out & e, 
      port_out & data, 
      int lines, 
      int columns
    ):
      console{ lines, columns },
      pin_e( e ), 
      pin_rs( rs ), 
      port_data( data )
   {
      // give LCD time to wake up
      pin_e.set( 0 );
      pin_rs.set( 0 );
      wait_ms( 100  );

      // interface initialisation: make sure the LCD is in 4 bit mode
      // (magical sequence, taken from the HD44780 datasheet)
      write4( 0x03 );
      wait_ms( 15 );
      write4( 0x03 );
      wait_us( 100 );
      write4( 0x03 );
      write4( 0x02 );     // 4 bit mode

      // functional initialisation
      command( 0x28 );    // 4 bit mode, 2 lines, 5x8 font
      command( 0x0C );    // display on, no cursor, no blink
      clear();            // clear display, 'cursor' home
      goto_xy( 0, 0 );    // 'cursor' home    
   }    
   
   /// write a command byte to the LCD
   //
   /// Use this function only for features that are not 
   /// provided by the console interface, like the definition
   /// of the user-defined characters.
   void command( unsigned char cmd ){
      write8( 0, cmd );
   }

   /// write a data byte to the LCD
   //
   /// Use this function only for features that are not 
   /// provided by the console interface, like the definition
   /// of the user-defined characters.
   void data( unsigned char chr ){
      write8( 1, chr );
   }

   void clear() override {
      command( 0x01 );
      wait_ms( 5 );
      goto_xy( 0, 0 );
   }   
   
private:

   void goto_xy_implementation( int new_x, int new_y ) override {
      // the NVI goto_xy() has already set the x and y variables
      
      if( columns == 1 ){
         if( x < 8 ){
            command( 0x80 + x );
         } else {
            command( 0x80 + 0x40 + ( x - 8 ));
         }
      } else {
         if( lines == 2 ){
            command( 
               0x80
               + (( y > 0 ) 
                  ? 0x40 
                  : 0x00 )
               + ( x )
            );
         } else {
            command( 
                0x80
                 + (( y & 0x01 )
                    ? 0x40 
                    : 0x00 )
                 + (( y & 0x02 )
                    ? 0x14 
                    : 0x00 )
                 + ( x )
             );            
         }
      }
   }   
   
   void putc_implementation( char chr ) override {
      // the NVI putc() handles the x and y variables
      
      // handle the gap for 1-line displays
      if( columns == 1 ){
         if( x == 8 ){
            goto_xy( 8, y );
         }
      }
      
      data( chr );
   }  
   
}; // class hd44780
   
}; // namespace hwlib

#endif // HWLIB_HD44780_H