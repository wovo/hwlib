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
   auto oled      = hwlib::glcd_oled_i2c_128x64_fast_buffered( bus );
   
   auto font1     = hwlib::font_default_8x8();
   auto part1     = hwlib::part( oled, hwlib::xy( 0, 0 ), hwlib::xy( 128, 16 ) );
   auto console1  = hwlib::terminal_from( part1, font1 );
   
   auto part2     = hwlib::part( oled, hwlib::xy( 10, 16 ), hwlib::xy( 108, 32 ) );
   
   auto font3     = hwlib::font_default_16x16();
   auto part3     = hwlib::part( oled, hwlib::xy( 0, 48 ), hwlib::xy( 128, 16 ) );
   auto console3  = hwlib::terminal_from( part3, font3 );
   
   console1 
      << "\f" << "Hello world!!" 
      << "\n" << "second line..";
 
   console3
      << "\fBIF FNT";
      
   hwlib::graphics_random_circles( part2 );        
}

