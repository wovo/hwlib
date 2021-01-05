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
/// Open issues and further work:
/// - string class needs rework, tests and documentation
/// - lpc1114 should run at 48 MHz, and use timer for timing
/// - arduino uno should use timer for timing, and hardware uart
/// - native target should support hwlib:cout and (less urgent) hwlib::cin  
///
/// Things that would be good to do but are not urgent:
/// - add some window decorators, like for instance a frame
/// - comment after each class closing }; 
/// - doxygen class list should be sorted by category
/// - consistency in decorator class names: all xxx_from_yyy_t
/// - document matrix keypart with 4x4 illustrations, add 3x4 demo
/// - add smart-buffering oled version, and read-write version
/// - find out what goes wrong with AVR8 and the 16x16 font
/// - add border decorator for frame, use in demos
/// - single way of keep-out-of-doxygen: ifdef DOXYGEN and ///cond
/// - add a list of i2c slave addresses
/// - add examples for pin & port 'all'
/// - add examples to istream, ostream, graphics, timing, i2c, spi, adc, dac
/// - add examples & more documentation for matrix-of-switches (pics of good & bad foil!)
/// - document the demo's (pin, port, dac)
/// = check and document the 'native' target
/// - add nrf24
/// - use invert() for an inverted window
/// - use part() for a window part, add terminal-part
/// - more documentation for the graphics page
/// - check demo comment titles
/// - how to \\ref to overloaded constructors (graphics)
/// - always use constructor function
/// - more tests, start with pins and ports
/// - targets auto-generate from text in targets??
/// - add 'best used via' to all generator function classes
/// - more text and examples in the graphics documentation
///
/// More-or-less urgent things to do:
/// - https://www.rhydolabz.com/wiki/?p=16424 ; https://alselectro.wordpress.com/2016/05/12/serial-lcd-i2c-module-pcf8574/
/// - document I2C and SPI
/// - check snippet comment titles (or remove?)
/// - solve -lgdi32 
/// - yield in oled i2c
/// - test the blue-pil blink (delay)
/// - repair the blue-pill uart
/// - port names instead of numbers
/// - yield in oled long i2c transfer!
/// - uno hardware uart note limitations
/// - uno check other LCD sizes
/// - rename to _*_t for invert, all, from
/// - test pins & decorators : add test pin
/// - copy-protect relevant classes like i2c transaction
/// - SPI write/read single byte
/// - lines/circles demo optional frame (parameter)? or frame decorator?
/// - more general text (buffering, generator functions, conversions)
/// - check more files, not done yet!
/// - due demos' rename / renumber
/// - check SPI for flush
/// - check 595 buffering
/// - add blue-pill documentation & picture
/// - char stream mux / demux
/// - ostream has format data *inside*: shouild be separate. raw_ostream?
///

/*

To do list

2019 refurbishment
- hwlib equal -> can't be included earlier??
- demo/due/chris oled spi
- uno common files doesn't work => depends on bmptk!! (doesn't work for arduino?)
- add external dependencies notes in doxygen (bmptk, linker, atmega lib stuff)
- 'nowait' I2C

Quality & consistency:
  - file-local objects are not documented? (check ostream)
  - db103 align pin classes
  - more examples (graphics, ...)
  - lcd5510 should use SPI!
  - i2c example of address-only write
  - test for input, output, oc, analog pins of a chip
  - rewrite text for uno (due?) IO pins
  - rename lcd to something that includes oled
  - cleanup oled => ssd1306, provide init code, expose command interface
  - pin decorators - did they exist at one point??
  - also check line length (in tab checker)
  - there is no on-line manual :(
  - columns,lines or other way round, or use position? (ostream, hd44780)

Nice to haves:
  - rectangle (filled), circle (filled), image (external converter)
  - graphics 2"4 LCD
  - targets: Pi, Liliypad85, ESP8266, ST32, MCP430
  - LCD/button shield
  - use and provide ranges (instead of x, y for loops)
  - add an I2C temp sensor for Leo of iets anders
  - I2C read, pcf8574a, demo: copy 1 to 2
  - use an abstraction instead of copied code in the extenders one_pin => pin_out_through_buffer
  - uno A/D, test with LCD shield
  - i2c hd44780 LCD
  - more pin/port cross type decorators

Misc:
  - meer examples lpc1114 - need the hardware!
  - db103 uart?
  - uart gebruikt??
  - rtos??
  - images licences!!
  - check all documentation
  - meer tests voor hwlib::string
  - bmptk...
  - bmptk blink examples
  - linux
  - esp8266 - eerste in bmptk
  - switch due to full speed??
  - geweer hardware aanpassen (private repository??)
  - oled spi, hw spi
  - graphics buffering via buffering::buffered -> ook in text
  - delays moeten 16-bit parameter Zijn ivm AVR en MSP430?
  - uno hello baudrate klopt niet

     lpc due uno
empty 1224 120 176
blink 1268! 420 680
- why is blink uno large??

make tool to extract this kind of info?

bmptk => use usbasp2, has no serial (include uno bootloader?)
but possible with separate serial!

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