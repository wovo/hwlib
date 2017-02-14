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
      
Each project directory has a makefile that builds that project. 
It sets the symbol RELATIVE, and includes the makefile.link 
of its parent directory, which updates RELATIVE to RELATIVE\.. and 
includes the makefile.link in the next-higher parent directory, etc,
up to the root of hwlib, where the makefile.link defers to the
makefile.inc of bmptk to do the real work.

Most non-project directories contain a makefile that (recursively)
builds its subdirectories. To do this, it also uses bmptk, so it uses
'bmptk-make -f makefile.link <target>' to include bmptk.inc, using the
above mechanism.

In the hwlib root the file makefile.find_local provides the location of the
external dependencies (bmptk, Catch). By default it does this by including
makefile.local, but when a bmptk.custom is present that one is used instead.
This makes it possible to customize the locations of the external dependencies
without changing an existing file.
      
(c) Wouter van Ooijen (wouter@voti.nl) 2017

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at 
http://www.boost.org/LICENSE_1_0.txt)     

note: include/hwlib-arduino-due-system-sam3xa.inc is (c) atmel, under asf license.      
      