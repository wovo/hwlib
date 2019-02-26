(c) Wouter van Ooijen (wouter@voti.nl) 2017

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at 
http://www.boost.org/LICENSE_1_0.txt)

This directory and its subdirectories contain 
the hwlib sources (.hpp and .cpp files).

core:        target- and peripheral- independent parts
peripheral:  peripheral chips 
targets:     target micro-controllers and boards

Open Issues and further work
- string needs rework
- lpc1114 48 MHz
      
      
todo
<<<<<<< HEAD
- document pins & decorators
=======
- rename to _*_t for invert, all, from
>>>>>>> f4298cb2616827df3f0fe6c5a4f959ef0c42f16d
- test pins & decorators : add test pin
- more tests for pins and more
- needs class list per category...
- LPC1114 use timer for timing 
- copy-protect relevant classes like i2c transaction
- I2C - write/read single byte
- oled smarter buffer flush, and dumb version
- lines/circles demo optional frame (parameter)? or frame decorator?
- frame modifier!
- check pin modifiers for need of direction-flush!
- check demos for needed flushes
- 2017-2019
- always use constructor function
- 16 pins or 8 for port?
- string with avr?
- compare i2c and spi
- add 'best used via' to all generator functions
- more general text (buffering, generator functions, conversions)
- re-seat the targets
- targets auto-generate from text in targets??
- check more files, not done yet!
- keypad demo (due)
- no [[examples]] needed in demo
- due demos' rename / renumber
- now two ways of keep-out-of-doxygen: ifdef DOXYGEN and ///cond
- update avr-gcc from http://blog.zakkemble.net/avr-gcc-builds/
- update arm gcc to 8.2
- difference between 16x16 and 8x8 fonts??
- avr8 problem with 16x16 font
- nr4f24 lib


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

graphics/hwlib-graphics-xy.hpp
graphics/hwlib-graphics-color.hpp
graphics/hwlib-graphics-image.hpp
graphics/hwlib-graphics-window.hpp
graphics/hwlib-graphics-drawables.hpp
graphics/hwlib-graphics-window-decorators.hpp
graphics/hwlib-graphics-window-demos.hpp
graphics/hwlib-graphics-console.hpp
graphics/hwlib-graphics-font-8x8.hpp
graphics/hwlib-graphics-font-16x16.hpp

peripherals/hwlib-pcf8574a.hpp
peripherals/hwlib-pcf8591.hpp
peripherals/hwlib-hc595.hpp
peripherals/hwlib-hd44780.hpp
peripherals/hwlib-glcd-5510.hpp
peripherals/hwlib-glcd-oled.hpp

targets/hwlib-arduino-due.hpp
targets/hwlib-arduino-uno.hpp
targets/hwlib-blue-pill.hpp
targets/hwlib-stm32f103c8.hpp
targets/hwlib-db103.hpp
targets/hwlib-native.hpp
targets/hwlib-none.hpp