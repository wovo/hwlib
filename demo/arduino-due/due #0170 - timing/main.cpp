#include "hwlib.hpp"

namespace target = hwlib::target;

template< typename T >
void time( const char *name, int n, T lambda ){   
   auto start = hwlib::now_us();
   for( int i = 0; i < n; ++i ){
      lambda();
   }   
   auto end = hwlib::now_us();
   
   hwlib::cout 
      << hwlib::hex << start << "\n" << hwlib::hex << end << hwlib::dec << "\n"
      << hwlib::setw( 25 ) << name
      << " : "
      << hwlib::setw( 10 ) << ( end - start ) / n
      << " us\n"
      << hwlib::flush;

}

int main( void ){
   
   // wait for the PC to start the terminal
   hwlib::wait_ms( 500 );
   
   time( 
      "empty", 100, 
      [&](){ 
      } );
      
   time( 
      "hwlib::now_us()", 100, 
      [&](){ 
         auto volatile n = hwlib::now_us();
         (void) n;
      } );
      
   time( 
      "hwlib::now_us() * 2", 100, 
      [&](){ 
         auto volatile n = hwlib::now_us();
         n = hwlib::now_us();
         (void) n;
      } );
      

}
