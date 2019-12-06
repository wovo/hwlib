// ==========================================================================
//
// File      : hwlib-servo-background.hpp
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
   
class servo_background : 
   public servo, 
   private hwlib::background 
{ 
private:
   hwlib::pin_out & pin;    
   uint64_t next_pulse;
   virtual void dummy() override {}
   
public:    

   servo_background( 
      hwlib::pin_out & pin,
      const servo_properties & properties = servo_properties()     
   ):
      servo( properties ),
      pin( pin ),
      next_pulse( hwlib::now_us() )
   {}
      
   void work() override {
      if( hwlib::now_us() > next_pulse ){
         next_pulse += 20'000;
         pin.write( 1 );
         hwlib::wait_us_busy( pulse_us );
         pin.write( 0 );
      }
   }

};

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
   
}; // namespace hwlib
