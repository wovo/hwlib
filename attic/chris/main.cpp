// ==========================================================================
//
// Hello world on DB103 (LPC1114)
//
// (c) Wouter van Ooijen (wouter@voti.nl) 2017
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt) 
//
// ==========================================================================

#include "hwlib.hpp"
//
#include "due-spi.hpp"
#include "glcd-oled-spi.hpp"

int main( void ){
    
   // kill the watchdog
   WDT->WDT_MR = WDT_MR_WDDIS;
   
   // wait for the terminal to start on the PC side
   hwlib::wait_ms( 500 );
   
      namespace target = hwlib::target;
   
      auto mosi  = target::pin_out(target::pins::d9);
      auto sclk  = target::pin_out(target::pins::d10);
      auto dc    = target::pin_out(target::pins::d11);
      auto cs    = target::pin_out(target::pins::d12);
      auto reset = target::pin_out(target::pins::d13);
 
      auto spi = hwlib::spi_bus_bit_banged_sclk_mosi_miso( sclk, mosi, hwlib::pin_in_dummy );   
   
   auto oled    = hwlib::glcd_oled_spi( spi, cs, dc, reset );
HWLIB_TRACE;   
   oled.clear();
HWLIB_TRACE;  
   
   auto font    = hwlib::font_default_8x8();
   auto display = hwlib::window_ostream( oled, font );
HWLIB_TRACE;     

   display 
      << "\f" << "Hello world" 
      << "\n" << "second line"
      << "\t0305" << "pos 3 line 5"
      << hwlib::flush;   
}
