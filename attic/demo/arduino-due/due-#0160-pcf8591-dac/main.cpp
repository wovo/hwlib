// ==========================================================================
//
// show triangle waveform on dac output
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
 
   auto scl      = hwlib::target::pin_oc{ hwlib::target::pins::scl };
   auto sda      = hwlib::target::pin_oc{ hwlib::target::pins::sda };
   
   auto i2c_bus  = hwlib::i2c_bus_bit_banged_scl_sda{ scl,sda };
   auto chip     = hwlib::pcf8591{ i2c_bus };
   
   hwlib::dac_triangle( chip.dac0 );
   
}  
