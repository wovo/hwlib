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

/// \brief
/// hwlib library
/// \details
/// This namespace contains the target-independent 
/// parts of the hwlib library.
namespace hwlib {}


/// \mainpage
///
/// \image html toolset.png
///
/// \author Wouter van Ooijen (wouter@voti.nl)
/// \version 1.1 (last modified 2017-02-15)
/// \copyright boost license (but see below for exceptions)
///
/// -------------------------------------------------------------------------
/// 
/// Hwlib is a C++ OO library for close-to-the-hardware programming.
/// It is used in an number of courses at the Hogeschool Utrecht.
/// The library is meant to be used with bmptk.
/// The language used is the 2014 C++ standard. 
///
/// Hardware pins and ports, and other hardware-related interfaces like
/// A/D converters and character streams are represented by abstract
/// interfaces (classes with virtual functions).
///
/// -------------------------------------------------------------------------
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
/// \page use Use
///
/// Implementations of the hardware abstractions (like pins and delays)
/// are provided for the supported targets:
///    - Arduino Due (ATSAM3X8E chip)
///    - DB103 (LPC1114 chip)
///    - Arduino Uno (ATMEGA328P chip)
///
/// The easy way is to use the library with bmptk.
/// Include hwlib.hpp, which will include the
/// correct target header based on the TARGET that is set in the  
/// bmptk makefile. Bmptk passes this setting to the hwlib.hpp file 
/// via a macro definition on the compiler command line.
///
/// \snippet "demo\arduino-due\blink\main.cpp" [blink example]
/// \snippet "demo\arduino-due\makefile.link" [makefile example]
/// 
/// Another way to use the library is by directly including the header 
/// for the target (hwlib-arduino-due.hpp, ...), and using some other
/// build system.
///
/// \snippet "demo\arduino-due\blink-direct-include\main.cpp" [blink example]
/// 
/// 


// ==========================================================================
//
/// \page buffering Buffering
///
/// For efficiency, some operations are provided in two ways: direct 
/// and (potentially) buffered. A direct operation will have an
/// immediate external effect (for output operations) or work on a 
/// fresh sample of the external conditions (for input operations).
/// A buffered operation might have its effect delayed up to the
/// next flush operation (output), or work on input that is as old
/// as the most recent refresh() oparation.
/// 
/// The easy way is to always use the unbuffered operations.
/// Drawing a drawable is by default unbuffered.
/// 
/// \snippet "demo\arduino-due\oled-timing\main.cpp" [direct]
///
/// Using unbuffered operations can produce a significant speedup
/// because the actual output operation is postponed, and can 
/// handle all changes in one go.
///
/// \snippet "demo\arduino-due\oled-timing\main.cpp" [buffered]
///
/// For the OLED the difference can be very large. 
/// Writing one pixel requires up to three operations:
///    - optionally set X address (7-byte I2C transaction) 
///    - optionally set Y address (7-byte I2C transaction)
///    - write data byte (3-byte I2C transaction)
/// For a direct operation this is done for each and every pixel.
///
/// The buffered graphics operations write to the in-memory pixel buffer,
/// which is written out to the oled in one go by the flush operation.
/// This is done in one I2C transaction, with some small overhead and
/// 1024 data bytes. Hence a flush takes roughtly the time it takes to
/// write 60 pixels. For the SPI interface the single pixel write
/// overhead is a little bit smaller because a SPI transfer has no command
/// byte (hence each transfer takes 1 byte less).
///
/// Character output to a graphic window is always buffered. The
/// flush manipulator is required to write the pixels to the screen.
///
/// \snippet "demo\arduino-due\oled-hello\main.cpp" [flush]
///


// ==========================================================================
//
/// \page naming Naming conventions
///
/// The following naming conventions are used:
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


// ==========================================================================
//
/// \page rationale Rationale
///
/// Hwlib makes it possible to program micro-controllers in classic Object
/// Oriented style (using objects, inhertitance, virtuals, etc).
/// It provides abstract interfaces to the basic low-level things found
/// in a micro-controller like pins, ports and A/D interfaces, and 
/// implementations of these things for a few targets. 
/// 
/// Hwlib is used in a number of C++ courses
///    - as library for the examples
///    - as library for homework
///    - style example for hardware OO interfacing
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
/// Hwlib must be effective on micro-controllers with different word sizes.
/// Hence plain int types are (almost) never used, 
/// instead the likes of uint_fast8_t are used.
///
/// Hwlib is *not* meant to be the most effective (fast, compact) library
/// for close-to-the-hardware programming, because that requires concepts
/// (templates, and a lot of SFINAE) that are not appropriate for 
/// (relatively) new C++ programmers.
/// My hwcpp library is an (ongoing) attempt to fill that niche.d
///


// ==========================================================================
//
/// \page acknowledgements Acknowledgements
///
/// This documentation is provided under the same (boost) license
/// as the library, except for some of the pictures:
///
///--------------------------------------------------------------------------
///
/// \image html toolset.png
/// Creative Commons Attribution 3.0
///
///--------------------------------------------------------------------------
///
/// \image html uno-pinout.png
/// Creative Commons, details in the image itself
///
///--------------------------------------------------------------------------
///
/// \image html due-pinout.png
/// Creative Commons, details in the image itself
/// 
///--------------------------------------------------------------------------
///
/// \image html mini-micro-pinout.png
/// Creative Commons, details in the image itself
/// 
///--------------------------------------------------------------------------
///
/// \image html nano-pinout.png
/// Creative Commons, details in the image itself
/// 
///--------------------------------------------------------------------------
///
/// A source for IC pinouts: 
/// https://commons.wikimedia.org/wiki/Category:IC_pinout_diagrams


// ==========================================================================
//
