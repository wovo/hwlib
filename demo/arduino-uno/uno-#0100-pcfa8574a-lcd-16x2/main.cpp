// ==========================================================================
//
// Hello world on an Arduino Uno
//
// (c) Wouter van Ooijen (wouter@voti.nl) 2017
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt) 
//
// ==========================================================================

#include "hwlib.hpp"

namespace target = hwlib::target;

int main( void ){
   auto scl            = hwlib::target::pin_oc( hwlib::target::pins::a0 );
   auto sda            = hwlib::target::pin_oc( hwlib::target::pins::a1 );
      
   auto i2c_bus        = hwlib::i2c_bus_bit_banged_scl_sda{ scl,sda };
   auto chip           = hwlib::pcf8574a{ i2c_bus, 0x3F };
    
   auto d4 = hwlib::pin_out_from( chip.p4 );
   auto d5 = hwlib::pin_out_from( chip.p5 );
   auto d6 = hwlib::pin_out_from( chip.p6 );
   auto d7 = hwlib::pin_out_from( chip.p7 );
   auto d  = hwlib::port_out_from( d4, d5, d6, d7 );
   auto rs = hwlib::pin_out_from( chip.p0 );
   auto rw = hwlib::pin_out_from( chip.p1 );
   auto e  = hwlib::pin_out_from( chip.p2 );
   rw.write( 0 );rw.flush();
     
   auto lcd = hwlib::hd44780( rs, e, d, hwlib::xy( 16, 2 ) );  

   lcd 
      << "\fHello world!"
      //<< "\n=== 2nd line ==="
      << hwlib::flush;

}
