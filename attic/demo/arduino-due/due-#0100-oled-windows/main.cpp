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
   
   auto scl           = hwlib::target::pin_oc{ hwlib::target::pins::scl };
   auto sda           = hwlib::target::pin_oc{ hwlib::target::pins::sda };

   auto i2c_bus       = hwlib::i2c_bus_bit_banged_scl_sda( scl, sda );
   auto oled          = hwlib::glcd_oled( i2c_bus );  
   
   auto w1            = hwlib::part( 
      oled, hwlib::xy( 0, 0 ), hwlib::xy( 128, 16 ));  
   auto font1         = hwlib::font_default_8x8();
   auto console1      = hwlib::terminal_from( w1, font1 );
   
   auto w2            = hwlib::part( 
      oled, hwlib::xy( 0, 16 ), hwlib::xy( 128, 48 ));   
   auto font2         = hwlib::font_default_16x16();
   auto console2      = hwlib::terminal_from( w2, font2 );
   
   console1
      << "\f" << "Hello world!!" 
      << "\n" << "second line.."
      << hwlib::flush;     
      
   console2
      << "\f" << "Ho Ho Ho "
      << "\n" << "said"
      << "\n" << "Santa"
      << hwlib::flush;     
}
