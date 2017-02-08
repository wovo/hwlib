// ==========================================================================
//
// kitt on 8 LEDs on PCF8574A connected to a DB013 board
//
// This file is in the public domain.
//
// ==========================================================================

//! [[Doxygen pcf8574a example]]
#include "hwlib.hpp"

int main( void ){	

   auto scl = hwlib::target::pin_oc{ 0, 4 };
   auto sda = hwlib::target::pin_oc{ 0, 5 };
   
   auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda{ scl,sda };
   
   auto chip = hwlib::pcf8574a{ i2c_bus, 0 };
   
   auto leds = hwlib::port_oc_invert( chip );
 
   hwlib::kitt( leds, 50 );
}  
//! [[Doxygen pcf8574a example]]