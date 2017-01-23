// ==========================================================================
//
// File      : hwlib-spi.hpp
// Part of   : hwlib library for V1OOPC and V1IPAS
// Copyright : wouter@voti.nl 2016
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================
/// @file

#ifndef HWLIB_SPI_H
#define HWLIB_SPI_H

#include <stdint.h>

namespace hwlib {
   
/// spi bus interface
//
/// This class abstracts the interface of a master to a SPI bus.   
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
class spi_bus {
public:

   /// spi read-and-write transaction
   //
   /// This function simultaneously writes n bytes from data_out[] 
   /// to the slave activated by the sel pin, and reads n bytes into data_in[].
   /// When data_out is a nullptr, all-0 bytes are written.
   /// When data_in is a nullptr, the data that is read is not stored.
   virtual void write_and_read( 
      pin_out & sel, 
      int n, 
      const byte data_out[], 
      byte data_in[] 
   ) = 0;

}; // class spi_bus  

/// bit-banged SPI bus implementation
//
/// This class implements a bit-banged master interface to a SPI bus.
class spi_bus_bit_banged_sclk_mosi_miso : public spi_bus {
private:
   pin_out & sclk, & mosi;
   pin_in & miso;
   
   void wait_half_period(){
      wait_us( 1 );      
   }
   
public:

   /// construct a bit-banged SPI bus from the sclk, miso and mosi pins
   //
   /// This constructor creates a bit-banged SPI bus master
   /// from the sclk, miso and mosi pins. 
   ///
   /// The chip select pins for the individual chips supplied to the 
   /// write_and_read() functions.
   ///
   /// When the SPI bus is used for either only writing or only reading,
   /// the unused pin argument can be specified as pin_out_dummy or
   /// pin_in_dummy.
   spi_bus_bit_banged_sclk_mosi_miso( 
      pin_out & sclk, 
      pin_out & mosi, 
      pin_in & miso 
   ):
      sclk( sclk ), mosi( mosi ), miso( miso )
   {
      sclk.set( 0 );
   }
   
   /// write and read to (and from) a spi chip
   //
   /// This function performs an n byte write-and-read operation on the
   /// SPI chip activated by the (active low) sel pin.
   ///
   /// When either writing or reading is not needed the corresponding
   /// argument can be a nullptr.
   void write_and_read( 
      pin_out & sel, 
      int n, 
      const byte data_out[], 
      byte data_in[] 
   ) override {

      sel.set( 0 );
      for( int i = 0; i < n; ++i ){
          
          byte d = 
             ( data_out == nullptr )
             ? 0 
             : *data_out++;
             
          for( int j = 0; j < 8; ++j ){
              mosi.set( ( d & 0x80 ) != 0 );
              wait_half_period();
              sclk.set( 1 );
              wait_half_period();
              d = d << 1;
              if( miso.get() ){
                 d |= 0x01;
              }
              sclk.set( 0 );              
          }
          
          if( data_in != nullptr ){
             *data_in++ = d;
          }
      }      
      wait_half_period();
      sel.set( 1 );
      wait_half_period();
   }      
   
}; // class spi_bus_bit_banged_sclk_mosi_miso    
   
}; // namespace hwlib

#endif // HWLIB_SPI_H