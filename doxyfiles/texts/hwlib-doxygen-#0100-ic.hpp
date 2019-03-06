// ==========================================================================
//
// File      : hwlib-doxygen-i2c.hpp
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

/// \page i2c i2c
///
/// \section i2c-hardware hardware
///
/// In its simplest form, an I2C bus has one master and a number of slaves
/// that are connected by two wires: SCL (clock) and SDA (data). 
/// Both lines are pulled up by pull-up resistor, and can (only) 
/// be pulled down by a connected chip (open-collector).
///
/// \image html i2c-bus.png
///
///
/// <BR>
///
/// =========================================================================
///
/// \section i2c-transactions transactions
///
/// An I2C transaction is either a read transaction or a write transaction.
/// In both cases, the transaction starts with the master transmitting a 
/// control byte, which contains the address of the slave chip, and one bit
/// that indicates whether it is a read or a write transaction.
/// The bits of a byte are transferred MSB (most significant bit) first.
///
/// \image html i2c-command-1.png
///
/// \image html i2c-command-2.png
///
/// Next the slave chip receives (write transaction) or transmits 
/// (read transaction) as many bytes as the master asks for.
///
/// \image html i2c-write-read.png 
///
///
/// <BR>
///
/// =========================================================================
///
/// \section i2c-bits bit transfer 
///
/// At the bit level, master generates clock pulses by pulling the
/// SCL line low. While the SCL is low, the master or slave can put a bit
/// on the SDA line by pulling it down (for a 0) or letting it float
/// (for a 1). 
/// 
/// The SCL line is always driven by the master (unless the slave
/// uses clock-stretching), 
/// the SDA line is driven by the device on the bus that sends the bit.
///
/// \image html i2c-bit-level.png 
///
///
/// <BR>
///
/// =========================================================================
///
/// \section i2c-specials special conditions
///
/// Two special conditions are used.
/// To signal the start (S) of a transaction, the sda is pulled low while
/// the clk is high. The reverse is used to indicate a stop 
/// (P, the end of a transaction):
/// the dta is released (goes high) while the clock is high.
/// 
/// \image html i2c-signaling.png 
///
///
/// <BR>
///
/// =========================================================================
///
/// \section i2c-addressing addressing within a slave
///
/// Simple slave chips that have only one data byte 
/// that can be read or written using
/// a single-byte read or write transaction to read or write that data byte.
///
/// Slave chips that have more than one address that can be written often
/// use a write transaction where the first byte(s) written 
/// determine the address (within the slave chip), 
/// and the subsequent byte(s) are written to that address (and to
/// the next addresses).
///
/// An I2C read transaction addresses the slave chip, but has no provision
/// to specify an address within the slave chip.
/// The common trick is that a read addresses the last address specified by 
/// a (previous) write transaction.
/// Hence to read from address X first a write is done to address X, but
/// the transaction stops after the X, hence nothing is written,
/// but this sets the address pointer inside the slave chip.
/// Now a read transaction reads from this address.
///
/// As always, consult the datasheet of the chip for the details.
///
///
/// <BR>
///
/// =========================================================================
///
/// \section i2c-ownership I2C bus intellectual ownership
///
/// The I2C bus was invented by Philips, who had a patent on it. 
/// Hence other manufacturers that implemented the I2C bus on their 
/// chips had either to pay royalties to Philips, or tried to avoid this 
/// by implementing a protocol that was compatible with I2C, 
/// without mentioning I2C. The I2C patent has expired, 
/// but you can still find many chips that are described as 
/// 'implementing a two-wire protocol' or something similar. 
/// In most cases this means that the chip implements I2C.
///
/// references:
/// - <a href="http://www.nxp.com/documents/user_manual/UM10204.pdf">
///    I2C bus specification and user manual</a> (pdf)
/// - <a href="http://i2c.info/i2c-bus-specification">
///    I2C Bus Specification</A> (info page)
/// - <a href="https://en.wikipedia.org/wiki/I2C">
///    I2C Bus</A> (wikipedia)
///
///
/// <BR>
///
/// =========================================================================
///
/// \section i2c-primitives i2c primitives abstraction
///
/// The class i2c_primitives abstracts the primitive i2c operations, 
/// on which the higher-level read and write transactions can 
/// be implemented. 
/// In most cases it is advised to use i2c transactions.
///
/// function                  | effect
/// ------------------------- | ------------------------------------------
/// read_ack()                | read and return an (expected) ack bit
/// write_ack()               | write an ack bit
/// write_nack()              | read and ack bit
/// write_byte( b )           | write one byte (8 bits)
/// read_byte( b )            | read one byte (8 bits)
/// write( d, n )   |         | write n bytes (frm d )
/// read( d, n )              | read n bytes (into d)
///
///
/// <BR>
///
/// =========================================================================
///
/// \section i2c-transactions i2c transactions
///
/// An i2xc transaction encompasses a complete read or write transaction.
/// A transaction is created from an i2c_bus object and the slave address.
/// The transaction can be used to read (for a read transaction) or write 
/// (for a write transaction) data.
///
/// functions for a read transaction object | effect
/// --------------------------------------- | -------------------- 
/// read(d)                                 | read the single byte d
/// read( d, n )                            | read n bytes (into d)
///
///
/// functions for a write transaction object | effect
/// ---------------------------------------- | -------------------- 
/// write(d)                                 | write the single byte d
/// write( d, n )                            | write n bytes (into d)
///

