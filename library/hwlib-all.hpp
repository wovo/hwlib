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

#include "hwlib-defines.hpp"
#include "hwlib-common.hpp"
#include "hwlib-pin.hpp"
#include "hwlib-pin-dummies.hpp"
#include "hwlib-pin-decorators.hpp"
#include "hwlib-port.hpp"
#include "hwlib-port-from-pins.hpp"
#include "hwlib-port-decorators.hpp"
#include "hwlib-adc.hpp"
#include "hwlib-dac.hpp"
#include "hwlib-console.hpp"
#include "hwlib-graphics.hpp"
#include "hwlib-font-default-8x8.hpp"
#include "hwlib-font-default-16x16.hpp"
#include "hwlib-wait.hpp"
#include "hwlib-ostream.hpp"
#include "hwlib-panic.hpp"
#include "hwlib-i2c.hpp"
#include "hwlib-pcf8574a.hpp"
#include "hwlib-pcf8591.hpp"
#include "hwlib-spi.hpp"
#include "hwlib-hc595.hpp"
#include "hwlib-hd44780.hpp"
#include "hwlib-glcd-5510.hpp"
#include "hwlib-glcd-oled.hpp"
//#include "hwlib-string.hpp"
#include "hwlib-demo.hpp"

#endif // HWLIB_ALL_H