// ==========================================================================
//
// print hello, prefixed with a sequence number
//
// show how an application can define its own panic function
//
// ==========================================================================

#include "hwlib.hpp"

//! [[Doxygen panic example]]
namespace hwlib {
    
   void HWLIB_NORETURN panic( const char * file, const uint_fast16_t line ){

      // wait for the console connection to be ready
      hwlib::wait_ms( 500 );
   
      // tell what happend and where
      // (don't forget to flush)
      hwlib::cout 
         << "\n"
         << "   *** PANIC (unrecoverable error) *** \n"
         << "   detected in file '" << file << "'\n"
         << "   at line " << line << "\n"
         << hwlib::flush;
      
      // don't return   
      for(;;);
   }
}
//! [[Doxygen panic example]]

int main( void ){	
   // kill the watchdog
   WDT->WDT_MR = WDT_MR_WDDIS;
   
   // wait for the PC to start the console
   hwlib::wait_ms( 500 );

   // there is no port 99, so this will cause a panic
   hwlib::target::pin_out pin( 99, 0 );  

}