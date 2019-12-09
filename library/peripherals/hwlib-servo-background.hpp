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
   
/// servo implemented by background processing   
///
/// This is a servo, implemented by background processing.
class servo_background : 
   public servo, 
   private hwlib::background 
{ 
private:
   hwlib::pin_out & pin;    
   uint64_t next_pulse;
   uint64_t pulse_end;
   bool use_busy_waiting;
   bool pulse_active;
   int_fast16_t pulse_us;	   
   
   void work() override {
      
      // time for the next pulse has arrived
      if( hwlib::now_us() > next_pulse ){
         next_pulse += 20'000;
         
         if( use_busy_waiting ){
            // output the pulse (busy-wait mode)
            pin.write( 1 );
            hwlib::wait_us_busy( pulse_us );
            pin.write( 0 );
            
         } else {
            // start the pulse (run-to-completion mode)
            pin.write( 1 );
            pulse_end = hwlib::now_us() + pulse_us;  
            pulse_active = true;
         }
      }
      
      // terminate pulse in run-to-completion mode
      if( ( ! use_busy_waiting ) && pulse_active ){
         if( hwlib::now_us() > pulse_end ){
             pin.write( 0 );           
             pulse_active = false;
         } 
      }          
   }   
   
public:    

   // must be present for a servo implementation
   void write_us( int_fast16_t t ) override {     
      pulse_us = t;
   }

   /// create a servo served by background processing
   ///
   /// Construct a servo from the output pin, the servo
   //. properties, and a busy-wait flag.
   ///
   /// It writes a pulse to servo each 20 ms.
   ///
   /// During the pulse, it can either 
   ///    - use busy busy waiting, which
   ///      will block other background processing 
   ///      for the duration of the pulse;
   ///    - return and wait for the next activation,
   ///      which will cause jitter when the application
   ///      spends significant time without calling
   ///      a (non-busy) wait function.
   /// The default is to use busy waiting.
   servo_background( 
      hwlib::pin_out & pin,
      const servo_properties & properties = servo_properties(),
      bool use_busy_waiting = true
   ):
      servo( properties ),
      pin( pin ),
      next_pulse( hwlib::now_us() ),
      pulse_end( 0 ),
      use_busy_waiting( use_busy_waiting ),
      pulse_active( false )
   {}
      
};
   
}; // namespace hwlib
