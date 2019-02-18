// ==========================================================================
//
// File      : hwlib-all.hpp
// Part of   : C++ hwlib library for close-to-the-hardware OO programming
// Copyright : wouter@voti.nl 2017
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

// This file includes all target-independent hwlib files 
// (except hwlib-doxygen.hpp, which contains only Doxygen stuff)
// to add a file, add it here and in the Makefile.inc
//
// The individual hwlib header files depend on the order in which they 
// are included here, and don't have multiple-include guards.
// They are not meant to be included individually.
//
// In normal use, this file is included by a target-specific hwlib file.

#ifndef HWLIB_ALL_H
#define HWLIB_ALL_H

#include <cstdint>
#include <array>

#include HWLIB_INCLUDE( core/hwlib-defines.hpp )
#include HWLIB_INCLUDE( core/hwlib-panic.hpp )
#include HWLIB_INCLUDE( core/hwlib-common.hpp )

#include HWLIB_INCLUDE( core/hwlib-pin.hpp )
#include HWLIB_INCLUDE( core/hwlib-pin-dummies.hpp )
#include HWLIB_INCLUDE( core/hwlib-pin-stores.hpp )
#include HWLIB_INCLUDE( core/hwlib-pin-from.hpp )
#include HWLIB_INCLUDE( core/hwlib-pin-invert.hpp )
#include HWLIB_INCLUDE( core/hwlib-pin-all.hpp )
#include HWLIB_INCLUDE( core/hwlib-port.hpp )
#include HWLIB_INCLUDE( core/hwlib-port-from-pins.hpp )
#include HWLIB_INCLUDE( core/hwlib-port-decorators.hpp )

#include HWLIB_INCLUDE( core/hwlib-wait.hpp )

#include HWLIB_INCLUDE( core/hwlib-adc.hpp )
#include HWLIB_INCLUDE( core/hwlib-dac.hpp )
#include HWLIB_INCLUDE( core/hwlib-ostream.hpp )
#include HWLIB_INCLUDE( core/hwlib-console.hpp )
#include HWLIB_INCLUDE( core/hwlib-graphics.hpp )
#include HWLIB_INCLUDE( core/hwlib-font-default-8x8.hpp )
#include HWLIB_INCLUDE( core/hwlib-font-default-16x16.hpp )
#include HWLIB_INCLUDE( core/hwlib-i2c.hpp )
#include HWLIB_INCLUDE( core/hwlib-spi.hpp )

#include HWLIB_INCLUDE( peripherals/hwlib-pcf8574a.hpp )
#include HWLIB_INCLUDE( peripherals/hwlib-pcf8591.hpp )
#include HWLIB_INCLUDE( peripherals/hwlib-hc595.hpp )
#include HWLIB_INCLUDE( peripherals/hwlib-hd44780.hpp )
#include HWLIB_INCLUDE( peripherals/hwlib-glcd-5510.hpp )
#include HWLIB_INCLUDE( peripherals/hwlib-glcd-oled.hpp )
#include HWLIB_INCLUDE( peripherals/hwlib-matrix-keypad.hpp )

#include HWLIB_INCLUDE( core/hwlib-string.hpp )
#include HWLIB_INCLUDE( core/hwlib-demo.hpp )
#include HWLIB_INCLUDE( core/hwlib-test.hpp )

#endif // HWLIB_ALL_H