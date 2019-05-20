// ==========================================================================
//
// File      : hwlib-arduino-uno.hpp
// Part of   : C++ hwlib library for close-to-the-hardware OO programming
// Copyright : wouter@voti.nl 2017-2019
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

// this file contains Doxygen lines
/// @file

#ifndef HWLIB_UNO_H
#define HWLIB_UNO_H

#include "hwlib-atmega328.hpp"

namespace uno {

/// Arduino Uno pin names
///
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
   { 2,  2 },  // a2
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

using pin_adc = atmega328::pin_adc;

class pin_in : public atmega328::pin_in {
public:
   /// pin_in constructor from ATMega328P port/pin numbers
   ///
   /// This call creates a pin_in from an ATMega328P port/pin
   /// number pair.
   ///
   /// This constructor sets the pin direction to input.
   pin_in( uint8_t port_number, uint8_t pin_number ): 
      atmega328::pin_in( port_number, pin_number )
   {}      
   
   /// Arduino Uno pin_in constructor from an Uno pin name
   ///
   /// This call creates a pin_in from an Arduino Uno pin name.
   ///
   /// This constructor sets the pin direction to input.
   pin_in( pins name ): 
      pin_in{ 
         pin_info( name ).port, 
         pin_info( name ).pin 
      }
   {}   
};

class pin_out : public atmega328::pin_out {
public:

   /// pin_out constructor from ATMega328P port/pin numbers
   ///
   /// This call creates a pin_out from an ATMega328P port/pin
   /// number pair.
   ///
   /// This constructor sets the pin direction to output.
   pin_out( uint8_t port_number, uint8_t pin_number ): 
      atmega328::pin_out( port_number, pin_number )
   {}      
   
   /// Arduino Uno pin_out constructor from an Uno pin name
   ///
   /// This call creates a pin_out from an Arduino Uno pin name.
   ///
   /// This constructor sets the pin direction to output.
   pin_out( pins name ): 
      pin_out{ 
         pin_info( name ).port, 
         pin_info( name ).pin 
      }
   {}   
};

class pin_in_out : public atmega328::pin_in_out { 
public:

   /// ATmega pin_in_out constructor
   ///
   /// Constructor for a ATMega328P input/output pin.
   ///
   /// The port_number and pin_number refer to the chip, 
   /// not to the Arduino board pin names.
   ///
   /// This constructor doesn't set the pin direction 
   /// to input or output, a direction_set function must
   /// be called to do so.
   pin_in_out( uint8_t port_number, uint8_t pin_number ): 
      atmega328::pin_in_out( port_number, pin_number )
   {}      
   
   /// Arduino Uno pin_in_out constructor from an Uno pin name
   ///
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
};   

class pin_oc : public atmega328::pin_oc {   
public:

   /// Arduino Uno pin_oc constructor
   ///
   /// Constructor for a ATMega328P input pin.
   ///
   /// The port_number and pin_number refer to the chip, 
   /// not to the Arduino board pin names.
   ///
   /// This constructor sets the pin to high (high-impedance). 
   pin_oc( uint8_t port_number, uint8_t pin_number ): 
      atmega328::pin_oc( port_number, pin_number )
   {}      
   
   /// Arduino Uno pin_oc constructor from an Uno pin name
   ///
   /// This call creates a pin_oc from an Arduino Uno pin name.
   ///
   /// This constructor sets the pin to high (high-impedance). 
   pin_oc( pins name ): 
      pin_oc{ 
         pin_info( name ).port, 
         pin_info( name ).pin 
      }
   {}    
};

}; // namespace uno

namespace hwlib {

namespace target = ::uno;
const auto target_board = target_boards::arduino_uno;
   
}; //namespace hwlib   

#endif // HWLIB_UNO_H    
