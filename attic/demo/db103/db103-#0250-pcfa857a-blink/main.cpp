// ==========================================================================
//
// kitt on 8 LEDs on PCF8574A connected to a DB013 board (LPC1114)
//
// (c) Wouter van Ooijen (wouter@voti.nl) 2017
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt) 
//
// ==========================================================================

//! [[Doxygen pcf8574a example]]

#include "hwlib.hpp"

int main( void ){

   auto scl        = hwlib::target::pin_oc{ 0, 4 };
   auto sda        = hwlib::target::pin_oc{ 0, 5 };
      
   auto bus        = hwlib::i2c_bus_bit_banged_scl_sda{ scl,sda };
   auto chip       = hwlib::pcf8574a{ bus, 0x38 };
 
   hwlib::blink( chip.p0, 200 );
}  

//! [[Doxygen pcf8574a example]]