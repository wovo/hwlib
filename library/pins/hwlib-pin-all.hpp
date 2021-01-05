// ==========================================================================
//
// File      : hwlib-pin-all.hpp
// Part of   : C++ hwlib library for close-to-the-hardware OO programming
// Copyright : wouter@voti.nl 2017-2019
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


// ==========================================================================
//
// pin_out
//
// ==========================================================================

/// class that writes to all its slave pins
class all_from_pin_out_t : public pin_out {
private:

   static constexpr int max_pins = 16;  
   pin_out * pins[ max_pins ];   
   
public:

   /// construct a port_out from up to 8 pin_outs
   /// 
   /// This constructor creates a port_out from up to 8 pin_out pins.
   /// The first pin is the lowest pin in the port, etc.
   all_from_pin_out_t(
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
   ):
      pins{ 
	     &p0,  &p1,  &p2,  &p3,  &p4,  &p5,  &p6,  &p7, 
        &p8,  &p9,  &p10, &p11, &p12, &p13, &p14, &p15 
      }{}            
   
   void write( bool x ) override {
      for( auto & pin : pins ){
         pin->write( x );
      }         
   }
   
   void flush() override {
      for( auto & pin : pins ){
         pin->flush();
      }                
   }

};


// ===========================================================================
//
// constructor functions
//
// ===========================================================================

/// return a pin that writes to all its slave pins
all_from_pin_out_t all( 
   pin_out & p0   = pin_out_dummy,
   pin_out & p1   = pin_out_dummy,
   pin_out & p2   = pin_out_dummy,
   pin_out & p3   = pin_out_dummy,
   pin_out & p4   = pin_out_dummy,
   pin_out & p5   = pin_out_dummy,
   pin_out & p6   = pin_out_dummy,
   pin_out & p7   = pin_out_dummy,
   pin_out & p8   = pin_out_dummy,
   pin_out & p9   = pin_out_dummy,
   pin_out & p10  = pin_out_dummy,
   pin_out & p11  = pin_out_dummy,
   pin_out & p12  = pin_out_dummy,
   pin_out & p13  = pin_out_dummy,
   pin_out & p14  = pin_out_dummy,
   pin_out & p15  = pin_out_dummy	
);


// ===========================================================================
//
// implementations
//
// ===========================================================================

#ifdef _HWLIB_ONCE

all_from_pin_out_t all( 
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
   return all_from_pin_out_t(
     p0,  p1,  p2,  p3,  p4,  p5,  p6,  p7,
     p8,  p9,  p10, p11, p12, p13, p14, p15
   );
}   

#endif // _HWLIB_ONCE

}; // namespace hwlib
