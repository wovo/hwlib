// ==========================================================================
//
// File      : hwlib-demo.hpp
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

/// kitt function
/// 
/// This function shows a kitt display on the pins of a port.
/// Each LED is on for m milliseconds. It never returns.
void kitt( port_in_out & port, uint_fast16_t ms = 100 );

/// @copydoc kitt( port_in_out & port, uint_fast16_t  ms = 100 )
void kitt( port_out & port, uint_fast16_t ms = 100 );

/// @copydoc kitt( port_in_out & port, uint_fast16_t  ms = 100 )
void kitt( port_oc & port, uint_fast16_t ms = 100 );

/// snake function
/// 
/// This function shows a snake display on the pins of a port.
/// Each LED is on for m milliseconds. It never returns.
void snake( port_in_out & port, uint_fast16_t ms = 100 );

/// @copydoc kitt( port_in_out & port, uint_fast16_t  ms = 100 )
void snake( port_out & port, uint_fast16_t ms = 100 );

/// @copydoc kitt( port_in_out & port, uint_fast16_t  ms = 100 )
void snake( port_oc & port, uint_fast16_t ms = 100 );


// ===========================================================================
//
// implementations
//
// ===========================================================================

#ifdef _HWLIB_ONCE 

void HWLIB_NORETURN kitt( port_out & port, uint_fast16_t ms ){
   auto direct_port = direct( port );
   for(;;){
      for( uint_fast8_t  i = 0; i < direct_port.number_of_pins(); ++i ){
         direct_port.write( 0x01 << i );       
         wait_ms( ms );
      }
      for( uint_fast8_t  i = direct_port.number_of_pins() - 2; i > 0; --i ){
         direct_port.write( 0x01 << i );      	 
         wait_ms( ms );
      }
   }      
}

void HWLIB_NORETURN kitt( port_in_out & port, uint_fast16_t ms ){
   auto out_port = port_out_from( port );
   kitt( out_port, ms );
}

void HWLIB_NORETURN kitt( port_oc & port, uint_fast16_t ms ){
   auto out_port = port_out_from( port );
   kitt( out_port, ms );    
}

void HWLIB_NORETURN snake( port_out & port, uint_fast16_t ms ){
   auto direct_port = direct( port );
   for(;;){
      for( uint_fast8_t  i = 0; i < direct_port.number_of_pins(); ++i ){
         direct_port.write( 0x01 << i );      		 
         wait_ms( ms );
      }
   }      
}

void HWLIB_NORETURN snake( port_in_out & port, uint_fast16_t ms ){
   auto out_port = port_out_from( port );
   snake( out_port, ms );
}

void HWLIB_NORETURN snake( port_oc & port, uint_fast16_t ms ){
   auto out_port = port_out_from( port );
   snake( out_port, ms );    
}

#endif // #ifdef HWLIB_ONCE


// ===========================================================================
//
// background kitt
//
// ===========================================================================

class kitt_background : public background {
private:
   port_out & port;
   uint_fast16_t us;
   
   uint_fast64_t next;
   int_fast8_t position = 0;
   int_fast8_t direction = 1;
   
   void work() override {
      auto now = now_us();       
      if( now > next ){
          next += us;
          position += direction;
          if( direction > 0 ){
             if( position + 1 == (int_fast8_t)port.number_of_pins() ){
                direction = -1; 
             }
          } else {
             if( position == 0 ){
                direction = +1; 
             }
          }
          port.write( 0b01 << position );
          port.flush();
      }
   }
   
public:   
   kitt_background( port_out & port, uint_fast16_t ms = 100 ):
      port( port ), us( ms * 1000 ), next( now_us() )
   {}
     
};


}; // namespace hwlib
