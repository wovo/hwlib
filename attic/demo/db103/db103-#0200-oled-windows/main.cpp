// ==========================================================================
//
// OLED demo on DB103 (LPC1114)
//
// (c) Wouter van Ooijen (wouter@voti.nl) 2019
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt) 
//
// ==========================================================================

#include "hwlib.hpp"

int main( void ){
       
   namespace target = hwlib::target;
   
   auto scl       = hwlib::target::pin_oc{ 0, 4 };
   auto sda       = hwlib::target::pin_oc{ 0, 5 };
   
   auto bus       = hwlib::i2c_bus_bit_banged_scl_sda( scl, sda );
   auto oled      = hwlib::glcd_oled( bus );
   
   auto font1     = hwlib::font_default_8x8();
   auto part1     = hwlib::part( oled, hwlib::xy( 0, 0 ), hwlib::xy( 128, 32 ) );
   auto console1  = hwlib::terminal_from( part1, font1 );
   
   auto font2     = hwlib::font_default_16x16();
   auto part2     = hwlib::part( oled, hwlib::xy( 0, 32 ), hwlib::xy( 128, 32 ) );
   auto console2  = hwlib::terminal_from( part2, font2 );
   
   console1 
      << "\f" << "Hello world!!" 
      << "\n" << "second line.."
      << "\n" << "line 3"
      << "\n" << "line 4"
      << hwlib::flush;    
 
   console2  
      << "\fBIG BIG"
      << "\nFONT"
      << hwlib::flush;     
}
