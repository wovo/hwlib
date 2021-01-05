#include "hwlib.hpp"

int main( void ){
   hwlib::wait_ms( 1000 );
   hwlib::cout << "2 servo wave demo\n";
   
   //auto p = hwlib::servo_properties( 1'000, 2'000 );
   auto p = hwlib::servo_properties();

   auto servo_1_pin = hwlib::target::pin_out( hwlib::target::pins::d8 );
   auto servo_2_pin = hwlib::target::pin_out( hwlib::target::pins::d9 );
   
   auto servo_1 = hwlib::servo_background( servo_1_pin, p );
   auto servo_2 = hwlib::servo_background( servo_2_pin, p );
   
   auto inv_1 = hwlib::invert( servo_1 );
   
   auto both = hwlib::all( inv_1, servo_2 );
   (void) servo_1;
   (void) servo_2;
   (void) both;
   
   auto & s = both; // hwlib::invert( servo_1 );
   
   const auto steps = 50;
   const auto t = 1'000'000;
   
   hwlib::sweep( s, hwlib::ratio( 0 ), hwlib::ratio( 1 ),     t,     steps );
   hwlib::sweep( s, hwlib::ratio( 1 ), hwlib::ratio( 0 ),     t,     steps );
   hwlib::sweep( s, hwlib::ratio( 0 ), hwlib::ratio( 1, 2 ),  t / 2, steps / 2 );  
}  