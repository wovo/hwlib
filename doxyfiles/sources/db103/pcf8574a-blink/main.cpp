// ==========================================================================
//
// kitt on 8 LEDs on PCF8574A connected to a DB013 board (LPC1114)
//
// (c) Wouter van Ooijen (wouter@voti.nl) 2017-2019
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt) 
//
// ==========================================================================

//! [[Doxygen pcf8574a example]]

// kitt display on 8 LEDs connected to a pcf8574a i2c I/O extender

#include "hwlib.hpp"

int main( void ){

   auto scl           = hwlib::target::pin_oc{ 0, 4 };
   auto sda           = hwlib::target::pin_oc{ 0, 5 };
   auto i2c_bus       = hwlib::i2c_bus_bit_banged_scl_sda{ scl,sda };
   auto chip_channel  = i2c_bus.channel( 0x38 );
   auto chip          = hwlib::pcf8574a{ chip_channel };
 
   hwlib::blink( chip.p0, 200 );
}  

//! [[Doxygen pcf8574a example]]