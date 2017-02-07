#include "hwlib.hpp"

int main( void ){	
   // kill the watchdog
   WDT->WDT_MR = WDT_MR_WDDIS;
   
   auto led = hwlib::target::pin_out( 1, 27 );
   hwlib::blink( led );
}
