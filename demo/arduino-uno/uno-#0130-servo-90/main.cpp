#include "hwlib.hpp"

int main( void ){
   auto servo_1_pin = hwlib::target::pin_out( hwlib::target::pins::d8 );
   //auto servo_2_pin = hwlib::target::pin_out( hwlib::target::pins::d9 );
   
   auto servo_1 = hwlib::servo_background( servo_1_pin );
   //auto servo_2 = hwlib::servo_background( servo_2_pin );
   
   int n = 1500;
   servo_1.write_us( n );
   //servo_2.write_us( n );
   for(;;){
      hwlib::wait_ms( 1 );
   }      
}  