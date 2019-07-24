// ==========================================================================
//
// File      : hwlib-demos.hpp
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

/// blink-forever function
/// 
/// This function blinks the pin: ms milliseconds on, and
/// ms milliseconds off. It never returns.
void blink( pin_out & pin, uint_fast16_t  ms = 200 );

/// @copydoc blink( pin_out & pin, uint_fast16_t  ms = 200 );
void blink( pin_oc & pin, uint_fast16_t  ms = 200 );

/// @copydoc blink( pin_out & pin, uint_fast16_t  ms = 200 );
void blink( pin_in_out & pin, uint_fast16_t  ms = 200 );

/// blink function
/// 
/// This function blinks the pin: ms milliseconds on, and
/// ms milliseconds off, for t milliseconds
void blink( pin_out & pin, uint_fast16_t ms, uint_fast16_t t );

/// @copydoc blink( pin_out & pin, uint_fast16_t ms, uint_fast16_t t );
void blink( pin_oc & pin, uint_fast16_t ms, uint_fast16_t t );

/// @copydoc blink( pin_out & pin, uint_fast16_t ms, uint_fast16_t t );
void blink( pin_in_out & pin, uint_fast16_t ms, uint_fast16_t t );

/// background blinker
///
/// As for all background jobs: be carefuill to preserve the object!
class [[nodiscard]] blinker : public background {
private:	

   pin_out & pin;
   
public: 

   bool state;
   bool active;
   uint64_t interval;
   uint_fast64_t next_run;   
   
   blinker( pin_out & pin, uint64_t interval ):
      pin( pin ), 
	  state( 0 ), 
	  active( 1 ),
	  interval( interval ), 
	  next_run( hwlib::now_us() )
   {
       }   
   
   void work() override {     
      if( now_us() > next_run ){
         next_run += interval;   
	     state = ( ! state ) & active;
	     pin.write( state );
	     pin.flush();
      }         
   }	  
};


// ===========================================================================
//
// implementations
//
// ===========================================================================

#ifdef _HWLIB_ONCE 

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

void HWLIB_NORETURN blink( pin_in_out & pin, uint_fast16_t ms ){
   auto p = pin_out_from( pin );
   blink( p, ms );   
}

void HWLIB_NORETURN blink( pin_oc & pin, uint_fast16_t ms ){
   auto p = pin_out_from( pin );
   blink( p, ms );   
}

void blink( 
   pin_out & pin, 
   uint_fast16_t ms, 
   uint_fast16_t t 
){
   for(; t > ms ; t -= ms ){
      pin.write( 1 );
      pin.flush();
      wait_ms( ms );   
  
      pin.write( 0 );
      pin.flush();
      wait_ms( ms );      
   }      
}

void blink( 
   pin_oc & pin, 
   uint_fast16_t ms, 
   uint_fast16_t t 
){
   auto p = pin_out_from( pin );
   blink( p, ms, t );   
}

void blink( 
   pin_in_out & pin, 
   uint_fast16_t ms, 
   uint_fast16_t t 
){
   auto p = pin_out_from( pin );
   blink( p, ms, t );   
}

#endif // #ifdef _HWLIB_ONCE

}; // namespace hwlib
