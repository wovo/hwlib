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
HEADERS           += core/hwlib-targets.hpp
HEADERS           += core/hwlib-panic.hpp
HEADERS           += core/hwlib-noncopyable.hpp
HEADERS           += core/hwlib-common.hpp
HEADERS           += core/hwlib-ratio.hpp
HEADERS           += core/hwlib-background.hpp
HEADERS           += core/hwlib-color.hpp
HEADERS           += core/hwlib-random.hpp
HEADERS           += core/hwlib-wait.hpp

HEADERS           += pins/hwlib-pin.hpp
HEADERS           += pins/hwlib-pin-dummies.hpp
HEADERS           += pins/hwlib-pin-stores.hpp
HEADERS           += pins/hwlib-pin-from-pin.hpp
HEADERS           += pins/hwlib-pin-invert.hpp
HEADERS           += pins/hwlib-pin-all.hpp
HEADERS           += pins/hwlib-pin-direct.hpp
HEADERS           += pins/hwlib-pin-demos.hpp

HEADERS           += ports/hwlib-port.hpp
HEADERS           += ports/hwlib-port-from-port.hpp
HEADERS           += ports/hwlib-port-from-pins.hpp
HEADERS           += ports/hwlib-port-invert.hpp
HEADERS           += ports/hwlib-port-all.hpp
HEADERS           += ports/hwlib-port-direct.hpp
HEADERS           += ports/hwlib-port-demos.hpp

HEADERS           += char-io/hwlib-ostream.hpp
HEADERS           += char-io/hwlib-istream.hpp
HEADERS           += char-io/hwlib-bb-uart.hpp
HEADERS           += char-io/hwlib-console.hpp
HEADERS           += char-io/hwlib-terminal.hpp
HEADERS           += char-io/hwlib-terminal-demos.hpp

HEADERS           += core/hwlib-test.hpp
HEADERS           += core/hwlib-string.hpp
HEADERS           += core/hwlib-xy.hpp

HEADERS           += core/hwlib-adc.hpp
HEADERS           += core/hwlib-dac.hpp
HEADERS           += core/hwlib-dac-demos.hpp
HEADERS           += core/hwlib-servo.hpp
HEADERS           += core/hwlib-i2c.hpp
HEADERS           += core/hwlib-spi.hpp

HEADERS           += graphics/hwlib-graphics-image.hpp
HEADERS           += graphics/hwlib-graphics-image-decorators.hpp
HEADERS           += graphics/hwlib-graphics-font.hpp
HEADERS           += graphics/hwlib-graphics-window.hpp
HEADERS           += graphics/hwlib-graphics-canvas.hpp
HEADERS           += graphics/hwlib-graphics-drawables.hpp
HEADERS           += graphics/hwlib-graphics-window-decorators.hpp
HEADERS           += graphics/hwlib-graphics-window-demos.hpp
HEADERS           += graphics/hwlib-graphics-window-terminal.hpp
HEADERS           += graphics/hwlib-graphics-font-8x8.hpp
HEADERS           += graphics/hwlib-graphics-font-16x16.hpp

HEADERS           += peripherals/hwlib-pcf8574.hpp
HEADERS           += peripherals/hwlib-pcf8591.hpp
HEADERS           += peripherals/hwlib-hc595.hpp
HEADERS           += peripherals/hwlib-hd44780.hpp
HEADERS           += peripherals/hwlib-glcd-5510.hpp
HEADERS           += peripherals/hwlib-glcd-oled.hpp
HEADERS           += peripherals/hwlib-matrix-keypad.hpp
HEADERS           += peripherals/hwlib-servo-background.hpp

HEADERS           += targets/hwlib-atmega328.hpp
HEADERS           += targets/hwlib-arduino-uno.hpp
HEADERS           += targets/hwlib-my-first-dev-board.hpp
HEADERS           += targets/hwlib-arduino-due.hpp
HEADERS           += targets/hwlib-blue-pill.hpp
HEADERS           += targets/hwlib-stm32f103c8.hpp
#HEADERS           += targets/hwlib-stm32f030x6.hpp
HEADERS           += targets/hwlib-db103.hpp
HEADERS           += targets/hwlib-native-windows.hpp
HEADERS           += targets/hwlib-native-linux.hpp
HEADERS           += targets/hwlib-native-sfml.hpp
HEADERS           += targets/hwlib-none.hpp

RELATIVE ?= $(BMPTK)/..
ifneq ($(wildcard $(HWLIB)/makefile.custom),)
   include $(HWLIB)/makefile.custom
else ifneq ($(wildcard $(HWLIB)/../makefile.custom),)
   include $(HWLIB)/../makefile.custom
else 
   include $(HWLIB)/makefile.local
endif

# add Catch
SEARCH            += $(CATCH)/single_include
SEARCH            += $(CATCH)/single_include/catch2

# add Boost
SEARCH            += $(BOOST)

# add SFML
ifeq ($(TARGET),native)
   ifeq ($(OS),Windows_NT)
      SEARCH            += $(SFML)/include
      LINKER_FLAGS      += -L$(SFML)/lib 
      LINKER_FLAGS      += -lsfml-graphics-s -lsfml-window-s -lsfml-system-s 
      LINKER_FLAGS      += -lopengl32 -lgdi32 -lws2_32 -lwinmm
      DEFINES           += -DSFML_STATIC
   else
      LINKER_FLAGS      += -lsfml-graphics -lsfml-window -lsfml-system 
      DEFINES           += -DSFML_STATIC
   endif
endif

# defer to bmptk 
include           $(BMPTK)/Makefile.inc
