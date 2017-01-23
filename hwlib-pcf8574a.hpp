// ==========================================================================
//
// File      : hwlib-pcf8574.hpp
// Part of   : hwlib library for V1OOPC and V1IPAS
// Copyright : wouter@voti.nl 2016
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================
/// @file

#ifndef HWLIB_PCF8574_H
#define HWLIB_PCF8574_H

#include "hwlib-pin.hpp"
#include "hwlib-port.hpp"
#include "hwlib-wait.hpp"

namespace hwlib {
   
/// pcf8574a I2C I/O extender 
//
/// This class implements an interface to a pcf8574a I2C I/O extender chip.
///
/// \image html pcf8574a-pinout.png
///
/// A pcf8574a is an I2C slave that provides 8 open-collector input/output
/// pins with weak pull-ups. 
/// The power supply range is 2.5 .. 5.5 Volt.
/// Of the 7-bit slave address, 
/// 3 bits are set by the level of 3 input pins (A0..A2) of the chip.
///
/// \image html pcf8574a-iopin.png
///
/// The chip has only one register, which can be read and written. 
/// When written, it determines the level of the 8 output pins:
/// low when the bit is 0, pulled weakly high when the bit is 1.
/// When read, the level of the 8 pins determines the value:
/// 0 for a low pin, 1 for a high pin.
///
/// \image html pcf8574a-diagram.png
///
/// The next code shows a kitt display 
/// on 8 LEDs connected to the PCF8574A output pins.
/// Because the output pins are open-collector, the LEDs
/// are connected to power (instead of to the ground), hence
/// the use of hwlib::port_out_invert().
/// \snippet "due\pcf8574a\main.cpp" [Doxygen pcf8574a example]
///
/// The pcf8574 (without the -a) is the same chip, but with a different
/// I2C bus address.
///
/// \image html pcf8574a-addresses.png
///
/// references:
///    - <A HREF="http://www.nxp.com/documents/data_sheet/PCF8574_PCF8574A.pdf">
///       PCF8574A data sheet</A> (pdf)
/// 
class pcf8574a : public port_oc {
private:
   i2c_bus & bus;
   fast_byte address;
   
   static constexpr int base = 0x38;
   
   byte write_buffer;
   byte read_buffer;
   
   void flush(){
      bus.write( base + address, &write_buffer, 1 ); 
   }
   
   void refresh(){
      bus.read( base + address, &read_buffer, 1 ); 
   }
   
   class _one_pin : public pin_oc {
      pcf8574a & chip;
      uint_fast8_t mask;
      
   public:
      _one_pin( pcf8574a & chip, int n ): 
         chip( chip ), 
         mask{ static_cast< fast_byte >( 0x01 << n ) }
      {}
      
      void set( bool v ) override {
         if( v ){
            chip.write_buffer |= mask;
         } else {
            chip.write_buffer &= ~ mask;
         }      
         chip.flush();
      }   
      
      bool get() override {
         chip.refresh();
         return ( chip.read_buffer & mask ) != 0;
      }
   };
   
public:

   /// construct an interface to a pcf8574a chip
   //
   /// This constructor creates an interface to a pcf8574a I2C
   /// I/O extender chip from the I2C bus it is connected to and 
   /// and the chip address.
   /// The address is the 3-bit address that is determined by the 3 
   /// address input pins of the chip.
   pcf8574a( i2c_bus & bus, fast_byte address ):
      bus( bus ), address{ address } {}    

   uint_fast8_t number_of_pins() override {
      return 8;
   }   
      
   void set( uint_fast8_t x ) override {
      write_buffer = x;
      flush();     
   }  
   
   uint_fast8_t get() override {
      refresh(); 
      return read_buffer;  
   }  
   
   // hide _one_pin for Doxygen
   #ifdef DOXYGEN
      typedef pin_out one_pin;
   #else
      typedef _one_pin one_pin;
   #endif   

   /// the open-collector pins of the chip
   //
   /// The p0 ... p7 attributes represent the 8 open-collector 
   /// output pins of the chip. 
   /// A write to one of these pins will affect (only) 
   /// the corresponding output pin of the chip.
   /// A read of one of these pins will reflect the status
   /// of the corresponding pin of the chip.
   //@{ 
   one_pin p0{ *this, 0 };   
   one_pin p1{ *this, 1 };   
   one_pin p2{ *this, 2 };   
   one_pin p3{ *this, 3 };   
   one_pin p4{ *this, 4 };   
   one_pin p5{ *this, 5 };   
   one_pin p6{ *this, 6 };   
   one_pin p7{ *this, 7 };   
   //@}
      
}; // class pcf8574a
   
}; // namespace hwlib

#endif // HWLIB_PCF8574_H