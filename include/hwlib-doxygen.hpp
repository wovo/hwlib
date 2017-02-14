// ==========================================================================
//
// File      : hwlib-doxygen.hpp
// Part of   : C++ hwlib library for close-to-the-hardware OO programming
// Copyright : wouter@voti.nl 2017
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

// this file contains Doxygen lines (of course, that is its only purpose)
/// @file

// This file contains doxygen stuff that doesn't belong in any specific
// header file. Hence this file is not included by hwlib-all.hpp.

/// hwlib library
//
/// This namespace contains the target-independent parts of the hwlib library.
namespace hwlib {}

/// \mainpage
///
/// \image html toolset.png
///
/// \author Wouter van Ooijen (wouter@voti.nl)
/// \version 1.1 (last modified 2017-02-03)
/// \copyright boost license (but see below for exceptions)
///
/// Hwlib is a C++ OO library for close-to-the-hardware programming.
/// It is used in an number of courses at the Hogeschool Utrecht.
/// The library is meant to be used with bmptk.
/// The language use is the 2014 C++ standard. 
///
/// Hardware pins and ports, and other hardware-related interfaces like
/// A/D converters and character streams are represented by abstract
/// interfaces (classes with virtual functions).
/// 
/// Implementations of the hardware abstractions (like pins and delays)
/// are provided for the supported targets:
///    - Arduino Due (ATSAM3X8E chip)
///    - DB103 (LPC1114 chip)
///    - Arduino Uno (ATMEGA328P chip)
///
/// The library is used by including either the header for the target
/// (hwlib-arduino-due.hpp, hwlib-db103.hpp, hwlib-arduino-uno.hpp),
/// or (preferrably) by including hwlib.hpp, which will include the
/// correct target header based on the macro that is set by bmptk 
/// (BMPTK_TARGET_ARDUIN_DUE etc.) on the compiler command line.
///
/// \snippet "demo\arduino-due\blink\main.cpp" [Doxygen blink example]
/// 
/// The following naming convention is used:
///    - functions that are called set() and get() (or have set or get as
///      part of their name) deal with entities or effects that are 
///      memoryless (behave like a variable): calling set() twice with
///      the same value has the same effect as calling it once; 
///      calling get() twice should (when the context has not changed)
///      return the same value. 
///      Examples are 
///         - digital and analog I/O pins
///         - pixels in a graphic window
///         - the value in a pool (synchronization mechanism)
///    - functions that are called read() and write() (or have those terms
///      as part of their names) deal with entities or effects that have 
///      memory or an otherwise lasting effect. Examples are:
///         - character (and other) streams  
///         - channels (queue-like synchronization mechanism)
///
/// Hwlib must be effective on micro-controllers with different word sizes.
/// Hence plain int types are (almost) never used, 
/// instead the likes of uint_fast8_t are used.
///
/// Hwlib is meant to be usable and understandable by users with (only) 
/// a basic knowledge of C++, specifically:
///    - basic C: types, expressions, control, functions, pointers,
///      declaration versus definition, use of header files
///    - char, short, int, long versus uintN_t, uint_fastN_t
///    - struct, class, public, private, protected, static
///    - constructors (incl. delegation), destructors
///    - inheritance, virtual, abstract interface, override, final
///    - const, constexpr
///    - static_cast<>
///    - references, object lifetime (danger of dangling references)
///    - for(:) used with arrays
///    - the effect of __attribute__((weak)) 
///    - use of << and >> for output and input
///
/// The following design patterns are used (extensively) within hwlib:
///    - adapter, decorator, composite, proxy 
///      (grouped because these are variations of the same basic idea)
///    - non-virtual interface (NVI)
///    - dependency injection
///    - proxy
///
/// The following C++ features are deliberately *not* used, 
/// because they are eiter too advanced, 
/// or not appropriate for use on small micro-controllers:
///    - dynamic memory (new, delete, STL containers)
///    - exception handling (throw, try ... catch)
///    - templates (except static_cast<>, and string<N>)
///    - RTTI, dynamic_cast
///
/// All hwlib files are provided under the boost license, except:
///    - some pictures used in the documentation are under a 
///      Creative Commons license that allows unaltered reproduction
///    - an arduino-due include file is from Atmel (Microchip) under asl
///
/// These exceptions have no impact on the status of an application
/// that includes hwlib in its build.
///
// ==========================================================================
//
/// \page todo  To do list
///
/// Known issue
///   - currently none
///
/// Nice to haves
///   - rectangle (filled), circle (filled), image (external converter)
///   - graphics 2"4 LCD
///   - targets: Pi, Liliypad85, ESP8266, ST32, MCP430
///   - LCD/button shield
///   - use and provide ranges (instead of x, y for loops)
///
/// Quality & consistency issues 
///   - file-local objects are not documented? (check ostream)
///   - db103 align pin classes
///   - more examples (graphics, ...)
///   - lcd5510 should use SPI??
///   - i2c example of address-only write
///   - test for input, output, oc, analog pins of a chip
///   - rewrite text for uno (due?) IO pins
///   - rename lcd to something that includes oled
///   - cleanup oled => ssd1306, provide init code, expose command interface
///   - pin decorators - did they exist at one point??
///   - also check line length (in tab checker)
///   - there is no on-line manual :(
///
/// Must test
///   - HD44780 other sizes
///
/// Doxygen issues
///   - alphabetical index??
///   - prevent ///   - in file listing?
///   - ostream::showos 'functions' have no 'More..." ??
///   - ostream members are listed as related??
///
/// The list of issues, plans, bugs, etc:
///   - add an I2C temp sensor for Leo of iets anders
///   - I2C read, pcf8574a, demo: copy 1 to 2
///   - use an abstraction instead of copied code in the extenders one_pin => pin_out_through_buffer
///
///   - meer examples lpc1114 - need hardware
///   - check uno 
///   - db103 uart?
///   - uart gebruikt??
///   - rtos??
///   - images licences!!
///   - check all documentation
///   - meer tests voor hwlib::string
///   - bmptk...
///   - can that subdirs thing be put into bmptk?
///   - bmptk blink examples
///   - linux
///   - esp8266 - eerste in bmptk
///   - switch due to full speed??
///   - geweer hardware aanpassen (private repository??)
///
// ==========================================================================




