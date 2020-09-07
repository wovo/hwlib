#include "hwlib.hpp"

namespace target = hwlib::target;

namespace hwlib {
   
class spi_bus_bit_banged_sclk_mosi_miso_2 : public spi_bus {
private:

   pin_direct_from_out_t sclk;
   pin_direct_from_out_t mosi;
   pin_direct_from_in_t  miso;
   
   // very crude;
   // delay should be a constructor parameter
   void HWLIB_INLINE wait_half_period(){
//      wait_us( 1 );      
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

            sclk.write( 1 );

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
   spi_bus_bit_banged_sclk_mosi_miso_2( 
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
   
class spi_bus_bit_banged_sclk_mosi_miso_3 : public spi_bus {
private:

   pin_direct_from_out_t sclk;
   pin_direct_from_out_t mosi;
   pin_direct_from_in_t  miso;
   
   // very crude;
   // delay should be a constructor parameter
   void HWLIB_INLINE wait_half_period(){
//      wait_us( 1 );      
   }
   
   void write_and_read( 
      const size_t n, 
      const uint8_t data_out[], 
      uint8_t data_in[] 
   ) override {

      uint_fast32_t d = data_out[ 0 ];
             
         for( uint_fast8_t j = 0; j < 8; ++j ){

            mosi.write( ( d & 0x80 ) != 0 );

            sclk.write( 1 );

            d = d << 1;
            sclk.write( 0 );              
         }

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
   spi_bus_bit_banged_sclk_mosi_miso_3( 
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
   
class spi_bus_bit_banged_sclk_mosi_miso_4 : public spi_bus {
private:

   pin_direct_from_out_t sclk;
   pin_direct_from_out_t mosi;
   pin_direct_from_in_t  miso;
   
   // very crude;
   // delay should be a constructor parameter
   void HWLIB_INLINE wait_half_period(){
//      wait_us( 1 );      
   }
   
   void fast( uint_fast8_t d ){
      auto clock_high = & PIOC->PIO_SODR;
      auto clock_low  = & PIOC->PIO_CODR;
      auto clock_mask = 1 << 28;
      
      auto data_high  = & PIOC->PIO_SODR;
      auto data_low   = & PIOC->PIO_CODR;
      auto data_mask = 1 << 26;
         //hwlib::wait_ms( 1 );
 
      for( uint_fast8_t j = 0; j < 8; ++j ){
         //mosi.write( ( d & 0x80 ) != 0 );
         if(( d & 0x80 ) != 0 ){
            *data_high = data_mask;
         } else {
            *data_low = data_mask;
         }            
         //sclk.write( 1 );
         *clock_low = clock_mask;
         d = d << 1;
         // sclk.write( 0 ); 
         *clock_high = clock_mask;             
      }   
   }
   
   void write_and_read( 
      const size_t n, 
      const uint8_t data_out[],
      uint8_t data_in[]       
   ) override {

      for( uint_fast8_t i = 0; i < n; ++i ){
         uint_fast8_t d = *data_out++;
         fast( d );
      }      
   }      
   
public:

   spi_bus_bit_banged_sclk_mosi_miso_4( 
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


int main( void ){
   
   // wait for the terminal emulator to start up
   hwlib::wait_ms( 2'000 );
   hwlib::cout << "ST7789 demo\n" << hwlib::flush;   
   
   auto _sclk = hwlib::target::pin_out{ hwlib::target::pins::d3 };
   auto sclk = hwlib::invert( _sclk );
   auto mosi = hwlib::target::pin_out{ hwlib::target::pins::d4 };;
   
   auto spi  = hwlib::spi_bus_bit_banged_sclk_mosi_miso_4 { 
      sclk, mosi, hwlib::pin_in_dummy };
      
   auto dc    = hwlib::target::pin_out{ hwlib::target::pins::d5 };
   auto & cs  = hwlib::pin_out_dummy;
   auto blk   = hwlib::target::pin_out{ hwlib::target::pins::d6 };
   auto rst   = hwlib::target::pin_out{ hwlib::target::pins::d7 };
   
   blk.write( 1 );blk.flush();

   auto display     = hwlib::st7789_spi_dc_cs_rst( spi, dc, cs, rst );   
   
   for(;;){
      hwlib::cout << __LINE__ << "\n";
      auto t1 = hwlib::now_us();
      display.clear( hwlib::red );
      auto t2 = hwlib::now_us();
      hwlib::cout << __LINE__ << " " << t2 - t1 << "\n";
      t1 = hwlib::now_us();    
//blk.write( 1 );  
      display.flush();
//blk.write( 0 );
      t2 = hwlib::now_us();      
      hwlib::cout << __LINE__ << " " << t2 - t1 << "\n";
      hwlib::wait_ms( 1'000 );
      
      hwlib::cout << __LINE__ << "\n";
      display.clear( hwlib::green );
      hwlib::cout << __LINE__ << "\n";
      display.flush();
      hwlib::wait_ms( 1'000 );

      hwlib::cout << __LINE__ << "\n";
      display.clear( hwlib::blue );
      hwlib::cout << __LINE__ << "\n";
      display.flush();
      hwlib::wait_ms( 1'000 );
   }
   
}
