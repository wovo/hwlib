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

#define HWCPP_QUOTE( FILE ) #FILE
#define HWCPP_INCLUDE( FILE ) HWCPP_QUOTE( library/FILE )

#ifdef BMPTK_TARGET_arduino_due
   HWCPP_INCLUDE( hwlib-arduino-due.hpp )
#endif

#ifdef BMPTK_TARGET_db103
   HWCPP_INCLUDE( hwlib-db103.hpp )
#endif

#ifdef BMPTK_TARGET_arduino_uno
   HWCPP_INCLUDE( hwlib-arduino-uno.hpp )
#endif

#ifdef BMPTK_TARGET_stm32f103c8
   HWCPP_INCLUDE( hwlib-stm32f103c8.hpp )
#endif

#ifdef BMPTK_TARGET_blue_pill
   HWCPP_INCLUDE( hwlib-blue-pill.hpp )
#endif

#ifdef BMPTK_TARGET_native
   HWCPP_INCLUDE( hwlib-native.hpp )
#endif

#ifdef BMPTK_TARGET_pyd
   HWCPP_INCLUDE( hwlib-native.hpp )
#endif

#ifndef BMPTK_TARGET
   HWCPP_INCLUDE( hwlib-all.hpp )
#endif

#endif // HWLIB_ALL_H