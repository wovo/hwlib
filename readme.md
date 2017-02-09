Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at 
http://www.boost.org/LICENSE_1_0.txt)

xxx

Hwlib is a C++ classic-OO-style library for close-to-the-hardware programming.
It is used in a number of courses at the Hogeschool Utrecht, HBO-ICT.

Run Doxygen in the root to create the documentation.

To use hwlib from within bmptk:
   - define $HWLIB to be the path where you placed your copy of hwlib
   - include $(HWLIB)/Makefile.include in your makefile
   - include "hwlib.hpp" in your code
   
To use hwlib without bmptk:
   - add the hwlib/include to your search
   - (if you wantto edit hwlib files) add the hwlib files to your dependencies
   - add hwlib.cpp to your sources
   - include the appropriate top-level target file in your code,
      for instance hwlib-due.hpp
      
      
      