// ==========================================================================
//
// File      : hwlib-my-first-devboard.hpp
// Part of   : C++ hwlib library for close-to-the-hardware OO programming
// Copyright : wouter@voti.nl 2017-2019
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

// this file contains Doxygen lines
/// @file

#ifndef HWLIB_MY_FIRST_DEV_BOARD_H
#define HWLIB_MY_FIRST_DEV_BOARD_H

#include "hwlib-atmega328.hpp"

namespace my_first_dev_board { 
   
class board {
private:

   atmega328::pin_in sw1_pin; 
   atmega328::pin_in sw2_pin;
   atmega328::pin_in sw3_pin;
   atmega328::pin_in sw4_pin;
   
public:   

   atmega328::pin_out buzzer;
   
   atmega328::pin_adc adc;

   hwlib::pin_invert_from_in_t sw1;
   hwlib::pin_invert_from_in_t sw2;
   hwlib::pin_invert_from_in_t sw3;
   hwlib::pin_invert_from_in_t sw4;
      
   atmega328::pin_out red;
   atmega328::pin_out green;
   atmega328::pin_out blue;
   
   atmega328::pin_out led1;
   atmega328::pin_out led2;
   atmega328::pin_out led3;
   atmega328::pin_out led4;
   atmega328::pin_out led5;
   atmega328::pin_out led6;
   atmega328::pin_out led7;
   atmega328::pin_out led8;
   atmega328::pin_out led9;
   
   board():
      sw1_pin( 2, 1 ),
      sw2_pin( 2, 2 ),
      sw3_pin( 2, 3 ),
      sw4_pin( 2, 4 ),

      buzzer( 3, 3 ),
      
      adc( 0 ),
   
      sw1( sw1_pin ),
      sw2( sw2_pin ),
      sw3( sw3_pin ),
      sw4( sw4_pin ),
      
      red(   1, 3 ),
      green( 1, 5 ),
      blue(  1, 4 ),
   
      led1( 3, 2 ),
      led2( 3, 7 ),
      led3( 3, 4 ),
      led4( 1, 0 ),
      led5( 3, 5 ),
      led6( 1, 1 ),
      led7( 3, 6 ),
      led8( 1, 2 ),
      led9( 2, 5 )      
   {}
   
};   

}; // namespace my_first_dev_board

namespace hwlib {

namespace target = ::my_first_dev_board;
const auto target_board = target_boards::my_first_dev_board;
   
}; //namespace hwlib   

#endif // HWLIB_MY_FIRST_DEV_BOARD_H    
