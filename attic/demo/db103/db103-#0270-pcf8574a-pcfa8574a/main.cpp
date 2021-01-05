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
   
   auto i2c_bus_1  = hwlib::i2c_bus_bit_banged_scl_sda{ scl,sda };
   auto chip_1     = hwlib::pcf8574a{ i2c_bus_1, 0x38 };
   
   auto i2c_bus_2  = hwlib::i2c_bus_bit_banged_scl_sda{ chip_1.p6, chip_1.p7 };
   auto chip_2     = hwlib::pcf8574a{ i2c_bus_2, 0x38 };
   
   hwlib::blink( chip_2.p4, 100 );
}  
//! [[Doxygen pcf8574a example]]