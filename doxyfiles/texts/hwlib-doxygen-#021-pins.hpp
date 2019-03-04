// ==========================================================================
//
// File      : hwlib-doxygen-pins.hpp
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
/// <BR>
///
/// =========================================================================
///
/// \section pin-types types
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
/// Each target provides (concrete) classes for each of the four types of pins.
///
/// \snippet "arduino-uno\gpio-types\main.cpp" [Doxygen pin example]
///
/// <BR>
///
/// =========================================================================
///
/// \section pin-construction construction
///
/// Micro-controller hardware groups their GPIO pins into ports.
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
/// <BR>
///
/// =========================================================================
///
/// \section pin-operation operations
///
/// The next tables shows the operations that are available for
/// each type of pin.
///
/// pin type | reading | writing | direction control |
/// -------- | ------- | ------- | ----------------- |
/// \ref hwlib::pin_in     "in"     |  \ref hwlib::pin_in::refresh "refresh()", \ref hwlib::pin_in::read "read()" | | |
/// \ref hwlib::pin_out    "out"    |  | \ref hwlib::pin_out::write "write()", \ref hwlib::pin_out::write "write()" | |
/// \ref hwlib::pin_in_out "in_out" | \ref hwlib::pin_in::refresh "refresh()", \ref hwlib::pin_in::read "read()" | \ref hwlib::pin_out::write "write()", \ref hwlib::pin_out::write "write()" | \ref hwlib::pin_in_out::direction_set_input "direction_set_input()", \ref hwlib::pin_in_out::direction_set_output "direction_set_output()", \ref hwlib::pin_in_out::direction_flush "direction_flush()" |
/// \ref hwlib::pin_oc     "oc"     | \ref hwlib::pin_in::refresh "refresh()", \ref hwlib::pin_in::read "read()" | \ref hwlib::pin_out::write "write()", \ref hwlib::pin_out::write "write()" | |
/// 
/// A read() returns a bool, a write() accepts a bool.
/// The other calls take no parameters and return void.
///
/// \snippet "db103\pin-bool\main.cpp" [Doxygen read example]
/// \snippet "db103\pin-bool\main.cpp" [Doxygen write example]
///
/// For an \ref hwlib::pin_in_out "in_out" pin the direction must be
/// set to input before a read() is done, and to output before
/// a write() is done.
///
/// \snippet "db103\pin-direction\main.cpp" [Doxygen direction example]
///
/// As shown in the examples, a read() should be preceded by a refresh(), 
/// a write should be followed by a %flush(), 
/// and a direction change should be followed
/// by a \ref hwlib::pin_in_out::direction_flush "direction_flush()", 
/// as explained in the page on \ref buffering "buffering".
///
/// <BR>
///
/// =========================================================================
///
/// \section pin-direct direct
///
/// Pin operations (read, write, direction_set_input, direction_set_output)
/// are (potentially) \ref buffering "buffered".
///
/// The direct() creator function can be used to create a pin that
/// has read(), write() and direction_set_*() operations with direct effect.
///
/// \snippet "db103\pin-direct\main.cpp" [Doxygen direct example]
///
/// <BR>
///
/// =========================================================================
///
/// \section pin-invert invert
///
/// The \ref hwlib::invert invert() function constructs a new pin 
/// from an existing one.
/// When a value is written to this new pin, the inverse of this
/// value is written to the old pin.
/// Likewise, when a value is read from the new pin, the value 
/// is the inverse of the value read from the old pin.
/// The new pin is of the same type (in, out, in_out, oc) 
/// as the existing one from which it was created.
///
/// \snippet "db103\pin-invert\main.cpp" [Doxygen invert example]
///
/// <BR>
///
/// =========================================================================
///
/// \section pin-conversion conversion
/// 
/// Conversion functions are available that create a pin of one type
/// from one of another type. 
/// Of course, not all such conversions are possible.
///
/// function                | accepted pin types
/// ----------------------- | -----------------------
/// pin_in_from( pin )      | in, in_out, oc
/// pin_out_from( pin )     | out, in_out, oc
/// pin_in_out_from( pin )  | in_out, oc
/// pin_oc_from( pin )      | in_out, oc
///
/// <BR>
///
/// \snippet "db103\pin-conversion\main.cpp" [Doxygen conversion example]
/// <BR>
///
/// =========================================================================
///
/// \section pin-all All
/// 
/// The overloaded all() function creates a single out pin from up
/// to 16 out pins. Writing a value to the single pin writes the value 
/// to all pin that it was constructed from, and similarly flushing the 
/// single pin flushes all pins it was constructed from.
///
/// <BR>
///
/// =========================================================================
///
/// \section pin-pullups Pull-ups & pull-downs
/// 
/// Some pins have pull-up and/or pull-down resistors that can be 
/// enabled and disabled under software control. If so, such
/// pins provide these functions:
/// - pullup_disable(), pullup_enable() (when pull-ups are available)
/// - pulldown_disable(), pulldown_enable() (when pull-downs are available)
///
/// Unlike other pin functionality, these functions operate directly 
/// (they have no corresponding %flush() functions).
///
/// <BR>
///
