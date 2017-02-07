// ==========================================================================
//
// File      : hwlib.hpp
// Part of   : hwlib library for V1OOPC and V1IPAS
// Copyright : wouter@voti.nl 2016
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#ifndef HWLIB_H
#define HWLIB_H

#ifdef BMPTK_TARGET_arduino_due
   #include "hwlib-due.hpp"
#endif

#ifdef BMPTK_TARGET_db103
   #include "hwlib-db103.hpp"
#endif

#ifdef BMPTK_TARGET_arduino_uno
   #include "hwlib-uno.hpp"
#endif

#ifndef BMPTK_TARGET
   #include "hwlib-all.hpp"
#endif

#endif // HWLIB_ALL_H