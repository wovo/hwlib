// ==========================================================================
//
// kitt on 8 LEDs on PCF8574A connected to a DB103 (LPC1114)
//
// (c) Wouter van Ooijen (wouter@voti.nl) 2017
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt) 
//
// ==========================================================================

//! [[Doxygen pcf8591-adc example]]
#include "hwlib.hpp"

int main( void ){
 
   auto scl          = hwlib::target::pin_oc{ 0, 4 };
   auto sda          = hwlib::target::pin_oc{ 0, 5 };
   
   auto i2c_bus      = hwlib::i2c_bus_bit_banged_scl_sda{ scl,sda };
   auto chip         = hwlib::pcf8591( i2c_bus, 0x48 );
   
   for(;;){
      hwlib::cout 
         << "adc0: " << hwlib::setw( 4 ) << chip.adc0.read() << "   "
         << "adc1: " << hwlib::setw( 4 ) << chip.adc1.read() << "   " 
         << "adc2: " << hwlib::setw( 4 ) << chip.adc2.read() << "   "
         << "adc3: " << hwlib::setw( 4 ) << chip.adc3.read() << "\n";
      hwlib::wait_ms( 250 );
   }
}  
//! [[Doxygen pcf8591-adc example]]