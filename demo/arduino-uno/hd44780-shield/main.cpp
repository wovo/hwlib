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
    auto d4 = target::pin_out( target::pins::d4 );
    auto d5 = target::pin_out( target::pins::d5 );
    auto d6 = target::pin_out( target::pins::d6 );
    auto d7 = target::pin_out( target::pins::d7 );
    auto d  = hwlib::port_out_from_pins( d4, d5, d6, d7 );
    auto rs = target::pin_out( target::pins::d8 );
    auto e  = target::pin_out( target::pins::d9 );
    auto bl = target::pin_out( target::pins::d10 );
    auto lcd = hwlib::hd44780( rs, e, d, 2, 16 );  
     
    bl.set( 0 );
    hwlib::wait_ms( 500 );    
    bl.set( 1 );
  
    lcd << "\fHello world!\nnice to meet you" << hwlib::flush;
 
}
