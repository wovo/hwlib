// ==========================================================================
//
// File      : hwlib-ostream.hpp
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
	
	
// ===========================================================================
//
// bit-banged UARTs
//
// ===========================================================================	
   
/// a bit-banged UART char output
///
/// This function implements a bit-banged output UART pin
/// using the BMPTK_BAUDRATE.   
void uart_putc_bit_banged_pin( char c, pin_out & pin );
   
/// a bit-banged UART char input
///
/// This function implements a bit-banged input UART pin
/// using the BMPTK_BAUDRATE.      
char uart_getc_bit_banged_pin( pin_in & pin );
   
   
// ===========================================================================
//
// implementations
//
// ===========================================================================

#ifdef _HWLIB_ONCE

void uart_putc_bit_banged_pin( char c, pin_out & pin ){

   const auto bit_cel = ( ( 1000L * 1000L ) / HWLIB_BAUDRATE );
  
   pin.write( 1 );
   // use busy waiting, otherwise logging from within the RTOS
   // will cause serious problems
   wait_us_busy( bit_cel );
   
   // start bit
   pin.write( 0 );
   wait_us_busy( bit_cel );
   
   // 8 data bits
   for( uint_fast8_t i = 0; i < 8; ++i ){
      pin.write( ( c & 0x01 ) != 0x00 );
      c = c >> 1;
      wait_us_busy( bit_cel );
   }   
   
   // 2 stop bits
   pin.write( 1 );
   wait_us_busy( 2 * bit_cel ); 
}       
   
char uart_getc_bit_banged_pin( pin_in & pin ){
	
   char c = 0;        
   
   const auto bit_cel = ( ( 1000L * 1000L ) / HWLIB_BAUDRATE );
     
   // wait for start of startbit
   while( pin.read() ){ wait_ns( 1 ); }
      
   // wait until halfway the first data bit
   auto t = now_us();
   t += bit_cel + ( bit_cel / 2 );
   while( now_us() < t ){};
      
   // 8 data bits
   for( uint_fast8_t i = 0; i < 8; ++i ){
      c = c >> 1;            
      if( pin.read() ){
         c = c | 0x80;                
      }
         
      t+= bit_cel;
      while( now_us() < t ){};
   }   
   
   return c;
}     

#endif // #ifdef _HWLIB_ONCE

}; // namespace hwlib
