// ==========================================================================
//
// File      : hwlib-i2c.hpp
// Part of   : C++ hwlib library for close-to-the-hardware OO programming
// Copyright : wouter@voti.nl 2017-2019
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
   virtual void write( uint8_t x ){
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
         write( data[ i ] );
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
      bool first_read,
      uint8_t data[], 
      size_t n  
   ){
      for( uint_fast8_t i = 0; i < n; i++ ){
         if( ( ! first_read ) || ( i > 0 )){
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
      primitives.write( a << 1 );		  
   }
   
   /// write a single byte
   /// 
   /// This function write the byte d to the slave.
   ///
   void write( 
      const uint8_t d
   ){
      primitives.write( &d, 1 );			 
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
   bool first_read;
	  
public:
   
   /// create (start) a read transaction
   i2c_read_transaction( 
      i2c_primitives & primitives,
      uint_fast8_t a 
   ): 
       primitives( primitives ),
       first_read( true )
   {
      primitives.write_start();
      primitives.write( ( a << 1 ) | 0x01 );		
      primitives.read_ack();		 
   }   

   /// read a single bytes
   ///
   /// This function reads a single byte from the slave
   uint_fast8_t read( 
      uint8_t & data 
   ){	 
      primitives.read( first_read, &data, 1 );			  
      first_read = false;
      return data;
   }
   
   /// read a single bytes
   ///
   /// This function reads and returns  a single byte from the slave
   uint_fast8_t read_byte(){	 
      uint8_t data;
      primitives.read( first_read, &data, 1 );			  
      first_read = false;
      return data;
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
      primitives.read( first_read, data, n );			  
      first_read = false;
   }
   
   /// terminate (close) the read transaction
   ~i2c_read_transaction(){
      primitives.write_nack();
      primitives.write_stop();         		  
   }
     
}; // class i2c_read_transaction 

   
// ==========================================================================
//
// i2c bus
//
// ==========================================================================

/// i2c bus master interface
/// 
/// This class abstracts the interface of a master to an I2C bus.
class i2c_bus : public noncopyable {
public:

   /// low-level i2c bus operations
   i2c_primitives & primitives;

   i2c_bus( i2c_primitives & primitives ):
       primitives( primitives )
   {}   
   
   /// returns a write transaction	   
   i2c_write_transaction write( uint_fast8_t a ){
       return i2c_write_transaction( primitives, a );
   }
         
   /// returns a read transaction		 
   i2c_read_transaction read( uint_fast8_t a ){
       return i2c_read_transaction( primitives, a );
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
class i2c_bus_bit_banged_scl_sda : 
   public i2c_primitives, 
   public i2c_bus
{
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

      do {
         wait_half_period();
      } while( ! scl.read() );
   }

   bool read_bit() override {
      scl.write( 0 ); scl.flush();
      sda.write( 1 ); sda.flush();
      wait_half_period();  
      scl.write( 1 ); scl.flush();

      do {
         wait_half_period();
      } while( ! scl.read() );

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
      i2c_bus( *(i2c_primitives*) this ), scl( scl ), sda( sda )
   {
      scl.write( 1 ); scl.flush();
      sda.write( 1 ); sda.flush();
   }
   
}; // class i2c_bus_bit_banged_scl_sda    
   
}; // namespace hwlib
