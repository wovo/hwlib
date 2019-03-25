// ==========================================================================
//
// File      : hwlib-hc595.hpp
// Part of   : C++ hwlib library for close-to-the-hardware OO programming
// Copyright : wouter@voti.nl 2016-2019
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
   
/// hc595 8-bit output shift register 
/// 
/// This class implements an interface to 
/// an hc595 8-bit output shift register chip.  
///
/// \image html hc595-pinout.png
///
/// The hc595 is an 8-bit serial-in parallel-out shift register, 
/// connected to an 8-bit data storage register.
/// The 8 outputs of the data register are available on chip pins.
/// The power supply range is 2.0 .. 6.0 Volt.
///
/// \image html hc595-diagram.png
///
/// The HC595 can be used as SPI output-only peripheral:
///    - connect MR (active-low reset input) to the power
///    - connect OE (active-low output enable) to gound
///    - use DS as MOSI
///    - use SHCP as SLCK
///    - use STCP as SS
///
/// Note that STCP is not a real chip-select: the chip will always
/// respond to the data that is clocked by storing it in the shift register.
/// But only the chip that got the select signal will (on the rising edge
/// of the SS) transfer the data from the shift register to the storage 
/// register, hence affecting the outputs.
///
/// The next code shows a kitt display 
/// on 8 LEDs connected to the HC595 output pins:
/// \snippet "db103\hc595\main.cpp" [Doxygen hc595 example]
///
/// The 74HCT595 is a similar chip, but intended (only) for 5V power,
/// and for use with the old TTL signal levels 
/// (HC chips are for the CMOS signal levels that are more common now).
///
/// references:
///    - <A HREF="https://www.nxp.com/documents/data_sheet/74HC_HCT595.pdf">
///       74HC595/74HCT595 data sheet</A> (nxp, pdf)
/// 
class hc595 : public port_out {
private:
   spi_bus & bus;
   pin_out & sel;
   uint8_t write_buffer;
     
   // one_pin is an implementation detail
   class one_pin : public pin_out {
      hc595 & chip;
      uint_fast8_t mask;
      
   public:
      one_pin( hc595 & chip, uint_fast8_t n ): 
         chip( chip ), 
         mask{ static_cast< uint_fast8_t >( 0x01 << n ) }
      {}
      
      void write( bool v ) override {
         if( v ){
            chip.write_buffer |= mask;
         } else {
            chip.write_buffer &= ~ mask;
         }      
      }   
	  
      void flush() override {
         chip.flush();
      }	  
      
   };  
   
public:

   /// construct an interface to an hc595 chip
   ///
   /// This constructor creates an interface to 
   /// an hc595 8-bit output shift register chip
   /// from the SPI bus it is connected to and 
   /// and the active-low chip select line.
   hc595( spi_bus & bus, pin_out & sel ):
      bus( bus ), sel( sel ) {}    

   uint_fast8_t number_of_pins() override {
      return 8;
   }   
      
   void write( uint_fast16_t x ) override {
      write_buffer = x; 
   }  

   void flush() override {
      bus.transaction( sel ).write( write_buffer ); 
   }
   
   /// the output pins of the chip
   ///
   /// The p0 ... p7 attributes represent the 8 
   /// output pins of the chip. 
   /// A write to one of these pins will affect (only) 
   /// the corresponding output pin of the chip.
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
      
}; // class hc595
   
}; // namespace hwlib
