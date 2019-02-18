// ==========================================================================
//
// File      : hwlib-i2c.hpp
// Part of   : C++ hwlib library for close-to-the-hardware OO programming
// Copyright : wouter@voti.nl 2017
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

// included only via hwlib.hpp, hence no multiple-include guard is needed

// this file contains Doxygen lines
/// @file

namespace hwlib {
	
// ==========================================================================
//
// i2c primitives
//
// ==========================================================================

/// i2c primitives abstraction
///
/// This class abstracts the primitive i2c operations, on which
/// the higher-level read and write transactions can be implemented.
///
/// An implementation must implement these operations:
///    - read_bit()
///    - write_bit()
///    - write_start()
///    - write_stop()
///
/// An implementation can implement these operations 
/// (when it can perform these functions more efficiently than the default
/// implementatiosn):
///    - read_ack()
///    - write_ack()
///    - write_nack()
///    - write_byte( byte )
///    - read_byte( byte )
///    - write( multiple bytes )
///    - read( multiple bytes )
///
/// The default implementations do handle neither bus contention nor
/// clock-stretching by a slave.
class i2c_primitives {
public:
	
   /// output a single bit	
   virtual void write_bit( bool x ) = 0;

   /// input (read) a single bit
   virtual bool read_bit() = 0;
  
   /// output a start bit
   virtual void write_start() = 0;

   /// output a stop bit
   virtual void write_stop() = 0;
    
   /// input (read) and return an ack
   ///
   /// The default implementation inputs a bit and returns its inverse.
   virtual bool read_ack(){
      bool ack = ! read_bit(); 
      return ack;
   } 

   /// output an ack bit
   ///
   /// The default implementation outputs a 0 bit.
   virtual void write_ack(){
      write_bit( 0 );
   }

   /// output a nack bit 
   ///
   /// The default implementation outputs a 1 bit.
   virtual void write_nack(){
      write_bit( 1 );
   }

   /// output (write) a single byte
   ///
   /// The default implementation outputs the 8 bits.
   virtual void write_byte( uint_fast8_t x ){
      for( uint_fast8_t i = 0; i < 8; i++ ){
         write_bit( ( x & 0x80 ) != 0 );
         x = x << 1;
      }         
   }
   
   /// output (write) multiple bytes
   ///
   /// The default implementation calls, for each byte 
   ///    - read_ack
   ///    - write to output each byte.
   virtual void write( 
      const uint8_t data[], 
      size_t n  
   ){
      for( size_t i = 0; i < n; i++ ){
         (void) read_ack();
         write_byte( data[ i ] );
      }   
   }      

   /// input (read) a byte
   ///
   /// The default implementation inputs 8 bits and
   /// returns them as a byte.
   virtual uint_fast8_t read_byte(){
      uint_fast8_t result = 0;
      for( uint_fast8_t i = 0; i < 8; i++ ){
         result = result << 1;
         if( read_bit() ){
            result |= 0x01;
         } 
      }   
      return result;     
   }        
   
   /// input (read) multiple bytes
   ///
   /// The default implementation calls, for each byte 
   ///    - read_ack for each byte *except* the first when first_byte == true
   ///    - write to output each byte.   
   virtual void read( 
      bool first_write,
      uint8_t data[], 
      size_t n  
   ){
      for( uint_fast8_t i = 0; i < n; i++ ){
         if( ( ! first_write ) || ( i > 0 )){
            write_ack();
         }   
         data[ i ] = read_byte();
      }    
   }      
};
   

// ==========================================================================
//
// i2c write transaction
//
// ==========================================================================

/// i2c write transaction class
///
/// This class abstracts a write transaction.
/// The write transaction is in progress for 
/// as long as this object exists.
/// Multiple write calls can be done on the object.
/// The destructor will close the transaction.   
class i2c_write_transaction {
private:
   i2c_primitives & primitives;
      
public:
   
   /// create (start) a write transaction
   i2c_write_transaction( 
      i2c_primitives & primitives,
      uint_fast8_t a 
   ): 
       primitives( primitives )
   {
      primitives.write_start();
      primitives.write_byte( a << 1 );		  
   }
   
