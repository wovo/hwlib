// ==========================================================================
//
// File      : hwlib-doxygen-notes.hpp
// Part of   : C++ hwlib library for close-to-the-hardware OO programming
// Copyright : wouter@voti.nl 2017-2019
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

// this file contains Doxygen lines (of course, that is its only purpose)
/// @file


/// \page notes Notes
///
/// Open issues and further work
/// - string class needs rework, tests and documentation
/// - lpc1114 should run at 48 MHz, and use timer for timing
/// - arduino uno should use timer for timing, and hardware uart
/// - native target should support hwlib:cout and (less urgent) hwlib::cin  
///
/// More-or-less urgent things to do      
/// - test the blue-pil blink (delay)
/// - repair the blue-pillk uart
/// - test doxy code fragments
/// - something wring with matrix keypad
/// - oled direct
/// - demo that displays long string on 1-line character window
/// - sub_terminal like sub_window
/// - port names instead of numbers
/// - yield in oled long i2c transfer!
/// - uno hardware uart note limitations
/// - uno check other LCD sizes
/// - document pins & decorators
/// - rename to _*_t for invert, all, from
/// - test pins & decorators : add test pin
/// - more tests for pins and more
/// - needs class list per category...
/// - copy-protect relevant classes like i2c transaction
/// - SPI write/read single byte
/// - oled smarter buffer flush, and dumb version
/// - lines/circles demo optional frame (parameter)? or frame decorator?
/// - frame modifier!
/// - always use constructor function
/// - string partial problem with avr?
/// - compare i2c and spi
/// - add 'best used via' to all generator functions
/// - more general text (buffering, generator functions, conversions)
/// - targets auto-generate from text in targets??
/// - check more files, not done yet!
/// - eliminate[[examples]] from demo => doxyfiles
/// - due demos' rename / renumber
/// - now two ways of keep-out-of-doxygen: ifdef DOXYGEN and ///cond
/// - avr8 problem with 16x16 font
/// - nrf24 lib
/// - comment on each }; or the like
/// - list of i2c slave addresses
/// - check SPI for flush
/// - doxy examples compileren
/// - doxy timing example for multiple pins on PCF
/// - doxy.hpp naar doxydirs, split
/// - check matrix, compare size
/// - check 595 buffering
/// - order of info pages
/// - doxygen get targets from hwlib.hpp
///

/*
================================
check
================================

=hwlib.cpp
=hwlib.hpp
=hwlib-all.hpp

=core/hwlib-defines.hpp
=core/hwlib-panic.hpp
=core/hwlib-common.hpp
=core/hwlib-wait.hpp

=core/hwlib-pin.hpp
=core/hwlib-pin-dummies.hpp
=core/hwlib-pin-stores.hpp
=core/hwlib-pin-from-pin.hpp
=core/hwlib-pin-invert.hpp
=core/hwlib-pin-all.hpp
=core/hwlib-pin-direct.hpp
=core/hwlib-pin-demos.hpp

=core/hwlib-port.hpp
=core/hwlib-port-from-port.hpp
=core/hwlib-port-from-pins.hpp
=core/hwlib-port-invert.hpp
=core/hwlib-port-direct.hpp
=core/hwlib-port-demos.hpp

=char-io/hwlib-ostream.hpp
=char-io/hwlib-istream.hpp
=char-io/hwlib-bb-uart.hpp
=char-io/hwlib-console.hpp
=char-io/hwlib-terminal.hpp

=core/hwlib-test.hpp
=core/hwlib-string.hpp

=core/hwlib-adc.hpp
=core/hwlib-dac.hpp
=core/hwlib-dac-demos.hpp
core/hwlib-i2c.hpp
core/hwlib-spi.hpp

=graphics/hwlib-graphics-xy.hpp
=graphics/hwlib-graphics-color.hpp
=graphics/hwlib-graphics-image.hpp
=graphics/hwlib-graphics-window.hpp
=graphics/hwlib-graphics-drawables.hpp
=graphics/hwlib-graphics-window-decorators.hpp
=graphics/hwlib-graphics-window-demos.hpp
=graphics/hwlib-graphics-console.hpp
=graphics/hwlib-graphics-font-8x8.hpp
=graphics/hwlib-graphics-font-16x16.hpp

=peripherals/hwlib-pcf8574a.hpp
=peripherals/hwlib-pcf8591.hpp
=peripherals/hwlib-hc595.hpp
=peripherals/hwlib-hd44780.hpp
peripherals/hwlib-glcd-5510.hpp
peripherals/hwlib-glcd-oled.hpp

targets/hwlib-arduino-due.hpp
targets/hwlib-arduino-uno.hpp
targets/hwlib-blue-pill.hpp
targets/hwlib-stm32f103c8.hpp
targets/hwlib-db103.hpp
targets/hwlib-native.hpp
=targets/hwlib-none.hpp
*/