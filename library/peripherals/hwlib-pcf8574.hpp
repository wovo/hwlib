// ==========================================================================
//
// File      : hwlib-pcf8574.hpp
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
   
/// pcf8574 / pcf8574a I2C I/O extender 
///
/// This class implements an interface to a pcf8574 and pcf8574a 
/// I2C I/O extender chip.
///
/// \image html pcf8574a-pinout.png
///
/// A pcf8574(a) is an I2C slave that provides 8 open-collector input/output
/// pins with weak pull-ups. 
/// The power supply range is 2.5 .. 5.5 Volt.
/// Of the 7-bit slave address, 
/// 3 bits are set by the level of 3 input pins (A0..A2) of the chip.
/// With all pulled low the iw2c address is 0x38.
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
/// \snippet "db103\pcf8574a-blink\main.cpp" [Doxygen pcf8574a example]
///
/// The pcf8574 and pcf8574a are the same chips, but with a different
/// I2C bus address.
///
/// \image html pcf8574a-addresses.png
///
/// references:
///    - <A HREF="http://www.nxp.com/documents/data_sheet/PCF8574_PCF8574A.pdf">
///       PCF8574A data sheet</A> (pdf)
/// 
class pcf8574 : public port_oc {
   private:

   i2c_bus & bus;
   uint8_t address;
   uint8_t write_buffer;
   uint8_t read_buffer;
   bool dirty;
   
   // one_pin is an implementation detail
   class one_pin : public pin_oc {
      pcf8574 & chip;
      uint_fast8_t mask;
      
   public:

      one_pin( pcf8574 & chip, uint_fast8_t n ): 
         chip( chip ), 
         mask{ static_cast< uint_fast8_t >( 0x01 << n ) }
      {}
      
      void write( bool v ) override {
         if( v ){
            chip.write_buffer |= mask;
         } else {
            chip.write_buffer &= ~ mask;
         }    
         chip.dirty = true;  
      }   
      
      bool read() override {
         return ( chip.read_buffer & mask ) != 0;
      }
	  
	  void flush() override {
         chip.flush();		  
      }
      
	  void refresh() override {
         chip.refresh();		  
      }
      
   };
   
public:

   /// construct an interface to a pcf8574 chip
   ///
   /// This constructor creates an interface to a pcf8574 I2C
   /// I/O extender chip from an I2C bus channel.
   pcf8574( i2c_bus & bus, uint_fast8_t address = 0x28 ):
      bus( bus), address( address ), dirty( false ) {}    

   uint_fast8_t number_of_pins() override {
      return 8;
   }   
      
   void write( uint_fast16_t x ) override {
      write_buffer = x; 
      dirty = true;
   }  
   
   uint_fast16_t read() override {
      return read_buffer;  
   }  

   void flush() override {
      if( dirty ){
         bus.write( address ).write( write_buffer ); 
         dirty = false;
      }
   }
   
   void refresh() override {
      bus.read( address ).read( read_buffer ); 
   }

   /// the open-collector pins of the chip
   ///
   /// The p0 ... p7 attributes represent the 8 open-collector 
   /// output pins of the chip. 
   /// A write to one of these pins will affect (only) 
   /// the corresponding output pin of the chip.
   /// A read of one of these pins will reflect the status
   /// of the corresponding pin of the chip.
   ///@{ 
   one_pin p0{ *this, 0 };   
   one_pin p1{ *this, 1 };   
   one_pin p2{ *this, 2 };   
   one_pin p3{ *this, 3 };   
   one_pin p4{ *this, 4 };   
   one_pin p5{ *this, 5 };   
   one_pin p6{ *this, 6 };   
   one_pin p7{ *this, 7 };   
   ///@}
      
}; // class pcf8574

/// pcf8574a is thge same chip, but with a different i2c address
using pcf8574a = pcf8574;
   
}; // namespace hwlib
