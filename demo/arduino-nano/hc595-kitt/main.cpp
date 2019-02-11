// ==========================================================================
//
// blink the LED on an Arduino Uno
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
    
   auto ds   = hwlib::target::pin_out( hwlib::target::pins::a2 );
   auto oe   = hwlib::target::pin_out( hwlib::target::pins::a3 );
   auto stcp = hwlib::target::pin_out( hwlib::target::pins::a4 );
   auto shcp = hwlib::target::pin_out( hwlib::target::pins::a5 );
   
   oe.set( 0 );
   auto spi  = hwlib::spi_bus_bit_banged_sclk_mosi_miso( 
      shcp, 
      ds, 
      hwlib::pin_in_dummy 
   );
   auto hc595 = hwlib::hc595( spi, stcp );
   
   auto leds = hwlib::port_out_from_pins(  
      hc595.p1, 
      hc595.p2, 
      hc595.p3, 
      hc595.p4, 
      hc595.p5, 
      hc595.p6,
      hc595.p7
   );
   
   hwlib::kitt( leds );
}

