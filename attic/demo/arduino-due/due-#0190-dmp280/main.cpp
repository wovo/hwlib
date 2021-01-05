
#include "hwlib.hpp"

class bmp280 {
private:
   hwlib::i2c_bus & bus;
   uint8_t i2c_address;
public:
   bmp280( hwlib::i2c_bus & bus, uint8_t i2c_address ):
      bus( bus ), i2c_address( i2c_address )
   {}      
   
   void write( uint8_t reg, uint8_t value ){
      auto transaction = bus.write( i2c_address );
      transaction.write( reg );
      transaction.write( value );
   }
   
   uint8_t read8( uint8_t reg ){
      bus.write( i2c_address ).write( reg );
      return bus.read( i2c_address ).read_byte();
   }
   
   int16_t read16s( uint8_t reg ){
      bus.write( i2c_address ).write( reg );
      auto transaction = bus.read( i2c_address );
      auto b1 = transaction.read_byte();
      auto b2 = transaction.read_byte();
      return ( b1 << 8 ) | ( b2 );
   }
   
   int16_t read16u( uint8_t reg ){
      bus.write( i2c_address ).write( reg );
      auto transaction = bus.read( i2c_address );
      auto b1 = transaction.read_byte();
      auto b2 = transaction.read_byte();
      return ( b1 << 8 ) | ( b2 );
   }
   
   int32_t temp_raw(){
      bus.write( i2c_address ).write( 0xFA );
      auto transaction = bus.read( i2c_address );
      auto b1 = transaction.read_byte();
      auto b2 = transaction.read_byte();
      auto b3 = transaction.read_byte();
      return ( b1 << 12 ) | ( b2 << 4 ) | ( b3 >> 4 ); 
   }
   
   int32_t temp(){
      int32_t adc = temp_raw();
      auto T1 = read16u( 0x88 );
      auto T2 = read16s( 0x8A);
      auto T3 = read16s( 0x8D );
      
    auto var1 = ((double) adc ) / 16384.0 - ((double)T1) / 1024.0;
    var1 = var1 * ((double)T2);
    auto var2 = (((double) adc) / 131072.0 - ((double)T1) / 8192.0);
    var2 = (var2 * var2) * ((double)T3);
    //calib_data->t_fine = (int32_t)(var1 + var2);
    return (var1 + var2) / 5120.0;
   }
   
   void test(){
      hwlib::cout << "id = " << hwlib::hex << read8( 0xD0 ) << "\n"; 
      write( 0xF4, 0b101'101'11 );
      hwlib::cout << "stat = " << hwlib::hex << read8( 0xF3 ) << "\n"; 
      hwlib::cout << "traw = " << hwlib::hex << temp_raw() << "\n"; 
      hwlib::cout << "temp = " << hwlib::hex << temp() << "\n"; 
      
   }
};

int main( void ){
 
   auto scl      = hwlib::target::pin_oc{ hwlib::target::pins::scl };
   auto sda      = hwlib::target::pin_oc{ hwlib::target::pins::sda };
   auto i2c_bus  = hwlib::i2c_bus_bit_banged_scl_sda{ scl,sda };
   auto chip     = bmp280( i2c_bus, 0b111'0110 );
   
   // wait for the terminal emulator to start up
   hwlib::wait_ms( 1'000 );
   
   chip.test();
}  