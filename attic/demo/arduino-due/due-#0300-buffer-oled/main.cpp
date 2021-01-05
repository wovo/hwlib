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
   
   auto canvas        = hwlib::canvas_bw< 256, 128 >(); 
   auto font1         = hwlib::font_default_8x8();
   auto console       = hwlib::terminal_from( canvas, font1 );
     
   console
      << "It is an ancient Mariner,\n"
      << "And he stoppeth one of three.\n"
      << "'By thy long grey beard and glittering eye,\n"
      << "Now wherefore stopp'st thou me?\n"
      << "\n"
      << "The Bridegroom's doors are opened wide,\n"
      << "And I am next of kin;\n"
      << "The guests are met, the feast is set:\n"
      << "May'st hear the merry din.'\n"
      << hwlib::flush;    
      
   oled.clear();      
   oled.write( 
      hwlib::xy( 0, 0 ), 
      part( canvas.as_image, hwlib::xy( 0, 0 ), oled.size ) );
   hwlib::line( hwlib::xy( 2,2 ), hwlib::xy( 20,20), oled.background ).draw( oled );
   oled.flush();  
}
