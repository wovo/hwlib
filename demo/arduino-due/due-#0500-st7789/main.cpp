#include "hwlib.hpp"

namespace target = hwlib::target;

int main( void ){
   
   // wait for the terminal emulator to start up
   hwlib::wait_ms( 2'000 );
   hwlib::cout << "ST7789 demo\n" << hwlib::flush;   
   
   auto sclk = hwlib::target::pin_out{ hwlib::target::pins::d2 };
   auto mosi = hwlib::target::pin_out{ hwlib::target::pins::d3 };;
   
   auto spi  = hwlib::spi_bus_bit_banged_sclk_mosi_miso{ 
      sclk, mosi, hwlib::pin_in_dummy };
      
   auto dc  = hwlib::target::pin_out{ hwlib::target::pins::d4 };
   auto & cs = hwlib::pin_out_dummy;
   auto rst = hwlib::target::pin_out{ hwlib::target::pins::d5 };

   auto display     = hwlib::st7789_spi_dc_cs_rst( spi, dc, cs, rst );   
   
   for(;;){
      hwlib::cout << __LINE__ << "\n";   
      display.flush();
      hwlib::wait_ms( 1'000 );
   }
   
}
