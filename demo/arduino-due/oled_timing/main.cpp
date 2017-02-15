#include "hwlib.hpp"

namespace target = hwlib::target;

template< typename T >
void time( const char *name, T lambda ){   
   auto start = hwlib::now_us();
   lambda();
   auto end = hwlib::now_us();
   
   hwlib::cout 
      << name
      << " : "
      << end - start 
      << "us\n"
      << hwlib::flush;

}

int main( void ){	
   // kill the watchdog
   WDT->WDT_MR = WDT_MR_WDDIS;
   
   // create the i2c-interfaced display
   auto scl = target::pin_oc( target::pins::scl );
   auto sda = target::pin_oc( target::pins::sda );
   auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );
   auto display = hwlib::glcd_oled( i2c_bus, 0x3c );   
   
   time( 
      "clear - unbuffered", 
      [&](){ 
         display.clear(); 
      } );
      
   time( 
      "clear - buffered", 
      [&](){ 
         display.clear_buffered(); 
         // display.clear( hwlib::buffering::buffered ); 
         display.flush();
      } );
}
