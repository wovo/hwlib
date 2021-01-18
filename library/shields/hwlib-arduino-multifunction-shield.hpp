// ==========================================================================
//
// File      : hwlib-arduino-multifunction-shield.hpp
// Part of   : C++ hwlib library for close-to-the-hardware OO programming
// Copyright : wouter@voti.nl 2021
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

// included only via hwlib.hpp, hence no multiple-include guard is needed

// https://www.robkalmeijer.nl/techniek/computer/arduino/uno/mfs/index.html

// this file contains Doxygen lines
/// @file

#ifdef HWLIB_TARGET_arduino_uno

namespace hwlib {
   
class multifunction_shield {
   
   target::pin_out led_1_inv, led_2_inv, led_3_inv, led_4_inv;
   target::pin_in switch_1_inv, switch_2_inv, switch_3_inv;
   target::pin_out beeper_inv;
   
public:   

   hwlib::pin_invert_from_out_t led_1, led_2, led_3, led_4;
   hwlib::port_out_from_pins_t leds;
   
   hwlib::pin_invert_from_in_t switch_1, switch_2, switch_3;
   hwlib::port_in_from_pins_t switches;

   hwlib::pin_invert_from_out_t beeper;

   multifunction_shield():
      led_1_inv( target::pins::d13 ),
      led_2_inv( target::pins::d12 ),
      led_3_inv( target::pins::d11 ),
      led_4_inv( target::pins::d10 ),
      
      switch_1_inv( target::pins::a1 ),
      switch_2_inv( target::pins::a2 ),
      switch_3_inv( target::pins::a3 ),
      
      beeper_inv( target::pins::d3 ),

      led_1( led_1_inv ),
      led_2( led_2_inv ),
      led_3( led_3_inv ),
      led_4( led_4_inv ),
      leds( led_1, led_2, led_3, led_4 ),
      
      switch_1( switch_1_inv ),
      switch_2( switch_2_inv ),
      switch_3( switch_3_inv ),
      switches( switch_1, switch_2, switch_3 ),
      
      beeper( beeper_inv )
   {
      led_1.write( 0 ); led_1.flush();
      led_2.write( 0 ); led_2.flush();
      led_3.write( 0 ); led_3.flush();
      led_4.write( 0 ); led_4.flush();
      
      beeper.write( 0 ); beeper.flush();
      
   }
   
   // missing:
   // 7-segment displays - needs library support
   // potentiometer A/D input
   // LM35
   // DS1820
   // IR receiver
   // APC220
   
}; // class multifunction_shield

}; // namespace hwlib 

#endif
