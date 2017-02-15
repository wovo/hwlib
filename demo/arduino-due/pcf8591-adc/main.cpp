// ==========================================================================
//
// read and pint PCF8591 A/D inputs
//
// (c) Wouter van Ooijen (wouter@voti.nl) 2017
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt) 
//
// ==========================================================================

#include "hwlib.hpp"

int main( void ){
    
       // kill the watchdog
   WDT->WDT_MR = WDT_MR_WDDIS;
 
   auto scl = hwlib::target::pin_oc{ hwlib::target::pins::scl };
   auto sda = hwlib::target::pin_oc{ hwlib::target::pins::sda };
   auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda{ scl,sda };
   auto chip = hwlib::pcf8591{ i2c_bus, 0 };
   
   for(;;){
      hwlib::cout 
         << "adc0: " << hwlib::setw( 4 ) << chip.adc0.get() << "   "
         << "adc1: " << hwlib::setw( 4 ) << chip.adc1.get() << "   " 
         << "adc2: " << hwlib::setw( 4 ) << chip.adc2.get() << "   "
         << "adc3: " << hwlib::setw( 4 ) << chip.adc3.get() << "\n";
      hwlib::wait_ms( 250 );
   }
}  
