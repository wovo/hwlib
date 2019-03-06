// ==========================================================================
//
// File      : hwlib-doxygen-rationale.hpp
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
/// Instead it aims to make close-to-the-hardware programming,
/// understandable for those who understand classic (virtual-based)
/// C++ O0.
///
