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

// this file includes all hwlib files 
// (except hwlib-doxygen.hpp, which contains only Doxygen stuff)
// to add a file, add it here and in the Makefile.inc

#ifndef HWLIB_ALL_H
#define HWLIB_ALL_H

HWCPP_INCLUDE( hwlib-defines.hpp )
HWCPP_INCLUDE( hwlib-panic.hpp )
HWCPP_INCLUDE( hwlib-common.hpp )
HWCPP_INCLUDE( hwlib-pin.hpp )
HWCPP_INCLUDE( hwlib-pin-dummies.hpp )
HWCPP_INCLUDE( hwlib-pin-decorators.hpp )
HWCPP_INCLUDE( hwlib-port.hpp )
HWCPP_INCLUDE( hwlib-port-from-pins.hpp )
HWCPP_INCLUDE( hwlib-port-decorators.hpp )
HWCPP_INCLUDE( hwlib-adc.hpp )
HWCPP_INCLUDE( hwlib-dac.hpp )
HWCPP_INCLUDE( hwlib-console.hpp )
HWCPP_INCLUDE( hwlib-graphics.hpp )
HWCPP_INCLUDE( hwlib-font-default-8x8.hpp )
HWCPP_INCLUDE( hwlib-font-default-16x16.hpp )
HWCPP_INCLUDE( hwlib-wait.hpp )
HWCPP_INCLUDE( hwlib-ostream.hpp )
HWCPP_INCLUDE( hwlib-i2c.hpp )
HWCPP_INCLUDE( hwlib-pcf8574a.hpp )
HWCPP_INCLUDE( hwlib-pcf8591.hpp )
HWCPP_INCLUDE( hwlib-spi.hpp )
HWCPP_INCLUDE( hwlib-hc595.hpp )
HWCPP_INCLUDE( hwlib-hd44780.hpp )
HWCPP_INCLUDE( hwlib-glcd-5510.hpp )
HWCPP_INCLUDE( hwlib-glcd-oled.hpp )
HWCPP_INCLUDE( hwlib-matrix-keypad.hpp )
HWCPP_INCLUDE( hwlib-string.hpp )
HWCPP_INCLUDE( hwlib-demo.hpp )

#endif // HWLIB_ALL_H