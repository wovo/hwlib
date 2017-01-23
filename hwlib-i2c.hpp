// ==========================================================================
//
// File      : hwlib-i2c.hpp
// Part of   : hwlib library for V1OOPC and V1IPAS
// Copyright : wouter@voti.nl 2016
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================
/// @file

#ifndef HWLIB_I2C_H
#define HWLIB_I2C_H

#include <stdint.h>

namespace hwlib {
   
/// i2c bus master interface
//
/// This class abstracts the interface of a master to an I2C bus.
///
/// In its simplest form, an I2C bus has one master and a number of slaves
/// that are connected by two wires: SCL (clock) and SDA (data). 
/// Both lines are pulled up by pull-up resistor, and can (only) 
/// be pulled down by a connected chip (open-collector).
///
/// \image html i2c-bus.png
///
/// An I2C transaction is either a read transaction or a transaction.
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
/// At the bit level, master generates clock pulses by pulling the
/// SCL line low. While the SCL is low, the master or slave can put a bit
/// on the SDA line by pulling it down (for a 0) or letting it float
/// (for a 1). 
 
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
/// Most slave chips that have only one data byte 
/// that can be read or written use 
/// a single-byte read or write transmission to read or write that data byte.
/// Slave chips that have more than one address that can be written often
/// use a write transaction where the first byte(s) written 
/// determine the address (within the slave chip), 
/// and the subsequent byte(s) are written to that address (and to
/// the next addresses).
/// An I2C read transaction addresses the slave chip, but has no provision
/// to specify an address within the slave chip.
/// A common trick is that a read addresses the last address specified by 
/// a (previous) write transaction.
/// Hence to read from address X first a write is done to address X, but
/// the transaaction stops after the X, hence nothing is written,
/// but this sets the address pointer inside the slave chip.
/// Now a read transaction reads from this address.
///
/// As always, consult the datasheet of the chip for the details.
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

class i2c_bus {
public:

   /// i2c write transaction
   //
   /// This function write n bytes from data[] to the slave at address a.
   ///
   /// Note that n is a byte, hence the maximum number of bytes is 255.
   virtual void write( fast_byte a, const byte data[], fast_byte n ) = 0;

   /// i2c read transaction
   //
   /// This function reads n bytes from the slave at address a to data[].
   ///
   /// Note that n is a byte, hence the maximum number of bytes is 255. 
   virtual void read( fast_byte a, byte data[], fast_byte n ) = 0;
  
   
}; // class i2c_bus  

/// bit-banged i2c bus implementation
//
/// This class implements a bit-banged master interface to an I2C bus.
/// Limitations:
///    - only the 7-bit address format is supported
///    - clock stretching by the slave is not supporte
///    - only a single master is supported
///    - the speed is fixed at ~ 100 kHz or somewhat lower
class i2c_bus_bit_banged_scl_sda : public i2c_bus {
private:
   pin_oc & scl, & sda;
   
   void wait_half_period(){
      wait_us( 5 );      
   }
   
   void write_bit( bool x ){
      scl.set( 0 );
      wait_half_period();
      sda.set( x );
      scl.set( 1 );
      wait_half_period();
   }

   bool read_bit(){
      scl.set( 0 );
      sda.set( 1 );
      wait_half_period();  
      scl.set( 1 );
      wait_half_period();
      bool result = sda.get();
      wait_half_period();    
      return result;
   }       
  
   void write_start(){
      sda.set( 0 );
      wait_half_period();
      scl.set( 0 );
      wait_half_period(); 
   }

   void write_stop(){
      scl.set( 0 );
      wait_half_period();   
      sda.set( 0 );
      wait_half_period();   
      scl.set( 1 );
      wait_half_period();   
      sda.set( 1 );
      wait_half_period();    
   }
    
   bool read_ack(){
      bool ack = ! read_bit(); 
      return ack;
   } 

   void write_ack(){
      write_bit( 0 );
   }

   void write_nack(){
      write_bit( 1 );
   }

   void write_byte( fast_byte x ){
      for( fast_byte i = 0; i < 8; i++ ){
         write_bit( ( x & 0x80 ) != 0 );
         x = x << 1;
      }         
    }

   fast_byte read_byte(){
      fast_byte result = 0;
      for( fast_byte i = 0; i < 8; i++ ){
         result = result << 1;
         if( read_bit() ){
            result |= 0x01;
         } 
      }   
      return result;     
   }        
   
public:

   /// construct a bit-banged I2C bus from the scl and sda pins
   //
   /// This constructor creates a bit-banged I2C bus master
   /// from the scl and sda pins.
   i2c_bus_bit_banged_scl_sda( pin_oc & scl, pin_oc & sda ):
      scl( scl ), sda( sda )
   {
      scl.set( 1 );
      sda.set( 1 );
   }
      
   /// write to a connect I2C slave device   
   //
   /// This function writes n bytes of data to the device with address a
   /// that is connected to the I2C bus.
   void write( fast_byte a, const byte data[], fast_byte n ) override {
      write_start();
      write_byte( a << 1 );
      for( fast_byte i = 0; i < n; i++ ){
         read_ack();
         write_byte( data[ i ] );
      }               
      read_ack();
      write_stop();      
   }
   
   /// read from a connected I2C slave device
   //
   /// This function reads n bytes of data from the device with address a
   /// that is connected to the I2C bus.
   void read( fast_byte a, byte data[], fast_byte n ) override {
      write_start();
      write_byte( ( a << 1 ) | 0x01 );    
      read_ack();
      for( fast_byte i = 0; i < n; i++ ){
         if( i > 0 ){
            write_ack();
         }   
         data[ i ] = read_byte();
      }               
      write_stop();      
   }      
   
}; // class i2c_bus_bit_banged_scl_sda    
   
}; // namespace hwlib

#endif // HWLIB_I2C_H