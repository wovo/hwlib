Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at 
http://www.boost.org/LICENSE_1_0.txt)

Hwlib is a C++ classic-OO-style library for close-to-the-hardware programming.
It is used in a number of courses at the Hogeschool Utrecht, HBO-ICT.

Run Doxygen in the root to create the documentation.

To use the hwlib from bmptk:
   - define $HLWIB to be the root of hwlib
   - include $(HWLIB)/Makefile.include
   - include "hwlib.hpp" in your code
   
To use hwlib without bmptk:
   - add the hwlib/include to your search
   - (optionally) add the hwlib files to your dependencies
   - add hwlib.cpp to your sources
   - include the appropriate top-level target file in your code,
      for instance hwlib-due.hpp

The license for hwlib is boost:
      
      