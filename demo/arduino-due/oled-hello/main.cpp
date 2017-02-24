#include "hwlib.hpp"

int main( void ){
   
   // kill the watchdog
   WDT->WDT_MR = WDT_MR_WDDIS;
   
      // wait for the PC console to start
   hwlib::wait_ms( 500 );   
   
   namespace target = hwlib::target;
   
   auto scl     = target::pin_oc( target::pins::scl );
   auto sda     = target::pin_oc( target::pins::sda );
   auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl, sda );
   auto oled    = hwlib::glcd_oled( i2c_bus, 0x3c ); 
   
   auto font    = hwlib::font_default_8x8();
   auto display = hwlib::window_ostream( oled, font );
   
   //! [[flush]]
   display 
      << "\f" << "Hello world" 
      << "\n" << "second line"
      << "\t0305" << "pos 3 line 5"
      << hwlib::flush;   
   //! [[flush]]      

}
