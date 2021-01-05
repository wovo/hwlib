#include "hwlib.hpp"

int main( void ){
   auto servo_pin = hwlib::target::pin_out( hwlib::target::pins::d8 );
   auto servo = hwlib::servo_background( servo_pin );
   const auto steps = 50;
   const auto t = 1'000'000;
   hwlib::sweep( servo, hwlib::ratio( 0 ), hwlib::ratio( 1 ),     t,     steps );
   hwlib::sweep( servo, hwlib::ratio( 1 ), hwlib::ratio( 0 ),     t,     steps );
   hwlib::sweep( servo, hwlib::ratio( 0 ), hwlib::ratio( 1, 2 ),  t / 2, steps / 2 );
}  