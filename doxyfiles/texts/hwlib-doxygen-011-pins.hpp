// ==========================================================================
//
// File      : hwlib-doxygen-pins-and-ports.hpp
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


/// \page pins Pins
///
/// Micro-controllers have GPIO (General Purpose Input / Ouput) pins
/// that can be used by the micro-controller application software 
/// to interface with hardware external to the micro-controller 
/// in a very basic way.
///
/// A GPIO pin can - under software control - be configure to be either
/// an input or an output. When configured as input, its level
/// (high or low) can be read by the software. 
/// When configured as output, the software can write a level to the pin.
///
/// In hwlib, four (abstract) types of pin objects are defined:
///
/// - a \ref hwlib::pin_in can only be used for input (read)
/// - a \ref hwlib::pin_out can only be used for output (write)
/// - a \ref hwlib::pin_in_out can be used for input or output, 
///   but it must be configured for the appropriate direction 
///   (input or output) before it is used in either way.
/// - a \ref hwlib::pin_oc (open collector) can be used for input or output 
///   (without configuring it for a direction), but a write(1) must 
///   be done before it can be meaningfully read.
///
/// Each target provides a classes for each of the four types of pins.
///
/// Micro-controller chips group their GPIO pins into ports.
/// A pin can be constructed by specifying the port 
/// and the pin number within the port.
///
/// \snippet "arduino-uno\gpio-by-port-pin\main.cpp" [Doxygen pin example]
/// 
/// Boards (like the Arduino Uno) often have names for their pins.
/// Those names are often totally unrelated to the port and pins
/// of the micro-controller on the board.
/// A pin can be constructed by specifying the board-specific
/// pin name (or pin function, like 'led' or 'scl').
///
/// \snippet "arduino-uno\gpio-by-name\main.cpp" [Doxygen pin example]
///
/// Pin operations (read, write, direction_set_input, direction_set_output)
/// are (potentially) buffering buffered.
/// 