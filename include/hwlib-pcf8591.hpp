// ==========================================================================
//
// File      : hwlib-pcf8591.hpp
// Part of   : C++ hwlib library for close-to-the-hardware OO programming
// Copyright : wouter@voti.nl 2017
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

// this file contains Doxygen lines
/// @file

#ifndef HWLIB_PCF8591_H
#define HWLIB_PCF8591_H

#include "hwlib-pin.hpp"
#include "hwlib-port.hpp"
#include "hwlib-wait.hpp"
#include "hwlib-i2c.hpp"
#include "hwlib-adc.hpp"
#include "hwlib-dac.hpp"

namespace hwlib {
   
/// \brief
/// pcf8591 I2C A/D and D/A converter 
/// \details
/// This class implements an interface to a pcf8591 A/D & D/A converter chip.
///
/// \image html pcf8591-pinout.png
///
/// A pcf8591 is an I2C slave that provides 4 8-bits A/D inputs (that can 
/// be arranged in various combinations of single and balaced inputs),
/// and a single8-bits D/A output. 
/// The power supply range is 2.5 .. 5.5 Volt.
/// Of the 7-bit slave address, 
/// 3 bits are set by the level of 3 input pins (A0..A2) of the chip.
///
/// The next code repeatedly prints the values read
/// by the 4 (single-ended) A/D converters.
///
/// \snippet "demo\db103\pcf8591-adc\main.cpp" [Doxygen pcf8591-adc example]
///
/// references:
///    - <A HREF="http://www.nxp.com/documents/data_sheet/PCF8591.pdf">
///       PCF8591 data sheet</A> (pdf)
/// 
class pcf8591 {
private:
   i2c_bus & bus;
   uint_fast8_t address;
   
   static constexpr uint_fast8_t base = 0x48;
   
   uint_fast8_t configuration;
   
   uint_fast8_t get( uint_fast8_t channel ){
      // select the correct channel
      uint8_t control = ( configuration & ( ~ 0x03 )) + channel; 
      bus.write( base + address, & control, 1 ); 
      
      // read results, note that the first byte is the 
      // *previous* ADC result, the second byte is what we want
      uint8_t results[ 2 ];
      bus.read( base + address, results, 2 );
      return results[ 1 ];
   }   
   
   class _one_adc : public adc {
      pcf8591 & chip;
      uint_fast8_t channel;
      
   public:
      _one_adc( pcf8591 & chip, uint_fast8_t channel ): 
         adc{ 8 },
         chip( chip ), 
         channel{ channel }
      {}
      
      adc_value_type get() override {
         return chip.get( channel );
      }   
   };
   
   class _one_dac : public dac {
      pcf8591 & chip;
      
   public:
      _one_dac( pcf8591 & chip ): 
         dac{ 8 },
         chip( chip ) 
      {}
      
      void set( dac_value_type x ) override {
         uint8_t message[ 2 ] = { 
            static_cast< uint8_t >( chip.configuration ), 
            static_cast< uint8_t >( x )
         };
         chip.bus.write( 
            chip.base + chip.address, 
            message, 
            sizeof( message ) / sizeof( uint8_t ) 
         ); 
      }   
   };
   
   // hide the private classes from Doxygen
   #ifdef DOXYGEN
      typedef adc one_adc;
      typedef dac one_adc;
   #else
      typedef _one_adc one_adc;
      typedef _one_dac one_dac;
   #endif   

public:

   /// \brief
   /// construct an interface to a pcf8591 chip
   /// \details
   /// This constructor creates an interface to a pcf8591 I2C
   /// A/D and D/A converter from the I2C bus it is connected to and 
   /// and the chip address.
   /// The address is the 3-bit address that is determined by the 3 
   /// address input pins of the chip.
   pcf8591( i2c_bus & bus, uint_fast8_t address ):
      bus( bus ), 
      address{ address }, 
      configuration{ 0x40 }
   {}         

   /// \brief
   /// the A/D converter channels of the chip
   /// \details
   /// The adc0 ... adc3 attributes represent the 4 A/D 
   /// inputs of the chip. 
   //@{ 
   one_adc adc0{ *this, 0 };   
   one_adc adc1{ *this, 1 };   
   one_adc adc2{ *this, 2 };   
   one_adc adc3{ *this, 3 };   
   //@}
      
   /// the D/A converter channel of the chip
   one_dac dac0{ *this };   

}; // class pcf8591
   
}; // namespace hwlib

#endif // HWLIB_PCF8591_H