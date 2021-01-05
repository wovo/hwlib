// ==========================================================================
//
// File      : hwlib.hpp
// Part of   : C++ hwlib library for close-to-the-hardware OO programming
// Copyright : wouter@voti.nl 2017-2019
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

// An application defines the appropriate HWLIB_TARGET_* marco and 
// include this hwlib.hpp file.

// The bmptk build system will define the HWLIB_TARGET_* macro
// base on the TARGET specified in the makefile.

#ifndef HWLIB_H
#define HWLIB_H

#define HWLIB_QUOTE( FILE ) #FILE
#define HWLIB_INCLUDE( FILE ) HWLIB_QUOTE( FILE )

/// - HWLIB_TARGET_db103 : DB103 board (LPC1114FN28/102 chip)
#ifdef HWLIB_TARGET_db103
   #define HWLIB_TARGET
   #include HWLIB_INCLUDE( targets/hwlib-db103.hpp )
#endif

/// - HWLIB_TARGET_arduino_uno : Arduino Uno (ATMega328P chip)
#ifdef HWLIB_TARGET_arduino_uno
   #define HWLIB_TARGET
   #include HWLIB_INCLUDE( targets/hwlib-arduino-uno.hpp )
#endif

/// - HWLIB_TARGET_my_first_devboard : board with Arduino Nano (ATMega328P chip)
#ifdef HWLIB_TARGET_my_first_dev_board
   #define HWLIB_TARGET
   #include HWLIB_INCLUDE( targets/hwlib-my-first-dev-board.hpp )
#endif

/// - HWLIB_TARGET_arduino_due : Arduino Due(ATSAM3X8E chip chip)
#ifdef HWLIB_TARGET_arduino_due
   #define HWLIB_TARGET
   #include HWLIB_INCLUDE( targets/hwlib-arduino-due.hpp )
#endif

/// - HWLIB_TARGET_blue_pill : Blue Pill board (stm32f103c8 chip)
#ifdef HWLIB_TARGET_blue_pill
   #define HWLIB_TARGET
   #include HWLIB_INCLUDE( targets/hwlib-blue-pill.hpp )
#endif

/// - HWLIB_TARGET_stm32f103c8 : stm32f103c8 chip
#ifdef HWLIB_TARGET_stm32f103c8
   #define HWLIB_TARGET
   #include HWLIB_INCLUDE( targets/hwlib-stm32f103c8.hpp )
#endif

#ifdef BMPTK_TARGET_scouting_lock
   #define HWLIB_TARGET
   #include HWLIB_INCLUDE( hwlib-scouting-lock.hpp )
#endif

/// - HWLIB_TARGET_native : Windows native
#ifdef HWLIB_TARGET_Windows
   #define HWLIB_TARGET
   #include HWLIB_INCLUDE( targets/hwlib-native-sfml.hpp )
#endif

/// - HWLIB_TARGET_native : Linux native 
#ifdef HWLIB_TARGET_Linux
   #define HWLIB_TARGET
   #include HWLIB_INCLUDE( targets/hwlib-native-sfml.hpp )
#endif

#ifdef HWLIB_TARGET_pyd
   #define HWLIB_TARGET
   #include HWLIB_INCLUDE( targets/hwlib-native.hpp )
#endif

#ifndef HWLIB_TARGET
   #define HWLIB_TARGET
   #include HWLIB_INCLUDE( targets/hwlib-none.hpp )
#endif

#endif // HWLIB_ALL_H