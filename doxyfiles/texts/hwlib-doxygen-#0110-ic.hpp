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
/// In its simplest form, an i2c bus has one master and a number of slaves
/// that are connected by two wires: SCL (clock) and SDA (data). 
/// Both lines are pulled up by pull-up resistor, and can (only) 
/// be pulled down by a connected chip (open-collector,
/// hwlib pin type \ref hwlib::pin_oc "pin_oc").
///
/// \image html i2c-bus.png
///
///
/// <BR>
///
/// =========================================================================
///
/// \section i2c-transaction-format transaction formats
///
/// An i2c transaction is either a read transaction or a write transaction.
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
/// \section i2c-bits bit-level signaling
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
/// the transaction stops after the X.
/// Hence nothing is written,
/// but this sets the address pointer inside the slave chip.
/// Now a read transaction reads from this address.
///
/// As always, consult the datasheet of the chip for the details!
///
///
/// <BR>
///
/// =========================================================================
///
/// \section i2c-ownership I2C ownership
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
///    I2C bus specification and user manual (pdf)</a>
/// - <a href="http://i2c.info/i2c-bus-specification">
///    I2C Bus Specification (info page)</A>
/// - <a href="https://en.wikipedia.org/wiki/I2C">
///    I2C Bus (wikipedia)</A>
///
///
/// <BR>
///
/// =========================================================================
///
/// \section i2c-bus i2c bus
///
/// An i2c bus object represents an i2c bus.
/// An i2c bus can be used (in order of preference)
///    - by creating a channel to a slave
///      and using the operations of that channel
///    - by read or write transactions or a transaction object, 
///      which specify the slave
///    - through its primitives
///
/// i2c bus attributes and functions     | use
/// ------------------------------------ | -------------------- 
/// \ref hwlib::i2c_bus::channel "channel( s )"                         | creates a channel to slave s
/// \ref hwlib::i2c_bus::read "read( s, d )"                         | performs a single byte read transaction
/// \ref hwlib::i2c_bus::read "read( s, d, n )"                      | performs an n byte read transaction
/// \ref hwlib::i2c_bus::write "write( s, d )"                        | performs a single byte write transaction
/// \ref hwlib::i2c_bus::write "write( s, d, n )"                     | performs an n byte write transaction
/// \ref hwlib::i2c_bus_transactions::read "transactions.read( s )"               | creates a read transaction
/// \ref hwlib::i2c_bus_transactions::write "transactions.write( s )"              | creates a write transaction
/// \ref hwlib::i2c_primitives "primitives"                           | low-level operations
///
/// The read and write operations are easier to use than a transaction, 
/// but require the data to be read or written is one contiguous block.
///
/// A \ref hwlib::i2c_bus_bit_banged_scl_sda
/// "bit-banged i2c bus implementation" is provided.
/// An object of this class is constructed from the two pins (scl and scd),
/// which must be \ref hwlib::pin_oc "pin_oc" pins.
///
///
/// <BR>
///
/// =========================================================================
///
/// \section i2c-channel i2c channel
///
/// An i2c channel abstracts the communication over an i2c bus 
/// to a specific slave. An i2c channel is created
/// from an i2c bus by providing the slave address.
///
/// An i2c channel can be used (in order of preference)
///    - by read or write transactions on a single byte or a block of bytes
///    - by creating a read or write transaction 
///      and using the operations of that transaction
///    - through its primitives (which are same as the i2c bus primitives)
///
/// The read and write operations are easier to use than a transaction, 
/// but require the data to be read or written is one contiguous block.
///
/// i2c channel attributes and functions     | use
/// ---------------------------------------- | -------------------- 
/// \ref hwlib::i2c_channel::read "read( d )"                             | performs a single byte read transaction
/// \ref hwlib::i2c_channel::read "read( d, n )"                          | performs an n byte read transaction
/// \ref hwlib::i2c_channel::read "write( d )"                            | performs a single byte write transaction
/// \ref hwlib::i2c_channel::read "write( d, n )"                         | performs an n byte write transaction
/// \ref hwlib::i2c_channel_transactions::read "transactions.read()"      | creates a read transaction
/// \ref hwlib::i2c_channel_transactions::write "transactions.write()"    | creates a write transaction
/// \ref hwlib::i2c_primitives "primitives"                               | low-level operations
///
///
/// <BR>
///
/// =========================================================================
///
/// \section i2c-transactions i2c transactions
///
/// An i2c transaction encompasses a complete read or write transaction.
/// A transaction is created from an i2c_bus object and the slave address.
/// The transaction can be used to read (for a read transaction) or write 
/// (for a write transaction) data.
/// A transaction allows for multiple read or write operations
/// within a single transaction.
/// A transaction is started (control byte send) by the transaction constructor.
/// A transaction is closed (final NACK send) by the transaction destructor.
///
/// i2c read transaction functions     | use
/// ---------------------------------- | -------------------- 
/// \ref hwlib::i2c_read_transaction::read_byte "read_byte()"                          | performs a single byte read
/// \ref hwlib::i2c_read_transaction::read(uint8_t data[],size_t n) "read( d, n )"     | performs an n byte read
///
/// <BR>
///
/// i2c write transaction functions    | use
/// ---------------------------------- | -------------------- 
/// \ref hwlib::i2c_write_transaction::write(uint8_t) "write( d )"                     | performs a single byte write
/// \ref hwlib::i2c_write_transaction::write "write(const uint8_t data[],size_t n)"    | performs an n byte write
///
///
/// <BR>
///
/// =========================================================================
///
/// \section i2c-primitives i2c primitives 
///
/// The class i2c_primitives abstracts the primitive i2c operations, 
/// from which the higher-level read and write transactions 
/// are implemented. 
/// These are the operations that must be implemented by an i2c
/// implementation.
///
/// As an i2c user, you should probably never use these functions.
///
/// function                  | use
/// ------------------------- | ------------------------------------------
/// \ref hwlib::i2c_primitives::read_ack read_ack()      | read and return an (expected) ack bit
/// \ref hwlib::i2c_primitives::write_ack write_ack()    | write an ack bit
/// \ref hwlib::i2c_primitives::write_nack write_nack()  | read and ack bit
/// \ref hwlib::i2c_primitives::write(uint8_t)  write( b )    | write one byte (8 bits)
/// \ref hwlib::i2c_primitives::read_byte read_byte()    | read one byte (8 bits)
/// \ref hwlib::i2c_primitives::write write(uint8_t data[],size_t n)      | write n bytes (from d )
/// \ref hwlib::i2c_primitives::read read( d, n )        | read n bytes (into d)
///
///
/// <BR>
/// 


