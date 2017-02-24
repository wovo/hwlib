#include "hwlib.hpp"

namespace target = hwlib::target;

template< typename T >
void time( const char *name, T lambda ){   
   auto start = hwlib::now_us();
   lambda();
   auto end = hwlib::now_us();
   
   hwlib::cout 
      << hwlib::hex << start << "\n" << hwlib::hex << end << hwlib::dec << "\n"
      << hwlib::setw( 40 ) << name
      << " : "
      << hwlib::setw( 10 ) << ( end - start )
      << " us\n"
      << hwlib::flush;

}

void circles( hwlib::window & w, int n, hwlib::buffering buf ){
   auto m = w.size / 2;
   for( int i = 0; i < n; ++i ){
      hwlib::circle( m, 5 + 2 * i ).draw( w, buf );
   }
}

//! [[direct]]
void circles_direct( hwlib::window & w ){
   auto m = w.size / 2;
   for( int i = 0; i < 10; ++i ){
      hwlib::circle( m, 5 + 2 * i ).draw( w );
   }
}
//! [[direct]]

//! [[buffered]]
void circles_buffered( hwlib::window & w ){
   auto m = w.size / 2;
   for( int i = 0; i < 10; ++i ){       
      hwlib::circle( m, 5 + 2 * i ).draw( w, hwlib::buffering::buffered );
   }
   w.flush();
}
//! [[buffered]]

int main( void ){
   // kill the watchdog
   WDT->WDT_MR = WDT_MR_WDDIS;
   
   // wait for the PC to start the terminal
   hwlib::wait_ms( 500 );
   hwlib::cout << "OLED timing demo - have patience!\n";
   
   // create the i2c-interfaced display
   auto scl = target::pin_oc( target::pins::scl );
   auto sda = target::pin_oc( target::pins::sda );
   auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );
   auto display = hwlib::glcd_oled( i2c_bus, 0x3c );   
   
   time( 
      "clear - direct", 
      [&](){ 
         display.clear();
      } );
      
   time( 
      "clear - buffered", 
      [&](){ 
         display.clear( hwlib::buffering::buffered ); 
         display.flush();
      } );

   time( 
      "one circle - direct", 
      [&](){ 
         display.clear();          
         circles( display, 1, hwlib::buffering::unbuffered );
      } );
      
   time( 
      "one circle - buffered", 
      [&](){ 
         display.clear( hwlib::buffering::buffered );             
         circles( display, 1, hwlib::buffering::buffered ); 
         display.flush();
      } );
      
   time( 
      "10 circles - direct", 
      [&](){ 
         display.clear();             
         circles( display, 10, hwlib::buffering::unbuffered );
      } );
      
   time( 
      "10 circles - buffered", 
      [&](){ 
         display.clear( hwlib::buffering::buffered );   
         circles( display, 10, hwlib::buffering::buffered ); 
         display.flush();
      } );
      
   display.clear();   
   time( 
      "10 circles - direct - without cear", 
      [&](){ circles_direct( display ); }
      ); 
      
   display.clear();         
   time( 
      "10 circles - buffered - without clear", 
      [&](){ circles_buffered( display ); }
   );
}