   /// write bytes
   /// 
   /// This function writes n bytes from data[] to the slave.
   ///
   /// Note that n is a byte, hence the maximum 
   /// number of bytes per call is 255.   
   void write( 
      const uint8_t data[], 
      size_t n 
   ){
      primitives.write( data, n );			 
   }		  
   
   /// terminate (close) the write transaction
   ~i2c_write_transaction(){
      primitives.read_ack();
      primitives.write_stop();		  
   }
	  
}; // class i2c_write_transaction  


// ==========================================================================
//
// i2c read transaction
//
// ==========================================================================

/// i2c bus read transaction class
///
/// This class abstracts a read transaction.
/// The read transaction is in progress for as long as this object exists.
/// Multiple read calls can be done on the object.
/// The destructor will close the transaction.
class i2c_read_transaction {
private:
   i2c_primitives & primitives;    
   bool first_write;
	  
public:
   
   /// create (start) a read transaction
   i2c_read_transaction( 
      i2c_primitives & primitives,
      uint_fast8_t a 
   ): 
       primitives( primitives ),
       first_write( false )
   {
      primitives.write_start();
      primitives.write_byte( ( a << 1 ) | 0x01 );		
      primitives.read_ack();		 
   }   

   /// read bytes
   ///
   /// This function reads n bytes from the slave to data[].
   ///
   /// Note that n is a byte, hence the maximum 
   /// number of bytes per call is 255. 
   void read( 
      uint8_t data[], 
      size_t n 
   ){	 
      primitives.read( first_write, data, n );			  
      first_write = false;
   }
   
   /// terminate (close) the read transaction
   ~i2c_read_transaction(){
      primitives.write_stop();         		  
   }
     
}; // class i2c_read_transaction 

   
// ==========================================================================
//
// i2c bus transactions
//
// ==========================================================================
   
class i2c_bus_transactions {
private:

   i2c_primitives & primitives;	
   
public:    

   i2c_bus_transactions( i2c_primitives & primitives ):
      primitives( primitives )
   {}	  
       
   i2c_write_transaction write( uint_fast8_t a ){
       return i2c_write_transaction( primitives, a );
   }
         
   i2c_read_transaction read( uint_fast8_t a ){
       return i2c_read_transaction( primitives, a );
   }
         
}; // class i2c_bus_transactions


// ==========================================================================
//
// i2c channel transactions
//
// ==========================================================================

class i2c_channel_transactions {
private:

   i2c_primitives & primitives;		
   uint_fast8_t a;
   	
public:    

   i2c_channel_transactions( 
      i2c_primitives & primitives,
      uint_fast8_t a
   ):   
      primitives( primitives ),   
      a( a )
   {}	  
      
   i2c_write_transaction write(){
       return i2c_write_transaction( primitives, a );
   }
         
   i2c_read_transaction read(){
       return i2c_read_transaction( primitives, a );
   }
         
}; // class i2c_channel_transactions


// ==========================================================================
//
// i2c channel
//
// ==========================================================================

/// a channel to a specific i2c slave
class i2c_channel {
public:	
   
   i2c_primitives & primitives;
   i2c_channel_transactions transactions;	  

   i2c_channel( 
      i2c_primitives & primitives,
	  uint_fast8_t a 
   ):
      primitives( primitives ), transactions( primitives, a )
   {}
   
   /// single i2c write transaction
   ///
   /// This function writes n bytes from data[] to the slave 
   ///
   /// Note that n is a byte, hence the maximum number of bytes is 255.
   virtual void write( 
      const uint8_t data[], 
      size_t n 
   ){
      auto t = transactions.write();
      t.write( data, n );	  
   }

