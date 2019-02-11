#============================================================================
#
# makefile-include for bmptk: 
# sets 
# - the search path (the hwlib/include directory)
# - the dependencies (all hwlib source files)
# - the sources (only hwlib.cpp)
# 
# (c) Wouter van Ooijen (wouter@voti.nl) 2017
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at 
# http://www.boost.org/LICENSE_1_0.txt)   
#
#============================================================================

SEARCH            += $(HWLIB)/library

SOURCES           += hwlib.cpp
HEADERS           += hwlib.hpp
HEADERS           += hwlib-all.hpp

HEADERS           += core/hwlib-defines.hpp
HEADERS           += core/hwlib-panic.hpp
HEADERS           += core/hwlib-common.hpp

HEADERS           += core/hwlib-pin.hpp
HEADERS           += core/hwlib-pin-dummies.hpp
HEADERS           += core/hwlib-pin-decorators.hpp
HEADERS           += core/hwlib-port.hpp
HEADERS           += core/hwlib-port-from-pins.hpp
HEADERS           += core/hwlib-port-decorators.hpp

HEADERS           += core/hwlib-wait.hpp

HEADERS           += core/hwlib-adc.hpp
HEADERS           += core/hwlib-dac.hpp
HEADERS           += core/hwlib-console.hpp
HEADERS           += core/hwlib-graphics.hpp
HEADERS           += core/hwlib-font-default-8x8.hpp
HEADERS           += core/hwlib-font-default-16x16.hpp
HEADERS           += core/hwlib-ostream.hpp
HEADERS           += core/hwlib-i2c.hpp
HEADERS           += core/hwlib-spi.hpp

HEADERS           += peripherals/hwlib-pcf8574a.hpp
HEADERS           += peripherals/hwlib-pcf8591.hpp
HEADERS           += peripherals/hwlib-hc595.hpp
HEADERS           += peripherals/hwlib-hd44780.hpp
HEADERS           += peripherals/hwlib-glcd-5510.hpp
HEADERS           += peripherals/hwlib-glcd-oled.hpp

HEADERS           += core/hwlib-string.hpp
HEADERS           += core/hwlib-demo.hpp
HEADERS           += core/hwlib-equal.hpp

HEADERS           += targets/hwlib-arduino-due.hpp
HEADERS           += targets/hwlib-arduino-uno.hpp
HEADERS           += targets/hwlib-blue-pill.hpp
HEADERS           += targets/hwlib-stm32f103c8.hpp
HEADERS           += targets/hwlib-db103.hpp
HEADERS           += targets/hwlib-native.hpp
HEADERS           += targets/hwlib-none.hpp
