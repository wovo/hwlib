// ==========================================================================
//
// File      : hwlib-doxygen-ports.hpp
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


/// \page ports Ports
///
/// A port is a collection of up to 8 \ref pins "pins" 
/// of the same type (in, out, in_out or oc)
/// that are used (read, written, direction changed) together.
///
/// <BR>
///
/// =========================================================================
///
/// \section port-types types
///
/// Similar to \ref pins "pins", there are four (abstract) types of ports:
///
/// - a \ref hwlib::port_in can only be used for input (read)
/// - a \ref hwlib::port_out can only be used for output (write)
/// - a \ref hwlib::port_in_out can be used for input or output, 
///   but it must be configured for the appropriate direction 
///   (input or output) before it is used in either way.
/// - a \ref hwlib::port_oc (open collector) can be used for input or output 
///   (without configuring it for a direction), but each pin in the port 
///   must have been written high before it can be meaningfully read.
///
/// <BR>
///
/// =========================================================================
///
/// \section port-from creating a port from pins
///
/// A port can be constructed from a list of (up to 8) pins 
/// of the same type by the hwlib::port_from() constructor functions.
///
/// \snippet "db103\port-from\main.cpp" [Doxygen port-from example]
///
/// <BR>
///
/// =========================================================================
///
/// \section port-operation operations
///
/// The next tables shows the operations that are available for
/// each type of port.
///
/// port type | reading | writing | direction control |
/// -------- | ------- | ------- | ----------------- |
/// \ref hwlib::port_in     "in"     |  \ref hwlib::port_in::refresh "refresh()", \ref hwlib::port_in::read "read()" | | |
/// \ref hwlib::port_out    "out"    |  | \ref hwlib::port_out::write "write()", \ref hwlib::port_out::write "write()" | |
/// \ref hwlib::port_in_out "in_out" | \ref hwlib::port_in::refresh "refresh()", \ref hwlib::port_in::read "read()" | \ref hwlib::port_out::write "write()", \ref hwlib::port_out::write "write()" | \ref hwlib::port_in_out::direction_set_input "direction_set_input()", \ref hwlib::port_in_out::direction_set_output "direction_set_output()", \ref hwlib::port_in_out::direction_flush "direction_flush()" |
/// \ref hwlib::port_oc     "oc"     | \ref hwlib::port_in::refresh "refresh()", \ref hwlib::port_in::read "read()" | \ref hwlib::port_out::write "write()", \ref hwlib::port_out::write "write()" | |
/// 
/// A read() returns a uint_fast8_t, a write() accepts a uint_fast8_t.
/// The other calls take no parameters and return void.
///
/// When a port is read from, the lowest bit of the value read was read from
/// the first pin supplied to the port constructor, the second-lowest
/// bit from the second pin, etc. Likewise, when a port is written to,
/// the lowest bit of the value is written to the first pin supplied to
/// the constructor, etc.
///
/// \snippet "db103\port-uint\main.cpp" [Doxygen read example]
/// \snippet "db103\port-uint\main.cpp" [Doxygen write example]
///
/// For an \ref hwlib::port_in_out "in_out" port the direction must be
/// set to input before a read() is done, and to output before
/// a write() is done.
///
/// \snippet "db103\port-direction\main.cpp" [Doxygen direction example]
///
/// As shown in the examples, a read() should be preceded by a refresh(), 
/// a write should be followed by a %flush(), 
/// and a direction change should be followed
/// by a \ref hwlib::port_in_out::direction_flush "direction_flush()", 
/// as explained in the page on \ref buffering "buffering".
///
/// <BR>
///
/// =========================================================================
///
/// \section port-direct direct
///
/// Port operations (read, write, direction_set_input, direction_set_output)
/// are (potentially) \ref buffering "buffered".
///
/// The direct() creator function can be used to create a port that
/// has read(), write() and direction_set_*() operations with direct effect.
///
/// \snippet "db103\port-direct\main.cpp" [Doxygen direct example]
///
/// <BR>
///
/// =========================================================================
///
/// \section port-invert invert
///
/// The \ref hwlib::invert invert() function constructs a new port 
/// from an existing one.
/// When a value is written to this new port, the bitwise inverse of this
/// value is written to the old pin.
/// Likewise, when a value is read from the new port, the value 
/// is the bitwise inverse of the value read from the old port.
/// The new port is of the same type (in, out, in_out, oc) 
/// as the existing one from which it was created.
///
/// \snippet "db103\port-invert\main.cpp" [Doxygen invert example]
///
/// <BR>
///
/// =========================================================================
///
/// \section port-conversion conversion
/// 
/// Conversion functions are available that create a port of one type
/// from one of another type. 
/// Of course, not all such conversions are possible.
///
/// function                  | accepted port types
/// ------------------------- | -----------------------
/// port_in_from( port )      | in, in_out, oc
/// port_out_from( port )     | out, in_out, oc
/// port_in_out_from( port )  | in_out, oc
/// port_oc_from( port )      | oc
///
/// Unlike for the pin conversions, it is not possible to create a port_oc
/// from a port_in_out, because a port_in_out doesn't allow for individual
/// control of the pin directions.
///
/// <BR>
///
/// \snippet "db103\port-conversion\main.cpp" [Doxygen conversion example]
///
/// <BR>
///
/// =========================================================================
///
/// \section port-all All
/// 
/// The overloaded all() function creates a single out pin from an out 
/// port. Writing a value to the single pin writes the value 
/// to all pins of the port. 
/// Flushing the single pin flushes the port.
///
/// <BR>
///

