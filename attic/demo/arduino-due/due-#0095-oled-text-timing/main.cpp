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
   
   auto scl           = hwlib::target::pin_oc{ hwlib::target::pins::scl1 };
   auto sda           = hwlib::target::pin_oc{ hwlib::target::pins::sda1 };
   
   auto i2c_bus       = hwlib::i2c_bus_bit_banged_scl_sda( scl, sda );
   auto oled          = hwlib::glcd_oled( i2c_bus );  
   
   auto font          = hwlib::font_default_8x8();
   auto display       = hwlib::terminal_from( oled, font );
   
   // wait for the terminal emulator to start up
   hwlib::wait_ms( 1'000 );   
   
   for(;;){
      auto t1 = hwlib::now_us();
      display 
         << "\f" << "Hello world!!" 
         << "\n" << "second line.."
         << "\t0305" << "pos 3 line 5"
         << "\t0203" << "pos 2 line 3";
      auto t2 = hwlib::now_us();
      hwlib::cout << "chars: " << ( t2 - t1 ) << " us\n";

      t1 = hwlib::now_us();
      display 
         << hwlib::flush;     
      t2 = hwlib::now_us();
      hwlib::cout << "flush: " << ( t2 - t1 ) << " us\n";
   }         
}
