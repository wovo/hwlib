// ==========================================================================
//
// File      : hwlib.hpp
// Part of   : C++ hwlib library for close-to-the-hardware OO programming
// Copyright : wouter@voti.nl 2017
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#ifndef HWLIB_H
#define HWLIB_H

#define HWLIB_QUOTE( FILE ) #FILE
#define HWLIB_INCLUDE( FILE ) HWLIB_QUOTE( FILE )

#ifdef BMPTK_TARGET_arduino_due
   #include HWLIB_INCLUDE( hwlib-arduino-due.hpp )
#endif

#ifdef BMPTK_TARGET_db103
   #include HWLIB_INCLUDE( hwlib-db103.hpp )
#endif

#ifdef BMPTK_TARGET_arduino_uno
   #include HWLIB_INCLUDE( hwlib-arduino-uno.hpp )
#endif

#ifdef BMPTK_TARGET_stm32f103c8
   #include HWLIB_INCLUDE( hwlib-stm32f103c8.hpp )
#endif

#ifdef BMPTK_TARGET_blue_pill
   #include HWLIB_INCLUDE( hwlib-blue-pill.hpp )
#endif

#ifdef BMPTK_TARGET_native
   HWLIB_INCLUDE( hwlib-native.hpp )
#endif

#ifdef BMPTK_TARGET_pyd
   HWLIB_INCLUDE( hwlib-native.hpp )
#endif

#ifndef BMPTK_TARGET
   HWLIB_INCLUDE( hwlib-all.hpp )
#endif

#endif // HWLIB_ALL_H