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

#include HWLIB_INCLUDE( hwlib-defines.hpp )
#include HWLIB_INCLUDE( hwlib-panic.hpp )
#include HWLIB_INCLUDE( hwlib-common.hpp )
#include HWLIB_INCLUDE( hwlib-pin.hpp )
#include HWLIB_INCLUDE( hwlib-pin-dummies.hpp )
#include HWLIB_INCLUDE( hwlib-pin-decorators.hpp )
#include HWLIB_INCLUDE( hwlib-port.hpp )
#include HWLIB_INCLUDE( hwlib-port-from-pins.hpp )
#include HWLIB_INCLUDE( hwlib-port-decorators.hpp )
#include HWLIB_INCLUDE( hwlib-adc.hpp )
#include HWLIB_INCLUDE( hwlib-dac.hpp )
#include HWLIB_INCLUDE( hwlib-console.hpp )
#include HWLIB_INCLUDE( hwlib-graphics.hpp )
#include HWLIB_INCLUDE( hwlib-font-default-8x8.hpp )
#include HWLIB_INCLUDE( hwlib-font-default-16x16.hpp )
#include HWLIB_INCLUDE( hwlib-wait.hpp )
#include HWLIB_INCLUDE( hwlib-ostream.hpp )
#include HWLIB_INCLUDE( hwlib-i2c.hpp )
#include HWLIB_INCLUDE( hwlib-pcf8574a.hpp )
#include HWLIB_INCLUDE( hwlib-pcf8591.hpp )
#include HWLIB_INCLUDE( hwlib-spi.hpp )
#include HWLIB_INCLUDE( hwlib-hc595.hpp )
#include HWLIB_INCLUDE( hwlib-hd44780.hpp )
#include HWLIB_INCLUDE( hwlib-glcd-5510.hpp )
#include HWLIB_INCLUDE( hwlib-glcd-oled.hpp )
#include HWLIB_INCLUDE( hwlib-matrix-keypad.hpp )
#include HWLIB_INCLUDE( hwlib-string.hpp )
#include HWLIB_INCLUDE( hwlib-demo.hpp )

#endif // HWLIB_ALL_H