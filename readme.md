Hwlib is a C++ classic-OO-style library for close-to-the-hardware 
programming. It is used in a number of Computer Sience courses 
at the Hogeschool Utrecht, HBO-ICT.

The typical blink-al-led application code using hwlib is:

```C++
#include "hwlib.hpp"

int main( void ){   
   auto led = hwlib::target::pin_out( 1, 5 );
   hwlib::blink( led );
}
```

Run 'make doxygen' (or doxygen doxyfiles/Doxyfile )
in the root to create the documentation.

-----------------------------------------------------------------------------  

To use the library from with bmptk:
   - define $HWLIB to be the path where you placed your copy of hwlib
   - include $(HWLIB)/Makefile.include in your makefile
   - include "hwlib.hpp" in your code
   
To use the library without bmptk:
   - add the hwlib/include to your search
   - (if you want to edit hwlib files) 
       add the hwlib files to your dependencies
   - add hwlib.cpp to your sources
   - include the appropriate top-level target file in your code,
       for instance hwlib-arduino-due.hpp
      
-----------------------------------------------------------------------------      

The following is (only) relevant if you want to work on the library 
itself and use its makefile structure. It is assumed that you use bmptk.     
      
Each project directory has a makefile that builds that project. 
It sets the symbol RELATIVE, and includes the makefile.link 
of its parent directory, which updates RELATIVE to RELATIVE\.. and 
includes the makefile.link in the next-higher parent directory, etc,
up to the root of the library, where the makefile.link defers to the
makefile.inc of bmptk to do the real work.

Most non-project directories contain a makefile that (recursively)
builds its subdirectories. To do this, it also uses bmptk, so it uses
'bmptk-make -f makefile.link <target>' to include bmptk.inc, using the
above mechanism.

In the root of the library the file makefile.find_local 
provides the location of 
the external dependencies (bmptk, Catch). By default it does this by 
including makefile.local, but when a bmptk.custom is present 
one level higher, or in that directory (in that order) that one 
is used instead. This makes it possible to customize the locations 
of the external dependencies without changing an existing file.

Each directory that contains project sub-directories has a file 
update_codelite_workspace.bat. When executed, it creates a CodeLite 
workspace that contains the projects.

-----------------------------------------------------------------------------
      
(c) Wouter van Ooijen (wouter@voti.nl) 2017

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at 
http://www.boost.org/LICENSE_1_0.txt)     

note: include/hwlib-arduino-due-system-sam3xa.inc is (c) atmel, 
under asf license.      

-----------------------------------------------------------------------------

To do list

Known problems:
  - a busy period > 0.7s without a now_us() call makes the Due miss timer overflows
    now a call in i2c avoid this, => this is not a real solution

Quality & consistency:
  - file-local objects are not documented? (check ostream)
  - db103 align pin classes
  - more examples (graphics, ...)
  - lcd5510 should use SPI!
  - i2c example of address-only write
  - test for input, output, oc, analog pins of a chip
  - rewrite text for uno (due?) IO pins
  - rename lcd to something that includes oled
  - cleanup oled => ssd1306, provide init code, expose command interface
  - pin decorators - did they exist at one point??
  - also check line length (in tab checker)
  - there is no on-line manual :(
  - columns,lines or other way round, or use position? (ostream, hd44780)

Nice to haves:
  - rectangle (filled), circle (filled), image (external converter)
  - graphics 2"4 LCD
  - targets: Pi, Liliypad85, ESP8266, ST32, MCP430
  - LCD/button shield
  - use and provide ranges (instead of x, y for loops)
  - add an I2C temp sensor for Leo of iets anders
  - I2C read, pcf8574a, demo: copy 1 to 2
  - use an abstraction instead of copied code in the extenders one_pin => pin_out_through_buffer
  - uno A/D, test with LCD shield
  - i2c hd44780 LCD
  - more pin/portr cross type decorators

Misc:
  - meer examples lpc1114 - need the hardware!
  - db103 uart?
  - uart gebruikt??
  - rtos??
  - images licences!!
  - check all documentation
  - meer tests voor hwlib::string
  - bmptk...
  - bmptk blink examples
  - linux
  - esp8266 - eerste in bmptk
  - switch due to full speed??
  - geweer hardware aanpassen (private repository??)
  - oled spi, hw spi
  - graphics buffering via buffering::buffered -> ook in text
  - delays moeten 16-bit parameter Zijn ivm AVR en MSP430?
  - uno hello baudrate klopt niet

     lpc due uno
empty 1224 120 176
blink 1268! 420 680
- why is blink uno large??

make tool to extract this kind of info?

bmptk => use usbasp2, has no serial (include uno bootloader?)
but possible with separate serial!
      