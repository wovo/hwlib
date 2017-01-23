// ==========================================================================
//
// File      : hwlib-uno.hpp
// Part of   : hwlib library for V1OOPC and V1IPAS
// Copyright : wouter@voti.nl 2016
//
// hwlib implementation for an Arduino Uno (ATMega328P chip)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================
/// @file

#ifndef HWLIB_UNO_H
#define HWLIB_UNO_H

#include "hwlib-all.hpp"
#include "io.h"
#include <stdint.h>

/// hwlib implementation for the Arduino Uno
//
/// \image html uno-pcb.jpg
//
/// This namespace contains the hwlib implementation of the pins, timing
/// and (sotware) UART output for the Arduino Uno (ATMega328P chip).
///
/// The port and pin parameters to the constructors of the pin classes
/// can either use ATMega328P port and pin numbers, or the Arduino names.
///
/// The Uno has an on-board LED connected to port 1 (= port B) pin 5.
///
/// The chip runs at 5 Volt and that is the level on its IO pins.
///
/// \image html uno-pinout.png
///
/// The Arduino Nano and Arduino Pro Mini that use the same ATMega328P chip
/// can also be used with this library, 
/// but have a very different form factor and pinout.
///
/// The Nano has an USB connector and an USB-to-serial connector and
/// can run the Arduino bootloader, but is often sold without the bootloader.
/// An AVRisp2 programmer can be used to program a Nano directly, or you
/// can use it to load the Arduino bootloader and use the Nano as you
/// would use an Uno.
///
/// \image html nano-pinout.jpg
///
/// The Pro Mini is little more than the micro-controler chip and a few
/// necessary components (crystal, capacitors). 
/// It has neither an USB-to-serial converter nor a standard
/// 6-pin AVRisp2 header, so you must make the correct connections yourself.
///
/// \image html mini-pro-pinout.png
///
/// AVR microcontrollers use a Hardvard-architecture with a strict
/// separation between data memory (RAM and special registers) 
/// and code memory (Flash). 
/// Consequently all data, including constant data, must be stored in RAM.
/// Other architectures can store constant data in ROM, 
/// which is often much larger than RAM.
/// 
///
/// References:
///    - <A HREF="https://www.arduino.cc/en/uploads/Main/arduino-uno-schematic.pdf">
///       Arduino Uno circuit reference diagram</A> (pdf)
///    - <A HREF="http://www.atmel.com/images/atmel-8271-8-bit-avr-microcontroller-atmega48a-48pa-88a-88pa-168a-168pa-328-328p_datasheet_complete.pdf">
///       ATMega328P datasheet</A> (pdf)
///
namespace uno {

/// Arduino Uno pin names
//
/// These are the pins of an Arduino Uno board.
/// Digital pins d0..d13, analog input pins A0..A5, 
/// SCL, SDA, TX (=D1), RX (=D0), 
/// LED (=D13), SCK (=D13), MISO (=D12), MOSI (=D11), SS (=D10).
enum class pins {
   d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13,
   a0, a1, a2, a3, a4, a5,
   scl, sda, tx, rx, led, 
   sck, miso, mosi, ss
/// \cond INTERNAL    
   ,SIZE_THIS_IS_NOT_A_PIN
/// \endcond   
};
   
/// \cond INTERNAL 

struct pin_info_type { 
   uint8_t port; 
   uint8_t pin; 
};

const pin_info_type pin_info_array[ (int) pins::SIZE_THIS_IS_NOT_A_PIN ] = {
   { 3,  0 },  // d0
   { 3,  1 },  // d1
   { 3,  2 },  // d2
   { 3,  3 },  // d3
   { 3,  4 },  // d4
   { 3,  5 },  // d5
   { 3,  6 },  // d6
   { 3,  7 },  // d7
   { 1,  0 },  // d8
   { 1,  1 },  // d9
   { 1,  2 },  // d10
   { 1,  3 },  // d11
   { 1,  4 },  // d12
   { 1,  5 },  // d13
   
   { 2,  0 },  // a0
   { 2,  1 },  // a1
   { 2,  2 },  // a1
   { 2,  3 },  // a3
   { 2,  4 },  // a4
   { 2,  5 },  // a5
   
   { 2,  5 },  // scl
   { 2,  4 },  // sda
   { 3,  0 },  // tx
   { 3,  1 },  // rx
   { 1,  5 },  // led
   
   { 1,  5 },  // sck
   { 1,  4 },  // miso
   { 1,  3 },  // mosi
   { 1,  2 },  // ss
};

const pin_info_type & HWLIB_WEAK pin_info( pins name ){
   uint_fast8_t n = static_cast< uint_fast8_t>( name );
   if( n >= static_cast< uint_fast8_t>( pins::SIZE_THIS_IS_NOT_A_PIN )){
      HWLIB_PANIC_WITH_LOCATION;
   }
   return pin_info_array[ n ];
}

volatile uint8_t & HWLIB_WEAK port_data( uint_fast8_t port ){
   switch( port ){
      // case 0  : return PORTA;
      case 1  : return PORTB;
      case 2  : return PORTC;
      case 3  : return PORTD;
      default : break;
   }   
   HWLIB_PANIC_WITH_LOCATION; 
   // doesn't return
}

volatile uint8_t & HWLIB_WEAK port_direction( uint_fast8_t port ){
   switch( port ){
      // case 0  : return DDRA;
      case 1  : return DDRB;
      case 2  : return DDRC;
      case 3  : return DDRD;
      default : break;
   }   
   HWLIB_PANIC_WITH_LOCATION; 
   // doesn't return
}

void HWLIB_WEAK configure_as_gpio( uint_fast8_t port, uint_fast8_t pin ){
   if( port == 3 ){
      if( pin == 0 ) {
         UCSR0B &= ~ 0x10; // disable UART receive
      }
      if( pin == 1 ){
         UCSR0B &= ~ 0x08; // disable UART transmit
      }
   }
}

/// \endcond
   
/// pin_in implementation for a ATMega328P
class pin_in : public hwlib::pin_in {
private:
   volatile uint8_t & port;
   uint8_t mask;
 
public:

