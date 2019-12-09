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
   
   
// ===========================================================================
//
// servo properties
//
// ===========================================================================   
   
/// properties of a servo
///
/// This struct stores the properties of an (individual) servo.   
struct servo_properties {
   
   /// the minimum pulse duration
   int_fast16_t min_pulse_us;	
   
   /// the maximum pulse duration
   int_fast16_t max_pulse_us;	   	
   
   /// the minimum angle, in degrees
   int_fast16_t min_angle_degrees;	
   
   /// the maximum angle, in de grees
   int_fast16_t max_angle_degrees;	   	
   
   /// construct the properties of a servo
   ///
   /// default values:
   /// pulse 500 .. 2500 us
   /// angle 0 .. 180 degrees
   constexpr servo_properties(
      int_fast16_t min_pulse_us       = 500,
      int_fast16_t max_pulse_us       = 2500,
      int_fast16_t min_angle_degrees  = 0,
      int_fast16_t max_angle_degrees  = 180
   ):
      min_pulse_us( min_pulse_us ),
      max_pulse_us( max_pulse_us ),
      min_angle_degrees( min_angle_degrees ),
      max_angle_degrees( max_angle_degrees )	  
   {}	  
   
}; // class servo_properties


// ===========================================================================
//
// servo interface
//
// ===========================================================================

/// servo interface
///
/// This abstract class represents a servo.
/// The servo angle can be set by calling either
/// write_us(), write_ratio(), or write_angle().
/// The write_ratio() and write_angle() functions 
/// use the servo properties to determine
/// the pulse duration.
class servo {
public:

   /// the properties of the servo
   const servo_properties properties;
   
   /// construct a servo interface
   ///
   /// The initial servo pulse duration is undefined.
   constexpr servo( 
      const servo_properties & properties
   ):
      properties( properties )
   {}
   
   /// set the servo angle by specifying the pulse length
   ///
   /// This function sets the pulse length (in us) 
   /// that will be written to the servo.
   ///
   /// The other write functions call this function, so
   /// a decorator only needs to implement this function.
   virtual void write_us( int_fast16_t t ) = 0;
   
   /// set the servo angle by specifying a ratio
   ///
   /// This function sets the pulse length that will be written
   /// to the servo a by specifying a ratio of the full travel.
   template< typename T >
   void write_ratio( const ratio< T > & r ){
      write_us( 
         properties.min_pulse_us +
         r * ( properties.max_pulse_us - properties.min_pulse_us )
      );
   }

   /// set the servo angle by specifying an angle
   ///
   /// This function sets the pulse length that will be written
   /// to the servo by specifying the angle (in degrees).
   void write_angle( uint_fast16_t t ){
      write_us( 
         properties.min_pulse_us +
         (int32_t) ( t - properties.min_angle_degrees ) 
            * ( properties.max_pulse_us - properties.min_pulse_us )
            / ( properties.max_angle_degrees - properties.min_angle_degrees )
      );
   }
   
}; // class servo


// ===========================================================================
//
// servo demos
//
// ===========================================================================

template< typename T, typename U >
void sweep(
   servo & s,
   const ratio< T > & start,
   const ratio< U > & end,
   uint64_t t,
   uint_fast16_t steps
){
   for( uint_fast16_t i = 0; i < steps; ++i ){
      s.write_ratio( start + ratio<>( ( end - start ) * i, steps ) );
      hwlib::wait_us( t / steps );
   }
}


// ===========================================================================
//
// servo dummy
//
// ===========================================================================
/// a dummy (do-nothing) servo class
class servo_dummy_t : public servo {
public:

   constexpr servo_dummy_t():
      servo( servo_properties() )
   {}
      
   void write_us( int_fast16_t t ) override {}
   
};  

/// a dummy (do-nothing) servo object
extern servo_dummy_t servo_dummy;

#ifdef _HWLIB_ONCE

servo_dummy_t servo_dummy;

#endif // _HWLIB_ONCE


// ===========================================================================
//
// servo invert
//
// ===========================================================================

/// inverse of a servo
///
/// The preferred way to use this class is through the overloaded 
/// constructor function invert().
class servo_invert_t : public servo {
private:
	
   servo & minion;
   
public:

   /// create an inverted servo
   servo_invert_t( servo & minion ):
      servo( minion.properties ),
      minion( minion )
   {}
   
   void write_us( int_fast16_t t ) override {
      minion.write_us( 
         properties.min_pulse_us 
         + ( properties.max_pulse_us - t )
      );         
   }
   
}; // class servo_invert_t

/// return a decorated servo
///@{ 
servo_invert_t invert( servo & s );
///@}

#ifdef _HWLIB_ONCE

servo_invert_t invert( servo & s ){
   return servo_invert_t( s );   
}   

#endif // _HWLIB_ONCE


// ===========================================================================
//
// servo all
//
// ===========================================================================

/// write to multiple servos
///
/// The preferred way to use this class is through the overloaded 
/// constructor function all().
class servo_all_t : public servo {
private:
	
   static constexpr int max_servos = 16;  
   servo * servos[ max_servos ];   
   
public:

   /// create a write-to-all servo
   servo_all_t(
      const servo_properties & properties,
      servo & p0,
      servo & p1,
      servo & p2,
      servo & p3,
      servo & p4,
      servo & p5,
      servo & p6,
      servo & p7,
      servo & p8,
      servo & p9,
      servo & p10,
      servo & p11,
      servo & p12,
      servo & p13,
      servo & p14,
      servo & p15	
   ):
      servo( properties ),
      servos { 
	     &p0,  &p1,  &p2,  &p3,  &p4,  &p5,  &p6, &p7, 
        &p8,  &p9,  &p10, &p11, &p12, &p13, &p14, &p15 
      }{}            
   
   void write_us( int_fast16_t t ) override {
      for( auto & servo : servos ){
         servo->write_us( t );
      }         
   }
   
}; // class servo_all_t

/// return a decorated servo
///@{ 
servo_all_t all( 
   servo & p0   = servo_dummy,
   servo & p1   = servo_dummy,
   servo & p2   = servo_dummy,
   servo & p3   = servo_dummy,
   servo & p4   = servo_dummy,
   servo & p5   = servo_dummy,
   servo & p6   = servo_dummy,
   servo & p7   = servo_dummy,
   servo & p8   = servo_dummy,
   servo & p9   = servo_dummy,
   servo & p10  = servo_dummy,
   servo & p11  = servo_dummy,
   servo & p12  = servo_dummy,
   servo & p13  = servo_dummy,
   servo & p14  = servo_dummy,
   servo & p15  = servo_dummy	
);
///@}

#ifdef _HWLIB_ONCE

servo_all_t all( 
   servo & p0,
   servo & p1,
   servo & p2,
   servo & p3,
   servo & p4,
   servo & p5,
   servo & p6,
   servo & p7,
   servo & p8,
   servo & p9,
   servo & p10,
   servo & p11,
   servo & p12,
   servo & p13,
   servo & p14,
   servo & p15	
){
   return servo_all_t( 
      servo_properties(),
      p0,  p1,  p2,  p3,  p4,  p5,  p6,  p7,
      p8,  p9,  p10, p11, p12, p13, p14, p15
   );
}   

#endif // _HWLIB_ONCE


}; // namespace hwlib
