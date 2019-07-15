// ==========================================================================
//
// File      : hwlib-lol-shield.hpp
// Part of   : C++ hwlib library for close-to-the-hardware OO programming
// Copyright : wouter@voti.nl 2019
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
	
class lol_shield : public window {	
private:

   bool buffer[ 9 ][ 14 ];
   
   void write_implementation( 
      xy pos, 
      color col
   ) override {

      buffer[ x ][ y ] = ( col == white );
   }  
	   
public:	

   lol_shield( ):
      window( pos( 9, 14 ),
   {
   }
   
   void poll(){
   for    	   
   }
    

}; // class lol_shield

}; // namespace hwlib
