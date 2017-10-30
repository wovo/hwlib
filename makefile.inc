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
HEADERS           += hwlib-defines.hpp
HEADERS           += hwlib-common.hpp
HEADERS           += hwlib-pin.hpp
HEADERS           += hwlib-pin-dummies.hpp
HEADERS           += hwlib-pin-decorators.hpp
HEADERS           += hwlib-port.hpp
HEADERS           += hwlib-port-from-pins.hpp
HEADERS           += hwlib-port-decorators.hpp
HEADERS           += hwlib-adc.hpp
HEADERS           += hwlib-dac.hpp
HEADERS           += hwlib-console.hpp
HEADERS           += hwlib-graphics.hpp
HEADERS           += hwlib-font-default-8x8.hpp
HEADERS           += hwlib-font-default-16x16.hpp
HEADERS           += hwlib-wait.hpp
HEADERS           += hwlib-ostream.hpp
HEADERS           += hwlib-panic.hpp
HEADERS           += hwlib-i2c.hpp
HEADERS           += hwlib-pcf8574a.hpp
HEADERS           += hwlib-pcf8591.hpp
HEADERS           += hwlib-spi.hpp
HEADERS           += hwlib-hc595.hpp
HEADERS           += hwlib-hd44780.hpp
HEADERS           += hwlib-glcd-5510.hpp
HEADERS           += hwlib-glcd-oled.hpp
HEADERS           += hwlib-string.hpp
HEADERS           += hwlib-demo.hpp

HEADERS           += hwlib-arduino-due.hpp
HEADERS           += hwlib-arduino-uno.hpp
HEADERS           += hwlib-blue-pill.hpp
HEADERS           += hwlib-stm32f103c8.hpp
HEADERS           += hwlib-db103.hpp
HEADERS           += hwlib-native.hpp
