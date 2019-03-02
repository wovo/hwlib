// ==========================================================================
//
// File      : hwlib-doxygen.hpp
// Part of   : C++ hwlib library for close-to-the-hardware OO programming
// Copyright : wouter@voti.nl 2017-2019
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
// (That would be a waste of compile time.)

/// \brief
/// hwlib library
/// \details
/// This namespace contains the target-independent 
/// parts of the hwlib library.
/// (Except for some macro's, which can't be inside a namespace.)
namespace hwlib {}


/// \mainpage
///
/// \image html toolset.png
///
/// \author Wouter van Ooijen (wouter@voti.nl)
/// \version 1.1 (last modified 2019-02-09)
/// \copyright boost license (but see below for exceptions)
///
/// -------------------------------------------------------------------------
/// 
/// Hwlib is a C++ OO library for close-to-the-hardware programming.
/// It is used in an number of courses at the Hogeschool Utrecht.
/// The library is meant to be used with bmptk.
/// The language used is currently the 2014 C++ standard. 
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
///    - Arduino Uno (ATMEGA328P chip)
///    - Arduino Due (ATSAM3X8E chip)
///    - DB103 (LPC1114 chip)
///    - blue-pill (stm32f103c8 chip)
///
/// The easy way is to use the library with bmptk:
/// Include hwlib.hpp, which will include the
/// correct target header based on the HWLIB_TARGET_* macro that is set 
/// in the bmptk makefile. Bmptk passes this setting to the hwlib.hpp file 
/// via a macro definition on the compiler command line.
///
/// \snippet "db103\blink\main.cpp" [Doxygen blink example]
/// \snippet "db103\blink\makefile" [Doxygen makefile example]
/// \snippet "db103\makefile.link"  [Doxygen makefile example]
/// 


// ==========================================================================
//
/// \page buffering Buffering
///
/// For efficiency, some operations are (potentially) buffered. 
/// A direct operation will have an immediate external effect 
/// (for output operations) or work on a fresh sample of the external 
/// conditions (for input operations).
/// A buffered operation might have its effect delayed up to the
/// next flush operation (output), or work on input that is as old
/// as the most recent refresh() operation.
///
/// Operations on pins, ports, AD-inputs, DA-outputs, character streams,
/// graphic windows, etc. are by default (potentially) buffered.
/// To ensure direct effects, all reads must be preceded by a refresh call, 
/// and all writes must be succeeded by a flush call
/// 
/// \snippet "db103\pin-copy\main.cpp" [Doxygen buffered example]
///
/// The direct() decorator automates this, making the refresh() and flus()
/// calls unnecessary. 
/// 
/// \snippet "db103\pin-copy\main.cpp" [Doxygen direct example]
///
/// Using unbuffered operations can produce a significant speedup
/// because the actual output operation is postponed, and can 
/// handle all pending changes in one go.
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
/// 1024 data bytes. Hence a flush takes roughly the time it takes to
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
///    - as library for use in homework assignments
///    - as a style example for hardware OO interfacing
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
///    - std::array<>
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
///    - creator functions
///
/// The following C++ features are deliberately *not* used, 
/// because they are eiter too advanced, 
/// or not appropriate for use on small micro-controllers:
///    - dynamic memory (new, delete, STL containers)
///    - exception handling (throw, try ... catch)
///    - templates (except static_cast<>, and string<N>) 
///      (except for hwlib::string)
///    - RTTI, dynamic_cast
///
/// Hwlib must be effective on micro-controllers with different word sizes.
/// Hence plain int types are (almost) never used, 
/// instead the likes of uint_fast8_t are used.
///
/// Hwlib is *not* meant to be the most effective (fast, compact) library
/// for close-to-the-hardware programming, because that requires templates
/// and concepts, which are not appropriate for 
/// (relatively) new C++ programmers.
/// Hwcpp library is my (ongoing) attempt to fill that niche.
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
/// \image html mini-pro-pinout.png
/// Creative Commons, details in the image itself
/// 
///--------------------------------------------------------------------------
///
/// \image html nano-pinout.png
/// Creative Commons, details in the image itself
/// 
///--------------------------------------------------------------------------
///
/// A nice source for IC pinouts: 
/// https://commons.wikimedia.org/wiki/Category:IC_pinout_diagrams


// ==========================================================================
//
