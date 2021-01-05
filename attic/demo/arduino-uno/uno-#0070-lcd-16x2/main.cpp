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
    auto d  = hwlib::port_out_from( d4, d5, d6, d7 );
    auto rs = target::pin_out( target::pins::d8 );
    auto e  = target::pin_out( target::pins::d9 );
    auto bl = target::pin_out( target::pins::d10 );
    
    // select the LCD size.
    // the shield has a 2 x 16 LCD
    // auto lcd = hwlib::hd44780( rs, e, d, 1, 16 );  
    auto lcd = hwlib::hd44780( rs, e, d, hwlib::xy( 16, 2) );  
    // auto lcd = hwlib::hd44780( rs, e, d, 4, 20 );  
    // auto lcd = hwlib::hd44780( rs, e, d, 2, 40 );  
     
    bl.write( 0 );
    hwlib::wait_ms( 500 );    
    bl.write( 1 );
  
    lcd 
       << "\fHello world!        | this is only for a"
       << "\nnice to meet you    | 40 col. display." 
       << "\t0002line 3 ============X"
       << "\nline 4 ============X"
       << hwlib::flush;
 
}
