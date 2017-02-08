// ==========================================================================
//
// blink the LED on an Arduino Due
//
// This file is in the public domain.
//
// =========================================================================

//! [[Doxygen blink example]]
#include "hwlib.hpp"

int main( void ){	
   // kill the watchdog
   WDT->WDT_MR = WDT_MR_WDDIS;
   
   auto led = hwlib::target::pin_out( 1, 27 );
   hwlib::blink( led );
}
//! [[Doxygen blink example]]