   /// single i2c read transaction
   /// 
   /// This function reads n bytes from the slave 
   ///
   /// Note that n is a byte, hence the maximum number of bytes is 255. 
   virtual void read(  
      uint8_t data[], 
      size_t n 
   ){
      auto t = transactions.read();
      t.read( data, n );	  
   }	   
	  
}; // class i2c_channel


// ==========================================================================
//
// i2c bus
//
// ==========================================================================

/// i2c bus master interface
/// 
/// This class abstracts the interface of a master to an I2C bus.
///
/// In its simplest form, an I2C bus has one master and a number of slaves
/// that are connected by two wires: SCL (clock) and SDA (data). 
/// Both lines are pulled up by pull-up resistor, and can (only) 
/// be pulled down by a connected chip (open-collector).
///
/// \image html i2c-bus.png
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
class i2c_bus : protected i2c_primitives {
protected:

   i2c_bus():
      primitives( *this ),
      transactions( *this )
   {}   
   
public:

   /// low-level i2c bus operations
   i2c_primitives & primitives;
   
   /// multi-step i2c-bus transactions
   i2c_bus_transactions transactions;

   /// single i2c write transaction
   ///
   /// This function writes n bytes from data[] to the slave at address a.
   ///
   /// Note that n is a byte, hence the maximum number of bytes is 255.
   virtual void write( 
      uint_fast8_t a, 
      const uint8_t data[], 
      size_t n 
   ){
      auto t = transactions.write( a );
      t.write( data, n );	  
   }

   /// single i2c read transaction
   /// 
   /// This function reads n bytes from the slave at address a to data[].
   ///
   /// Note that n is a byte, hence the maximum number of bytes is 255. 
   virtual void read( 
      uint_fast8_t a, 
      uint8_t data[], 
      size_t n 
   ){
      auto t = transactions.read( a );
      t.read( data, n );	  
   }	   
   
   i2c_channel channel( uint_fast8_t a ){
      return i2c_channel( primitives, a );
   }	  
     
}; // class i2c_bus  


// ==========================================================================
//
// bit-banged i2c bus implementation
//
// ==========================================================================


/// bit-banged i2c bus implementation
/// 
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
      wait_us( 1 );      
   }
   
   void write_bit( bool x ) override {
      scl.write( 0 ); scl.flush();
      wait_half_period();
      sda.write( x ); sda.flush();
      scl.write( 1 ); scl.flush();
      wait_half_period();
   }

   bool read_bit() override {
      scl.write( 0 ); scl.flush();
      sda.write( 1 ); sda.flush();
      wait_half_period();  
      scl.write( 1 ); scl.flush();
      wait_half_period();
      sda.refresh();
      bool result = sda.read();
      wait_half_period();    
      return result;
   }       
  
   void write_start() override {
      sda.write( 0 ); sda.flush();
      wait_half_period();
      scl.write( 0 ); scl.flush();
      wait_half_period(); 
   }

   void write_stop() override {
      scl.write( 0 ); scl.flush();
      wait_half_period();   
      sda.write( 0 ); sda.flush();
      wait_half_period();   
      scl.write( 1 ); scl.flush();
      wait_half_period();   
      sda.write( 1 ); sda.flush();
      wait_half_period();    
   }     
   
public:

   /// construct a bit-banged I2C bus from the scl and sda pins
   /// 
   /// This constructor creates a bit-banged I2C bus master
   /// from the scl and sda pins.
   i2c_bus_bit_banged_scl_sda( pin_oc & scl, pin_oc & sda ):
      scl( scl ), sda( sda )
   {
      scl.write( 1 ); scl.flush();
      sda.write( 1 ); sda.flush();
   }
   
   /// write to a connect I2C slave device   
   /// 
   /// This function writes n bytes of data to the device with address a
   /// that is connected to the I2C bus.
   void write( 
      uint_fast8_t a, 
      const uint8_t data[], 
      size_t n 
   ) override {
      auto t = transactions.write( a );
      t.write( data, n );  
   }
   
   /// read from a connected I2C slave device
   /// 
   /// This function reads n bytes of data from the device with address a
   /// that is connected to the I2C bus.
   void read( 
      uint_fast8_t a, 
      uint8_t data[], 
      size_t n 
   ) override {
      auto t = transactions.read( a );
      t.read( data, n );       
   }      
   
}; // class i2c_bus_bit_banged_scl_sda    
   
}; // namespace hwlib
