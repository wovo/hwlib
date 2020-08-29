// ==========================================================================
//
// File      : hwlib-all.hpp
// Part of   : C++ hwlib library for close-to-the-hardware OO programming
// Copyright : wouter@voti.nl 2017-2019
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
// C/C++ library files are included here rather than in the individual
// library files.
// The individual hwlib header files depend on the order in which they 
// are included here, and don't have multiple-include guards.
// They are not meant to be included individually.
//
// In normal use, this file is included by a target-specific hwlib file.

#ifndef HWLIB_ALL_H
#define HWLIB_ALL_H

#include <cstdint>
#include <array>
#include <cstddef>
#include <type_traits>
#include <numeric>

#include HWLIB_INCLUDE( core/hwlib-defines.hpp )
#include HWLIB_INCLUDE( core/hwlib-targets.hpp )
#include HWLIB_INCLUDE( core/hwlib-panic.hpp )
#include HWLIB_INCLUDE( core/hwlib-noncopyable.hpp )
#include HWLIB_INCLUDE( core/hwlib-common.hpp )
#include HWLIB_INCLUDE( core/hwlib-ratio.hpp )
#include HWLIB_INCLUDE( core/hwlib-background.hpp )
#include HWLIB_INCLUDE( core/hwlib-xy.hpp )
#include HWLIB_INCLUDE( core/hwlib-color.hpp )
#include HWLIB_INCLUDE( core/hwlib-random.hpp )
#include HWLIB_INCLUDE( core/hwlib-wait.hpp )

#include HWLIB_INCLUDE( pins/hwlib-pin.hpp )
#include HWLIB_INCLUDE( pins/hwlib-pin-dummies.hpp )
#include HWLIB_INCLUDE( pins/hwlib-pin-stores.hpp )
#include HWLIB_INCLUDE( pins/hwlib-pin-from-pin.hpp )
#include HWLIB_INCLUDE( pins/hwlib-pin-invert.hpp )
#include HWLIB_INCLUDE( pins/hwlib-pin-all.hpp )
#include HWLIB_INCLUDE( pins/hwlib-pin-direct.hpp )
#include HWLIB_INCLUDE( pins/hwlib-pin-demos.hpp )

#include HWLIB_INCLUDE( ports/hwlib-port.hpp )
#include HWLIB_INCLUDE( ports/hwlib-port-from-port.hpp )
#include HWLIB_INCLUDE( ports/hwlib-port-from-pins.hpp )
#include HWLIB_INCLUDE( ports/hwlib-port-invert.hpp )
#include HWLIB_INCLUDE( ports/hwlib-port-all.hpp )
#include HWLIB_INCLUDE( ports/hwlib-port-direct.hpp )
#include HWLIB_INCLUDE( ports/hwlib-port-demos.hpp )

#include HWLIB_INCLUDE( char-io/hwlib-ostream.hpp )
#include HWLIB_INCLUDE( char-io/hwlib-istream.hpp )
#include HWLIB_INCLUDE( char-io/hwlib-bb-uart.hpp )
#include HWLIB_INCLUDE( char-io/hwlib-console.hpp )
#include HWLIB_INCLUDE( char-io/hwlib-terminal.hpp )
#include HWLIB_INCLUDE( char-io/hwlib-terminal-demos.hpp )

#include HWLIB_INCLUDE( core/hwlib-test.hpp )
#include HWLIB_INCLUDE( core/hwlib-string.hpp )

#include HWLIB_INCLUDE( core/hwlib-adc.hpp )
#include HWLIB_INCLUDE( core/hwlib-dac.hpp )
#include HWLIB_INCLUDE( core/hwlib-dac-demos.hpp )
#include HWLIB_INCLUDE( core/hwlib-servo.hpp )
#include HWLIB_INCLUDE( core/hwlib-i2c.hpp )
#include HWLIB_INCLUDE( core/hwlib-spi.hpp )

#include HWLIB_INCLUDE( graphics/hwlib-graphics-image.hpp )
#include HWLIB_INCLUDE( graphics/hwlib-graphics-image-decorators.hpp )
#include HWLIB_INCLUDE( graphics/hwlib-graphics-font.hpp )
#include HWLIB_INCLUDE( graphics/hwlib-graphics-window.hpp )
#include HWLIB_INCLUDE( graphics/hwlib-graphics-canvas.hpp )
#include HWLIB_INCLUDE( graphics/hwlib-graphics-drawables.hpp )
#include HWLIB_INCLUDE( graphics/hwlib-graphics-window-decorators.hpp )
#include HWLIB_INCLUDE( graphics/hwlib-graphics-window-demos.hpp )
#include HWLIB_INCLUDE( graphics/hwlib-graphics-window-terminal.hpp )
#include HWLIB_INCLUDE( graphics/hwlib-graphics-font-8x8.hpp )
#include HWLIB_INCLUDE( graphics/hwlib-graphics-font-16x16.hpp )

#include HWLIB_INCLUDE( peripherals/hwlib-pcf8574.hpp )
#include HWLIB_INCLUDE( peripherals/hwlib-pcf8591.hpp )
#include HWLIB_INCLUDE( peripherals/hwlib-hc595.hpp )
#include HWLIB_INCLUDE( peripherals/hwlib-hd44780.hpp )
#include HWLIB_INCLUDE( peripherals/hwlib-glcd-5510.hpp )
#include HWLIB_INCLUDE( peripherals/hwlib-glcd-oled.hpp )
#include HWLIB_INCLUDE( peripherals/hwlib-matrix-keypad.hpp )
#include HWLIB_INCLUDE( peripherals/hwlib-servo-background.hpp )


#endif // HWLIB_ALL_H
