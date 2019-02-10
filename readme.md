Hwlib is a C++ classic-OO-style library for close-to-the-hardware 
programming. It is used in a number of Computer Science courses 
at the Hogeschool Utrecht, HBO-ICT.

The typical blink-a-led application code using hwlib 
(assuming the target board has a default led) is:

```C++
#include "hwlib.hpp"

int main( void ){   
   auto led = hwlib::target::led;
   hwlib::blink( led );
}
```

See index.html (which redirects to html/index.html) for the documentation.

-----------------------------------------------------------------------------      
      
(c) Wouter van Ooijen (wouter@voti.nl) 2017

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at 
http://www.boost.org/LICENSE_1_0.txt)     

note: include/hwlib-arduino-due-system-sam3xa.inc is (c) atmel, 
under asf license.

-----------------------------------------------------------------------------  

bmptk build (makefile) structure

The following is (only) relevant if you want to work on the library 
itself and use its bmptk-bases makefile structure. 

To build and run a single project, run *bmptk-make run* in its directory.

Each project is in a separate directory and has its own bmptk makefile
that builds that project. 
This project makefile specifies project-specific properties, 
sets the symbol RELATIVE, and includes the makefile.link 
in the next higher directory, which can specify things
that are common to the projects in its subdirectories, 
updates RELATIVE to RELATIVE\.., and includes the
makefile.link in the next higher directory, up to the one in the main
directory of the library, which includes a makefile.custom (if present)
or else the makefile.local. It also adds some global specifications,
and finally includes the bmptk makefile.inc.

To build everything in a directory and below, run *bmptk-make build*.

Each directory that contains subdirectories that contain projects has 
a makefile that responds to this command by re-issuing it in all its
subdirectories. To do this, it also uses bmptk, so it uses
'bmptk-make -f makefile.link <target>' to include bmptk.inc, using the
above mechanism.

De makefile.inc is included by the bmptk makefile.inc to update the bmptk
SEARCH, HEADERS and SOURCES with the itmes from the hwlib library.

Each directory that contains project sub-directories has a file 
update_codelite_workspace.bat. When executed, it creates a CodeLite 
workspace that contains the projects.

To use the library with bmptk:
   - define HWLIB to be the path where you placed your copy of hwlib
   - include $(HWLIB)/Makefile.include in your makefile
   - include "hwlib.hpp" in your code
   
To use the library without bmptk:
   - add the hwlib/library directory to your search
   - (if you want to edit hwlib files) 
       add the hwlib files to your dependencies
   - define the appropriate target as -DHWLIB_TARGET_* (see hwlib.hpp)	   
       in your compiler parameters
   - add hwlib.cpp to your sources
   - include hwlib.hpp in your application source(s)      

-----------------------------------------------------------------------------

To do list

2019 refurbishment
- build structure => doxygen
- no separate includes in the hwlib include files
- remove buffering => examples & style!
- what does a target provide => split mega328 from uno
- can ONCE imply NO_DOXYGEN?
- hwlib equal -> can't be included earlier??
- less root directories & files please
- demo/due/chris oled spi
- uno common files doesn't work => depends on bmptk!! (doesn't work for arduino?)
- add external dependencies notes in doxygen (bmptk, linker, atmega lib stuff)
- 'nowait' I2C
- more efficient OLED - dirty bits
- db103 uart - needs wait_us_busy => look at wait services
- 5510 retry
- hc595 must flush
- pin_oc_invert has no p0 etc?
- mcp23008, 23016
- HD44780
- die grafische LCD
- matrix keypad

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
  - more pin/port cross type decorators

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
      