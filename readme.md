Hwlib is a C++ classic-OO-style library for close-to-the-hardware 
programming. It is used in a number of Computer Science courses 
at the Hogeschool Utrecht, HBO-ICT.

The typical blink-a-led application code using hwlib 
(assuming a target board like the Arduino Uno that has a default led) is:

```C++
#include "hwlib.hpp"

int main( void ){   
   auto led = hwlib::target::led;
   hwlib::blink( led );
}
```

For the documentation: run 
```
   doxygen doxyfiles/doxyfile
```
and open index.html (which redirects to html/index.html).

-----------------------------------------------------------------------------      
      
(c) Wouter van Ooijen (wouter@voti.nl) 2017-2019

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at 
http://www.boost.org/LICENSE_1_0.txt)     

note: include/hwlib-arduino-due-system-sam3xa.inc is (c) atmel, 
under asf license.
      