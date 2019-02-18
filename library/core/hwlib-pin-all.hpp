// ==========================================================================
//
// File      : hwlib-pin-decorators.hpp
// Part of   : C++ hwlib library for close-to-the-hardware OO programming
// Copyright : wouter@voti.nl 2017
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

// included only via hwlib.hpp, hence no multiple-include guard is needed

// this file contains Doxygen linesd
/// @file

namespace hwlib {

class pin_out_from_oc : public pin_out {
   pin_oc & slave;
   
public:
   pin_out_from_oc( pin_oc & slave ): slave( slave ){}
   
   void write( bool x ){
      slave.write( x );
   }
};

class pin_invert_from_out : public pin_out {
   pin_out & slave;
   
public:
   pin_invert_from_out( pin_out & slave ): slave( slave ){}
   
   void write( bool x ){
      slave.write( !x );
   }

   void flush() override {
      slave.flush();            
   }
};

	
// ==========================================================================
//
// pin_out
//
// ==========================================================================

class all_from_pin_out : public pin_out {
private:

   static constexpr int max_pins = 16;  

   // 8 must match the number of parameters of the constructor
   pin_out * pins[ max_pins ];   
   
public:

   /// \brief
   /// construct a port_out from up to 8 pin_outs
   /// \details
   /// This constructor creates a port_out from up to 8 pin_out pins.
   /// The first pin is the lowest pin in the port, etc.
   all_from_pin_out(
      pin_out & p0 = pin_out_dummy,
      pin_out & p1 = pin_out_dummy,
      pin_out & p2 = pin_out_dummy,
      pin_out & p3 = pin_out_dummy,
      pin_out & p4 = pin_out_dummy,
      pin_out & p5 = pin_out_dummy,
      pin_out & p6 = pin_out_dummy,
      pin_out & p7 = pin_out_dummy,
      pin_out & p8 = pin_out_dummy,
      pin_out & p9 = pin_out_dummy,
      pin_out & p10 = pin_out_dummy,
      pin_out & p11 = pin_out_dummy,
      pin_out & p12 = pin_out_dummy,
      pin_out & p13 = pin_out_dummy,
      pin_out & p14 = pin_out_dummy,
      pin_out & p15 = pin_out_dummy	
   ):
      pins{ 
	     &p0, &p1, &p2, &p3, &p4, &p5, &p6, &p7, &p8, 
		 &p9, &p10, &p11, &p12, &p13, &p14, &p15 
      }{}            
   
   void write( bool x ) override {
      for( uint_fast8_t i = 0; i < max_pins; ++i ){
         pins[ i ]->write( x );
      }         
   }
   
   void flush() override {
      for( uint_fast8_t i = 0; i < max_pins; ++i ){
         pins[ i ]->flush();
      }                
   }

};

all_from_pin_out all( 
   pin_out & p0  = pin_out_dummy,
   pin_out & p1  = pin_out_dummy,
   pin_out & p2  = pin_out_dummy,
   pin_out & p3  = pin_out_dummy,
   pin_out & p4  = pin_out_dummy,
   pin_out & p5  = pin_out_dummy,
   pin_out & p6  = pin_out_dummy,
   pin_out & p7  = pin_out_dummy,
   pin_out & p8  = pin_out_dummy,
   pin_out & p9  = pin_out_dummy,
   pin_out & p10 = pin_out_dummy,
   pin_out & p11 = pin_out_dummy,
   pin_out & p12 = pin_out_dummy,
   pin_out & p13 = pin_out_dummy,
   pin_out & p14 = pin_out_dummy,
   pin_out & p15 = pin_out_dummy	
);

#ifdef HWLIB_ONCE

all_from_pin_out all( 
   pin_out & p0,
   pin_out & p1,
   pin_out & p2,
   pin_out & p3,
   pin_out & p4,
   pin_out & p5,
   pin_out & p6,
   pin_out & p7,
   pin_out & p8,
   pin_out & p9,
   pin_out & p10,
   pin_out & p11,
   pin_out & p12,
   pin_out & p13,
   pin_out & p14,
   pin_out & p15
){   
   return all_from_pin_out(
      p0,
	  p1,
	  p2,
	  p3,
	  p4,
	  p5,
	  p6,
	  p7,
	  p8,
	  p9,
	  p10,
	  p11,
	  p12,
	  p13,
	  p14,
	  p15
   );
}   

#endif

}; // namespace hwlib