   /// Arduino Uno pin_in constructor from ATMega328P port/pin numbers
   //
   /// This call creates a pin_in from an ATMega328P port/pin
   /// number pair.
   ///
   /// This constructor sets the pin direction to input.
   pin_in( uint8_t port_number, uint8_t pin_number ): 
      port{ port_data( port_number ) }, 
      mask( 0x1 << pin_number )
   {
      configure_as_gpio( port_number, pin_number );
      port_direction( port_number ) &= ~mask;
   }
   
   /// Arduino Uno pin_in constructor from an Uno pin name
   //
   /// This call creates a pin_in from an Arduino Uno pin name.
   ///
   /// This constructor sets the pin direction to input.
   pin_in( pins name ): 
      pin_in{ 
         pin_info( name ).port, 
         pin_info( name ).pin 
      }
   {}
   
   bool get() override {
      return ( port & mask ) != 0;   
   }
};

/// pin_out implementation for a ATMega328P
class pin_out : public hwlib::pin_out {
private:
   volatile uint8_t & port;
   uint8_t mask;
   
public:

   /// Arduino Uno pin_out constructor from ATMega328P port/pin numbers
   //
   /// This call creates a pin_out from an ATMega328P port/pin
   /// number pair.
   ///
   /// This constructor sets the pin direction to output.
   pin_out( uint8_t port_number, uint8_t pin_number ): 
      port{ port_data( port_number ) }, 
      mask( 0x1 << pin_number )
   {
      configure_as_gpio( port_number, pin_number );
      port_direction( port_number ) |= mask;
   }
   
   /// Arduino Uno pin_out constructor from an Uno pin name
   //
   /// This call creates a pin_out from an Arduino Uno pin name.
   ///
   /// This constructor sets the pin direction to output.
   pin_out( pins name ): 
      pin_out{ 
         pin_info( name ).port, 
         pin_info( name ).pin 
      }
   {}   
   
   void set( bool v ) override {
      if( v ){
         port |= mask;
      } else {
         port &= ~mask;
      }
   }
};

/// pin_in_out implementation for a ATMega328P
class pin_in_out : public hwlib::pin_in_out {
private:
   volatile uint8_t & port;
   uint8_t port_number;
   uint8_t mask;
   
public:

   /// Arduino Uno pin_in_out constructor
   //
   /// Constructor for a ATMega328P input/output pin.
   ///
   /// The port_number and pin_number refer to the chip, 
   /// not to the Arduino board pin names.
   ///
   /// This constructor doesn't set the pin direction 
   /// to input or output, a direction_set function must
   /// be called to do so.
   pin_in_out( uint8_t port_number, uint8_t pin_number ): 
      port{ port_data( port_number ) }, 
      port_number( port_number ),
      mask( 0x1 << pin_number )
   {
      configure_as_gpio( port_number, pin_number );
   }
   
