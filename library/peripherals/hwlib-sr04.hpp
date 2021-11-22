// ==========================================================================
//
// File      : hwlib-sr04.hpp
// Part of   : C++ hwlib library for close-to-the-hardware OO programming
// Copyright : wouter@voti.nl 2016-2019
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
   
class sr04 {    
private:
   pin_out & trigger;
   pin_in & echo;
   
public:

   sr04( pin_out & trigger, pin_in & echo ):
       trigger( trigger ), echo( echo )
   {
      trigger.write( 0 );trigger.flush();
   }
   
   int read_cm( int max_distance = 400 ){
      echo.refresh();
      if( echo.read() == 1 ){
         return max_distance;
      }    
       
      trigger.write( 1 );trigger.flush();
      wait_us( 10 );
      trigger.write( 0 );trigger.flush();
      
      // wait for start of high pulse
      for( 
         auto start = now_us(); 
         echo.refresh(), echo.read() == 0;
      ){
         if( ( now_us() - start ) > 1'000 ){
            return max_distance;
         }
      }
      
      // measure high pulse length
      for( 
         auto start = now_us(); 
         ( now_us() - start ) < (long long unsigned) max_distance * 58; 
      ){
         echo.refresh();
         if( echo.read() == 0 ){
             return ( hwlib::now_us() - start ) / 58;
         }
      }
      return max_distance;
   }
   
}; // class sr04
   
}; // namespace hwlib
