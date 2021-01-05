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


/// \page spi-bus spi bus   
/// 
/// The SPI (Serial Peripheral Interface) protocol 
/// is based on shift registers. 
/// The master (in most cases the micro-controller) generates
/// clock pulses (SCLK), and on each pulse one bit of data is transferred
/// from the shift register inside the master to the shift register inside
/// the slave, AND one bit is transferred in the other direction.
/// After N clock pulses, all N data bits in the master and the slave 
/// are exchanged.
/// The MOSI line transfers data from master to slave (Master Out Slave In),
/// the MISO (Master In Slave Out) line transfers data 
/// from the slave to the master.
///
/// \image html spi-master-slave.png
///
/// The SS (Slave Select) line is used to signal the start and end of a 
/// SPOI transfer. In most cases, the select line is active low.
///
/// \image html spi-select-1.png
///
/// A SPI bus can have multiple slaves. 
/// All slaves (and the master) share the MOSI, MISO and SLCK lines. 
/// Each slave has a separate SS line, that is used to activate
/// a single slave for a transfer.
///
/// \image html spi-select-2.png
///
/// The SPI bus is a de-facto standard: there is no official document
/// that defines it, but various manufacturers agree on how it should work
/// and (more or less!) implement it the same. But there are differences
/// that might give problems: 
///    - the polarity (active low or active high) of the SS line
///    - the initial level of the clock 
///    - the polarity of the clock 
///       (the clock edge on which the master and slave transfer data)
///    - the (maximum) clock frequency
///
/// As always, consult the datasheet of the chip for the details.
/// 
/// references:
/// - <a href="https://embeddedmicro.com/tutorials/mojo/serial-peripheral-interface-spi">
///    SPI explanation</A> (Embedded Micro Forum)
/// - <a href="https://en.wikipedia.org/wiki/Serial_Peripheral_Interface_Bus">
///    Serial Peripheral Bus</A> (wikipedia)
///  