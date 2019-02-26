// ==========================================================================
//
// File      : hwlib-demo.hpp
// Part of   : C++ hwlib library for close-to-the-hardware OO programming
// Copyright : wouter@voti.nl 2017
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

/// \brief
/// blink function
/// \details
/// This function blinks the pin: ms milliseconds on, and
/// ms milliseconds off. It never returns.
void blink( pin_out & pin, uint_fast16_t  ms = 200 );

/// @copydoc blink( pin_out & pin, uint_fast16_t  ms = 200 );
void blink( pin_oc & pin, uint_fast16_t  ms = 200 );

/// \brief
/// kitt function
/// \details
/// This function shows a kitt display on the pins of a port.
/// Each LED is on for m milliseconds. It never returns.
void kitt( port_in_out & port, uint_fast16_t ms = 100 );

/// @copydoc kitt( port_in_out & port, uint_fast16_t  ms = 100 )
void kitt( port_out & port, uint_fast16_t ms = 100 );

/// @copydoc kitt( port_in_out & port, uint_fast16_t  ms = 100 )
void kitt( port_oc & port, uint_fast16_t ms = 100 );

/// \brief
/// snake function
/// \details
/// This function shows a snake display on the pins of a port.
/// Each LED is on for m milliseconds. It never returns.
void snake( port_out & port, uint_fast16_t ms = 100 );

/// \brief
/// dac triangle waveform demo
/// \details
/// This functions outputs a triangle waveform on the DAC outpout,
/// with step_ms milliseconds between each step.
void dac_triangle( dac & d, uint_fast16_t step_ms = 10 );

uint_fast32_t HWLIB_WEAK rand();

uint_fast32_t HWLIB_WEAK random_in_range( 
   uint_fast32_t min, 
   uint_fast32_t max 
);

// implemantations

#ifdef HWLIB_ONCE 

void HWLIB_NORETURN blink( pin_out & pin, uint_fast16_t ms ){
   for(;;){
      pin.write( 1 );
	  pin.flush();
      wait_ms( ms );   
	  
      pin.write( 0 );
	  pin.flush();
      wait_ms( ms );      
   }      
}

void HWLIB_NORETURN blink( pin_oc & pin, uint_fast16_t ms ){
   for(;;){
      pin.write( 1 );
	  pin.flush();
      wait_ms( ms );   
	  
      pin.write( 0 );
	  pin.flush();
      wait_ms( ms );      
   }      
}

void HWLIB_NORETURN kitt( port_in_out & port, uint_fast16_t ms ){
   port.direction_set_output();
   for(;;){
      for( uint_fast8_t  i = 0; i < port.number_of_pins(); ++i ){
         port.write( 0x01 << i );    
         port.flush();		 
         wait_ms( ms );
      }
      for( uint_fast8_t  i = port.number_of_pins() - 2; i > 0; --i ){
         port.write( 0x01 << i );      
         port.flush();		 
         wait_ms( ms );
      }
   }      
}

void HWLIB_NORETURN kitt( port_out & port, uint_fast16_t ms ){
   for(;;){
      for( uint_fast8_t  i = 0; i < port.number_of_pins(); ++i ){
         port.write( 0x01 << i );      
         port.flush();		 
         wait_ms( ms );
      }
      for( uint_fast8_t  i = port.number_of_pins() - 2; i > 0; --i ){
         port.write( 0x01 << i );      
         port.flush();		 
         wait_ms( ms );
      }
   }      
}

void HWLIB_NORETURN kitt( port_oc & port, uint_fast16_t ms ){
   for(;;){
      for( uint_fast8_t  i = 0; i < port.number_of_pins(); ++i ){
         port.write( 0x01 << i );      
         port.flush();		 
         wait_ms( ms );
      }
      for( uint_fast8_t  i = port.number_of_pins() - 2; i > 0; --i ){
         port.write( 0x01 << i );      
         port.flush();		 
         wait_ms( ms );
      }
   }      
}

void HWLIB_NORETURN snake( port_out & port, uint_fast16_t ms ){
   for(;;){
      for( uint_fast8_t  i = 0; i < port.number_of_pins(); ++i ){
         port.write( 0x01 << i );      
         port.flush();		 
         wait_ms( ms );
      }
   }      
}

void HWLIB_NORETURN dac_triangle( dac & d, uint_fast16_t step_ms ){
   for(;;){
      for( dac::dac_value_type i = 0; i <= d.dac_max_value; ++i ){
          d.write( i );
          wait_ms( step_ms );
      }
      for( dac::dac_value_type i = d.dac_max_value; i >= 0; --i ){
          d.write( i );
          wait_ms( step_ms );
      }
   }
}   

#endif // #ifdef HWLIB_ONCE

}; // namespace hwlib
