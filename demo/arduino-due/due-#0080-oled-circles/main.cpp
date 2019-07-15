// ==========================================================================
//
// OLED circle demo on DB103
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
   
   auto scl      = hwlib::target::pin_oc{ hwlib::target::pins::scl };
   auto sda      = hwlib::target::pin_oc{ hwlib::target::pins::sda };
   
<<<<<<< HEAD
   auto i2c_bus      = hwlib::i2c_bus_bit_banged_scl_sda( scl, sda );
   auto oled         = hwlib::glcd_oled_i2c_128x64_buffered( i2c_bus ); 
=======
   auto i2c_bus       = hwlib::i2c_bus_bit_banged_scl_sda( scl, sda );
   auto oled          = hwlib::glcd_oled( i2c_bus );  
>>>>>>> 23d687944e7ce90c99c9c2b20f113cce3948c3f4
   
   hwlib::graphics_random_circles( oled );  
   
}
