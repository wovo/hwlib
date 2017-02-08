// ==========================================================================
//
// kitt on 8 LEDs on a HC595 connected to a DB103 board
//
// This file is in the public domain.
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
 
   hwlib::kitt( chip, 50 );
}  
//! [[Doxygen hc595 example]]
