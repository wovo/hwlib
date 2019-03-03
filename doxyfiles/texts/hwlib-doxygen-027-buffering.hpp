// ==========================================================================
//
// File      : hwlib-doxygen-buffering.hpp
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
/// Operations on \ref pins "pins", \ref ports "ports", 
/// AD-inputs, DA-outputs, character streams,
/// graphic windows, etc. are by default (potentially) buffered.
/// To ensure direct effects, all reads must be preceded by a refresh call, 
/// and all writes must be succeeded by a flush call
/// 
/// \snippet "db103\pin-copy\main.cpp" [Doxygen flush example]
///
/// The direct() decorator automates this, making the refresh() 
/// and flush() calls unnecessary. 
/// 
/// \snippet "db103\pin-copy\main.cpp" [Doxygen direct example]
///
/// Using buffered operations can produce a significant speedup
/// because the actual output operation is postponed, and can 
/// handle all pending changes in one go.
///
/// The pcf8574a is an i2c I/O extender that provided 8 open-collector
/// pins. The hwlib::pcf8574a class is buffered: when a value is written
/// to a pin, it is actually written to a buffer in RAM. A flush call
/// writes this buffer to the chip, but only when it has beenm written to
/// since the last flush.
/// When a flush call is done after each write, 
/// each flush writes to the chip. 
/// On a 12 MHz LPC1114, four writes and flushes take 3.8 ms.
///
/// \snippet "db103\pcf8574a-timing\main.cpp" [Doxygen flush example]
///
/// When the flush() calls are done after the four write() calls, 
/// it all takes only 1.0 ms. 
/// Most of this is spent in the first flush() call, the others
/// have nothing left to do.
///
/// \snippet "db103\pcf8574a-timing\main.cpp" [Doxygen buffered example]
///