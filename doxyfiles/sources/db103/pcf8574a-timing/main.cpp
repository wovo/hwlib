// ==========================================================================
//
// kitt on 8 LEDs on PCF8574A connected to a DB013 board (LPC1114)
//
// (c) Wouter van Ooijen (wouter@voti.nl) 2017-2019
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt) 
//
// ==========================================================================

#include "hwlib.hpp"

void direct( hwlib::pcf8574a & chip ){
    
   //! [[Doxygen flush example]]

   auto t1 = hwlib::now_us();
   
   chip.p0.write( 0 );   chip.p0.flush();
   chip.p1.write( 0 );   chip.p1.flush();
   chip.p2.write( 0 );   chip.p2.flush();
   chip.p3.write( 0 );   chip.p3.flush();
   
   auto t2 = hwlib::now_us();
   hwlib::cout << "direct took " << t2 - t1 << " us.\n";
   
   // writing to pins on a pcf8574a chip, flushing each pin immediately
   
   //! [[Doxygen flush example]]   
}

void buffered( hwlib::pcf8574a & chip ){
   //! [[Doxygen buffered example]]

   // writing to pins on a pcf8574a chip, flushing after all writes
   
   auto t1 = hwlib::now_us();
   
   chip.p0.write( 0 );  
   chip.p1.write( 0 );   
   chip.p2.write( 0 );   
   chip.p3.write( 0 );   

   chip.p0.flush();
   chip.p1.flush();
   chip.p2.flush();
   chip.p3.flush();
   
   auto t2 = hwlib::now_us();
   hwlib::cout << "buffered took " << t2 - t1 << " us.\n";

   //! [[Doxygen buffered example]]   
}


int main(){

   auto scl           = hwlib::target::pin_oc{ 0, 4 };
   auto sda           = hwlib::target::pin_oc{ 0, 5 };
   auto i2c_bus       = hwlib::i2c_bus_bit_banged_scl_sda{ scl,sda };
   auto chip_channel  = i2c_bus.channel( 0x38 );
   auto chip          = hwlib::pcf8574a{ chip_channel };
   
   direct( chip );
   buffered( chip );

}