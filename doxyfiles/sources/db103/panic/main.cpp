// ==========================================================================
//
// shows how an application can define its own panic function
//
// (c) Wouter van Ooijen (wouter@voti.nl) 2017-2019
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt) 
//
// ==========================================================================

#include "hwlib.hpp"

//! [[Doxygen panic example]]

namespace hwlib {
   
   // defining your own panic hnadling function

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
   
   // wait for the PC to start the console
   hwlib::wait_ms( 500 );

   // there is no port 99, so this will cause a panic
   hwlib::target::pin_out pin( 99, 0 );  

}