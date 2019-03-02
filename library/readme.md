(c) Wouter van Ooijen (wouter@voti.nl) 2017-2019

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at 
http://www.boost.org/LICENSE_1_0.txt)

This directory and its subdirectories contain 
the hwlib sources (.hpp and .cpp files).

char-io         : character input/output 
core            : what did not fit elsewhere
graphics        : graphic window stuff
peripherals     : peripheral chips 
pins            : GPIO pins
ports           : ports (bundels of pins)
targets         : target micro-controllers and boards

hwlib.cpp       : must be compiled and linked along
hwlib.hpp       : included by the application
hwlib-all.hpp   : included by a target file, includes everything else

makefile        : dummy makefile, generates an error
