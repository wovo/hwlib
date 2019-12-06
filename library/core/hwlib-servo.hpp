// ==========================================================================
//
// File      : hwlib-servo.hpp
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
   
struct servo_properties {
   uint_fast16_t min_pulse_us;	
   uint_fast16_t max_pulse_us;	   	
   uint_fast16_t swing;
   
   servo_properties(
      uint_fast16_t min_pulse_us = 500,
      uint_fast16_t max_pulse_us = 2500,
      uint_fast16_t swing = 180
   ):
      min_pulse_us( min_pulse_us ),
      max_pulse_us( max_pulse_us ),
      swing( swing )  
   {}	  
};

class servo {
protected:
   servo_properties properties;
   uint_fast16_t pulse_us;	
   virtual void dummy() = 0;
   
public:

   servo( 
      const servo_properties & properties
   ):
      properties( properties ),
      pulse_us( properties.min_pulse_us )
   {}
   
   void write_us( uint_fast16_t t ){
      pulse_us = t;
   }
   
   template< typename T >
   void write_ratio( const ratio< T > & r ){
      pulse_us = 
         properties.min_pulse_us +
         r * ( properties.max_pulse_us - properties.min_pulse_us );
   }

};

}; // namespace hwlib
