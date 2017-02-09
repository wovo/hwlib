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

#ifdef BMPTK_TARGET_arduino_due
   #include "hwlib-arduino-due.hpp"
#endif

#ifdef BMPTK_TARGET_db103
   #include "hwlib-db103.hpp"
#endif

#ifdef BMPTK_TARGET_arduino_uno
   #include "hwlib-arduino-uno.hpp"
#endif

#ifdef BMPTK_TARGET_native
   #include "hwlib-native.hpp"
#endif

#ifndef BMPTK_TARGET
   #include "hwlib-all.hpp"
#endif

#endif // HWLIB_ALL_H