   /// Arduino Uno pin_in_out constructor from an Uno pin name
   //
   /// This call creates a pin_in_out from an Arduino Uno pin name.
   ///
   /// This constructor doesn't set the pin direction 
   /// to input or output, a direction_set function must
   /// be called to do so.
   pin_in_out( pins name ): 
      pin_in_out{ 
         pin_info( name ).port, 
         pin_info( name ).pin 
      }
   {}   
   
   virtual void direction_set_input() override {
      port_direction( port_number ) &= ~ mask;
   }
   
   bool get() override {
      return ( port & mask ) != 0;   
   }
   
   virtual void direction_set_output() override {
      port_direction( port_number ) |= mask;   
   }
   
   void set( bool v ) override {
      if( v ){
         port |= mask;
      } else {
         port &= ~mask;
      }
   }
};   

/// pin_oc implementation for a ATMega328P
class pin_oc : public hwlib::pin_oc {
private:
   volatile uint8_t & port;
   uint8_t port_number;
   uint8_t mask;
   
public:

   /// Arduino Uno pin_oc constructor
   //
   /// Constructor for a ATMega328P input pin.
   ///
   /// The port_number and pin_number refer to the chip, 
   /// not to the Arduino board pin names.
   ///
   /// This constructor sets the pin to high (high-impedance). 
   pin_oc( uint8_t port_number, uint8_t pin_number ): 
      port{ port_data( port_number ) }, 
      port_number( port_number ),
      mask( 0x1 << pin_number )
   {
      configure_as_gpio( port_number, pin_number );
   }
   
   /// Arduino Uno pin_oc constructor from an Uno pin name
   //
   /// This call creates a pin_oc from an Arduino Uno pin name.
   ///
   /// This constructor sets the pin to high (high-impedance). 
   pin_oc( pins name ): 
      pin_oc{ 
         pin_info( name ).port, 
         pin_info( name ).pin 
      }
   {}    
   
   bool get() override {
      return ( port & mask ) != 0;   
   }   
   
   void set( bool v ) override {
      if( v ){
         port_direction( port_number ) &= ~ mask;
      } else {
         port_direction( port_number ) |= mask;
         port &= ~mask;
      }
   }

};

// should be part of due, anders for Uno!
class shield_lcd_mcufriend {
private:
   pin_out rst, cs, rs, wr, rd;
   pin_in_out d0, d1, d2, d3, d4, d5, d6, d7;
   ::hwlib::port_in_out_from_pins data;
      
public:
   ::hwlib::glcd_mcufriend_2_4 lcd;

   shield_lcd_mcufriend():   
      rst{ pins::a4 },
      cs{  pins::a3 },
      rs{  pins::a2 },
      wr{  pins::a1 },
      rd{  pins::a0 },
      d0{  pins::d8 },
      d1{  pins::d9 },
      d2{  pins::d2 },
      d3{  pins::d3 },
      d4{  pins::d4 },
      d5{  pins::d5 },
      d6{  pins::d6 },
      d7{  pins::d7 },
      data{ d0, d1, d2, d3, d4, d5, d6, d7 },
      lcd{ rst, cs, rs, wr, rd, data }
   {}    
};

}; // namespace due

namespace hwlib {

namespace target = ::uno;
   
void HWLIB_WEAK wait_ns( int_fast32_t n ){
   wait_us( n / 1000 );
}

void HWLIB_WEAK wait_us( int_fast32_t n ){ 
    // first int parameter is passd in r24/r25
    __asm volatile(                  // clocks
       "1:  cp    r1, r24     \t\n"   // 1
       "    cpc   r1, r25     \t\n"   // 1
       "    brge  3f          \t\n"   // 1
       "    rcall 3f          \t\n"   // 7
       "    rjmp  2f          \t\n"  // 2
       "2:  sbiw  r24, 0x01   \t\n"   // 2
       "    rjmp  1b          \t\n"   // 2
       "3:                    \t\n"   // 16 total
   );     
}

void HWLIB_WEAK wait_ms( int_fast32_t n ){
   while( n > 0 ){
      wait_us( 1000 );
      --n;
   }   
}   

void HWLIB_WEAK uart_putc( char c ){
   static target::pin_out pin( 3, 1 );
   uart_putc_bit_banged_pin( c, pin );
}

}; //namespace hwlib   

#endif // HWLIB_UNO_H