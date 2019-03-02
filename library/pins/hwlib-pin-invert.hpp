// ==========================================================================
//
// File      : hwlib-pin-invert.hpp
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

/// inverse of a pin_out
///
/// The preferred way to use this class is through the overloaded 
/// constructor function invert().
class pin_invert_from_out_t : public pin_out {
private:
	
   pin_out & slave;
   
public:

   /// construct from a pin_out
   pin_invert_from_out_t( pin_out & slave ): slave( slave ){}
   
   void write( bool x ){
      slave.write( !x );
   }	

   void flush() override {
      slave.flush();            
   }
   
};	


// ==========================================================================
//
// pin_in
//
// ==========================================================================

/// inverse of a pin_in
///
/// The preferred way to use this class is through the overloaded 
/// constructor function invert().
class pin_invert_from_in_t : public pin_in {
private:
	
   pin_in & slave;
   
public:

   /// construct from a pin_in
   pin_invert_from_in_t( pin_in & slave ): slave( slave ){}
   
   bool read(){
      return ! slave.read();
   }	

   void refresh() override {
      slave.refresh();            
   }
   
};	


// ==========================================================================
//
// pin_in_out
//
// ==========================================================================

/// inverse of a pin_in_out
///
/// The preferred way to use this class is through the overloaded 
/// constructor function invert().
class pin_invert_from_in_out_t : public pin_in_out {
private:
	
   pin_in_out & slave;
   
public:

   /// construct from a pin_in_out
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

   void direction_flush() override {
      slave.direction_flush();       
   }

};	


// ==========================================================================
//
// pin_oc
//
// ==========================================================================

/// inverse of a pin_oc
///
/// The preferred way to use this class is through the overloaded 
/// constructor function invert().
class pin_invert_from_oc_t : public pin_oc {
private:
	
   pin_oc & slave;
   
public:

   /// construct from a pin_oc
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


// ===========================================================================
//
// constructor functions
//
// ===========================================================================

/// return the inverse of a pin
///@{ 
pin_invert_from_oc_t      invert( pin_oc & p );
pin_invert_from_in_out_t  invert( pin_in_out & p );
pin_invert_from_out_t     invert( pin_out & p );
pin_invert_from_in_t      invert( pin_in & p );
///@}


// ===========================================================================
//
// implementations
//
// ===========================================================================

#ifdef _HWLIB_ONCE

pin_invert_from_out_t invert( pin_out & p ){
   return pin_invert_from_out_t( p );
}   

pin_invert_from_in_t invert( pin_in & p ){
   return pin_invert_from_in_t( p );
}   

pin_invert_from_in_out_t invert( pin_in_out & p ){
   return pin_invert_from_in_out_t( p );
}   

pin_invert_from_oc_t invert( pin_oc & p ){
   return pin_invert_from_oc_t( p );
}   

#endif // _HWLIB_ONCE

}; // namespace hwlib
