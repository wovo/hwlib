(c) Wouter van Ooijen (wouter@voti.nl) 2017

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at 
http://www.boost.org/LICENSE_1_0.txt)

This directory and its subdirectories contain 
the hwlib sources (.hpp and .cpp files).

core:        target- and peripheral- independent parts
peripheral:  peripheral chips 
targets:     target micro-controllers and boards
      
      
todo
- document pins & decorators
- test pins & decorators : add test pin
- I2C transaction class -> more efficient oled use - hoe druk je uit dat je zo'n transaction rerf terug kan krjgen?
- more tests for pins and more
- split graphics
- needs class list per category...
- LPC1114 48MHz
- LPC1114 use timer for timing 
- copy-protect relevant classes like i2c transaction
- I2C - write/read single byte
- oled smarter buffer flush
- lines/circles demo optional frame (parameter)
- frame modifier!
- demos split pin_demos, port-demos, graphics-demos