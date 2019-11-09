// ==========================================================================
//
// File      : hwlib-spi.hpp
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
   
/// This class abstracts the interface of a master to a SPI bus. 
class spi_bus : public noncopyable {
private:

   /// spi transaction
   ///
   /// This is the read-and-write operation 
   /// that a concrete spi_bus must implement.
   /// It simultaneously reads and writes n bytes of data.
   ///
   /// The implementation must handle the situation that 
   /// one or both of data_out or data_in are nullptr.
   virtual void write_and_read( 
      const size_t n, 
      const uint8_t data_out[], 
      uint8_t data_in[] 
   ) = 0;   
   
   // read_and_write is used through the functions in transaction
   friend class spi_transaction;
   
public:   

   /// spi transaction object
   ///
   /// A SPI transaction object is created (adn destructed) 
   /// for each SPI transaction.
   /// When a SPI transaction object is is constructed, 
   //  the sel pin is activated. 
   /// When the object is destructed, the sel pin is deselected.
   ///
   /// While the transaction object exists, its functions
   /// can be used to transfer data to and from the peripheral. 
   class spi_transaction {
   private:
   
      spi_bus & bus;
      
      pin_direct_from_out_t sel;
      
      spi_transaction( spi_bus & bus, pin_out & _sel ):
         bus( bus ), sel( direct( _sel ))
      {
         sel.write( 0 );
      }
      
      friend class spi_bus;
      
   public:    
   
      /// destructor: deselect the sel pin
      ~spi_transaction(){
         sel.write( 1 );          
      }

      /// read and write data (raw arrays)
      ///      
      /// This function simultaneously writes n bytes 
      /// from data_out to the peripheral 
      /// and reads n bytes from the peripheral into data_in.
      ///
      /// This function uses an unsafe (raw array) interface.
      /// Prefer to use a function that uses std::array<> instead.
      ///
      /// When data_out is nullptr, 0 bits are written.
      /// When data_in is nullptr, the bits that are read are ignored.
      void HWLIB_INLINE write_and_read( 
         const size_t n, 
         const uint8_t data_out[], 
         uint8_t data_in[] 
      ){
         bus.write_and_read( n, data_out, data_in );
      }
   
      /// read and write data (std::array<>'s)
      ///      
      /// This function simultaneously writes the data from 
      /// data_out to the peripheral 
      /// and reads from the peripheral into data_in.
      template< size_t n >
      void HWLIB_INLINE write_and_read( 
         const std::array< uint8_t, n > & data_out, 
         std::array< uint8_t, n > & data_in
      ){
         bus.write_and_read( n, data_out.begin(), data_in.begin() );
      }   
      
      /// write data (raw array)
      ///      
      /// This function writes n bytes 
      /// from data_out to the peripheral.
      ///
      /// This function uses an unsafe (raw array) interface.
      /// Prefer to use a function that uses std::array<> instead.
      void HWLIB_INLINE write( 
         const size_t n, 
         const uint8_t data_out[]
      ){
         bus.write_and_read( n, data_out, nullptr );
      }

      /// write data (std:array<>)
      ///      
      /// This function writes the data 
      /// from data_out to the peripheral.      
      template< size_t n > 
      void HWLIB_INLINE write( 
         const std::array< uint8_t, n > & data_out
      ){
         bus.write_and_read( n, data_out.begin(), nullptr );
      }   
      
      /// write data (uint8_t)
      ///      
      /// This function writes a single byte of
      /// data to the peripheral.
      void HWLIB_INLINE write( 
         const uint8_t d
      ){
         bus.write_and_read( 1, & d, nullptr );
      }
      
      /// read data (raw array)
      ///      
      /// This function reads n bytes from the peripheral into data_in.
      ///	  
      /// This function uses an unsafe (raw array) interface.
      /// Prefer to use a function that uses std::array<> instead.
      void HWLIB_INLINE read( 
         const size_t n, 
         uint8_t data_in[] 
      ){
         bus.write_and_read( n, nullptr, data_in );
      }      
      
      /// read data (std::array<>)
      ///      
      /// This function reads n bytes from the peripheral into data_in.
      template< size_t n >
      void HWLIB_INLINE read( 
         std::array< uint8_t, n > & data_in
      ){
         bus.write_and_read( n, nullptr, data_in.begin() );
      }   
      
      /// read a single byte
      ///      
      /// This function reads and returns a single byte.
      uint8_t HWLIB_INLINE read_byte(){
         uint8_t d;          
         bus.write_and_read( 1, nullptr, & d );
         return d;
      }       
   
   }; // class spi_transaction   
   
   /// spi read-and-write transaction 
   ///
   /// This function creates and returns a SPI transaction object
   /// for the spi bus and the indicated sel pin. 
   spi_transaction transaction( pin_out & sel ){
      return spi_transaction( *this, sel );
   }

}; // class spi_bus  


/// bit-banged SPI bus implementation
///
/// This class implements a bit-banged master interface to a SPI bus.
class spi_bus_bit_banged_sclk_mosi_miso : public spi_bus {
private:

   pin_direct_from_out_t sclk;
   pin_direct_from_out_t mosi;
   pin_direct_from_in_t  miso;
   
   // very crude;
   // delay should be a constructor parameter
   void HWLIB_INLINE wait_half_period(){
      wait_us( 1 );      
   }
   
   void write_and_read( 
      const size_t n, 
      const uint8_t data_out[], 
      uint8_t data_in[] 
   ) override {

      for( uint_fast8_t i = 0; i < n; ++i ){
          
         uint_fast8_t d = 
            ( data_out == nullptr )
            ? 0 
            : *data_out++;
             
         for( uint_fast8_t j = 0; j < 8; ++j ){
            mosi.write( ( d & 0x80 ) != 0 );
            wait_half_period();
            sclk.write( 1 );
            wait_half_period();
            d = d << 1;
            if( miso.read() ){
               d |= 0x01;
            }
            sclk.write( 0 );              
         }
          
         if( data_in != nullptr ){
            *data_in++ = d;
         }
      }      
      wait_half_period();
   }      
   
public:

   /// construct a bit-banged SPI bus from the sclk, miso and mosi pins
   ///
   /// This constructor creates a simple bit-banged SPI bus master
   /// from the sclk, miso and mosi pins. 
   ///
   /// The chip select pins for the individual chips supplied to the 
   /// write_and_read() functions.
   ///
   /// When the SPI bus is used for either only writing or only reading,
   /// the unused pin argument can be specified as pin_out_dummy or
   /// pin_in_dummy.
   spi_bus_bit_banged_sclk_mosi_miso( 
      pin_out & _sclk, 
      pin_out & _mosi, 
      pin_in  & _miso 
   ):
      sclk( direct( _sclk ) ), 
      mosi( direct( _mosi ) ), 
      miso( direct( _miso ) )
   {
      sclk.write( 0 );
   }
   
}; // class spi_bus_bit_banged_sclk_mosi_miso    
   
}; // namespace hwlib
