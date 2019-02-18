// ==========================================================================
//
// blink on 1 LEDs on a HC595 connected to a DB103 
//
// (c) Wouter van Ooijen (wouter@voti.nl) 2017
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt) 
//
// ==========================================================================

//! [[Doxygen hc595 example]]
#include "hwlib.hpp"

int main( void ){

   auto sclk = hwlib::target::pin_out{ 1, 2 };
   auto mosi = hwlib::target::pin_out{ 1, 0 };
   auto cs   = hwlib::target::pin_out{ 1, 1 };
   
   auto spi_bus = hwlib::spi_bus_bit_banged_sclk_mosi_miso{ 
      sclk, mosi, hwlib::pin_in_dummy };
   
   auto chip = hwlib::hc595{ spi_bus, cs };
 
   hwlib::blink( chip.p0 );
}  
//! [[Doxygen hc595 example]]
