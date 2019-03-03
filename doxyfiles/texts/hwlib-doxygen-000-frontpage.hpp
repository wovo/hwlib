// ==========================================================================
//
// File      : hwlib-doxygen-frontpage.hpp
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


/// \brief
/// hwlib library (traget-independent parts)
/// 
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
