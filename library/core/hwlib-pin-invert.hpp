// ==========================================================================
//
// File      : hwlib-pin-invert.hpp
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
	

// ==========================================================================
//
// pin_out
//
// ==========================================================================

/// inverse of a pin_out
class pin_invert_from_out_t : public pin_out {
   pin_out & slave;
   
public:
   pin_invert_from_out_t( pin_out & slave ): slave( slave ){}
   
   void write( bool x ){
      slave.write( !x );
   }	

   void flush() override {
      slave.flush();            
   }
};	

/// return the inverse of a pin_out
pin_invert_from_out_t invert( pin_out & p );

#ifdef HWLIB_ONCE

pin_invert_from_out_t invert( pin_out & p ){
   return pin_invert_from_out_t( p );
}   

#endif


// ==========================================================================
//
// pin_in
//
// ==========================================================================

/// inverse of a pin_in
class pin_invert_from_in_t : public pin_in {
   pin_in & slave;
   
public:
   pin_invert_from_in_t( pin_in & slave ): slave( slave ){}
   
   bool read(){
      return ! slave.read();
   }	

   void refresh() override {
      slave.refresh();            
   }
};	

/// return the inverse of a pin_in
pin_invert_from_in_t      invert( pin_in & p );

#ifdef HWLIB_ONCE

pin_invert_from_in_t invert( pin_in & p ){
   return pin_invert_from_in_t( p );
}   

#endif


// ==========================================================================
//
// pin_in_out
//
// ==========================================================================

/// inverse of a pin_in_out
class pin_invert_from_in_out_t : public pin_in_out {
   pin_in_out & slave;
   
public:
   pin_invert_from_in_out_t( pin_in_out & slave ): slave( slave ){}
   
   bool read(){
      return ! slave.read();
   }	
   
   void write( bool x ){
      slave.write( !x );
   }	

   void direction_set_input() override {
      slave.direction_set_input();	   
   }

   void direction_set_output() override {
      slave.direction_set_output();	   
   }

   void refresh() override {
      slave.refresh();            
   }
   
   void flush() override {
      slave.flush();            
   }
};	

/// return the inverse of a pin_in_out
pin_invert_from_in_out_t  invert( pin_in_out & p );

#ifdef HWLIB_ONCE

pin_invert_from_in_out_t invert( pin_in_out & p ){
   return pin_invert_from_in_out_t( p );
}   

#endif


// ==========================================================================
//
// pin_oc
//
// ==========================================================================

/// inverse of a pin_oc
class pin_invert_from_oc_t : public pin_oc {
   pin_oc & slave;
   
public:
   pin_invert_from_oc_t( pin_oc & slave ): slave( slave ){}
   
   bool read(){
      return ! slave.read();
   }	
   
   void write( bool x ){
      slave.write( !x );
   }	

   void refresh() override {
      slave.refresh();            
   }
   
   void flush() override {
      slave.flush();            
   }
};	

/// return the inverse of a pin_oc
pin_invert_from_oc_t      invert( pin_oc & p );

#ifdef HWLIB_ONCE

pin_invert_from_oc_t invert( pin_oc & p ){
   return pin_invert_from_oc_t( p );
}   

#endif

}; // namespace hwlib
