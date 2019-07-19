#include "hwlib.hpp"

namespace hwlib {
    
class hx711 {
private:
   pin_out & sck;
   pin_in & data;
   
public:
   hx711( pin_out & sck, pin_in & data ):
      sck( sck ), data( data )
   {
      sck.write( 0 );
      sck.flush();       
   } 

   bool data_ready(){
      data.refresh();
      return ! data.read();
   }    

   uint64_t read(){
      while( ! data_ready() ){}
      uint64_t result = 0;
      
      for( int i =0; i < 24; ++i ){
      
         wait_us( 1 );
         sck.write( 1 );
         sck.flush();
         wait_us( 1 );
         
         data.refresh();
         if( data.read() ){
            result |= 0b01;
         }
         result = result << 1;
         
         sck.write( 0 );
         sck.flush();
      }
      
     for( int i = 0; i < 1; ++i ){
      
         sck.write( 1 );
         sck.flush();
         wait_us( 1 );
         
         sck.write( 0 );
         sck.flush();
         wait_us( 1 );
     }
     
     return result;
      
   }
};

};

int main( void ){
    
   // wait for the PC to start the console
   hwlib::wait_ms( 1000 );
   hwlib::cout << "HX711 demo \n";
   
   auto sck   = hwlib::target::pin_out{ hwlib::target::pins::a1 };
   auto data  = hwlib::target::pin_in{ hwlib::target::pins::a0 };
   auto hx    = hwlib::hx711( sck, data );

   for(;;){     
      hwlib::wait_ms( 500 );
      hwlib::cout << hwlib::hex << hx.read() << "\n";
   }
}   