// ==========================================================================
//
// File      : hwlib-doxygen.hpp
// Part of   : hwlib library for V1OOPC and V1IPAS
// Copyright : wouter@voti.nl 2016
//
// input for doxygen that is never included in a compilation
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================
/// @file

// This file contains doxygen stuff that doesn't belong in any specific
// header file. This file is not included by hwlib-all.hpp.

/// hwlib library
//
/// This namespace contains the target-independent parts of the hwlib library.
namespace hwlib {}

/// \mainpage
///
/// \image html toolset.png
///
/// \author Wouter van Ooijen (wouter@voti.nl)
/// \version 1.0 (last modified 2015-01-21)
/// \copyright boost license (some files public domain)
///
/// Hwlib is a C++ OO library for close-to-the-hardware programming.
/// It is used in the V1IPAS-TI course at the Hogeschool Utrecht.
/// The library is meant to be used within bmptk.
/// The language is the 2011 C++ standard. 
/// (But for compiling for the Arduino Uno the 2011 standard is used 
/// because gcc-avr doesn't yet support the 2014 standard.)
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
///    - Raspberry Pi (under Linux, using direct pin access; 
///      must run as root).
///
/// The library is used by including either the header for the target
/// (hwlib-due.hpp, hwlib-db103.hpp, hwlib-uno.hpp or hwlib-pi.hpp),
/// or (preferrably) by including hwlib.hpp, which will include the
/// correct target header based on the macro that is set by bmptk 
/// (BMPTK_TARGET_ARDUIN_DUE etc.) in the compiler command line.
///
/// \snippet "due\blink\main.cpp" [Doxygen blink example]
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
/// Hence plain int types are (almost) never used. 
/// For single 8-bit variables hwlib::fast_byte is used, which translates
/// to the fastest unsigned integer type that can hold 8 bits (uint_fast8_t):
/// 8 bit on 8-bit targets, 16 bits on 16-bit targets, etc.
/// For array variables and parameters hwlib::byte (uint8_t)
/// will often be a better choice.
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
///    - dynamic memory (new, delete)
///    - exception handling (throw, try ... catch)
///    - templates (except static_cast<>)
///    - RTTI, dynamic_cast
/// 
///
// ==========================================================================

/// \page todo  To do list
///
/// Known issue
///
/// Nice to haves
///   - character console on graphics
///   - rectangle (filled), circle (filled), image (external converter)
///   - graphics 2"4 LCD
///   - targets: Pi, Liliypad85
///   - ADS1115
///   - LCD/button shield
///   - due adc
///   - use and provide ranges (instead of x, y for loops)
///   - time-based wait (or at least a now() function)
///   - listener pattern 'dummy' pins?
///   - pcf8591
///   - block-write for graphics
///   - faster I2C by exposing the elements, use in oled?
///
/// Quality & consistency issues 
///   - main() not (void)
///   - file-local objects are not documented? (check ostream)
///   - author & change date everywhere?
///   - db103 align pin classes
///   - more examples (graphics, ...)
///   - lcd5510 should use SPI??
///   - i2c example of address-only write
///   - directories opschonen
///   - make full build, clean
///   - test for input, output, oc, analog pins of a chip
///   - rewrite text for uno (due?) IO pins
///   - foto for setups, eg. hc595 (pins!!)
///   - run does not recompile on changed main.cpp??
///   - test that all headers can compile *individually*
///   - rename lcd to something that includes oled
///   - cleanup oled => ssd1306, provide init code, expose command interface
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
///   - one_pin trick => defines.hpp
///   - use an abstraction instead of copied code in the extenders one_pin => pin_out_through_buffer





