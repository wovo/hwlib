// ==========================================================================
//
// File      : hwlib-pin-direct.hpp
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
	
	
// ==========================================================================
//
// pin_in_out
//
// ==========================================================================	
	
/// a direct-effect pin_in_out 
///
/// This is a version of pin_in_out where the various operations
/// have direct (immediate) effect: no refresh or flush calls needed.
/// This have a negative effect on the execution time.
///
/// The preferred way to use this class is through the overloaded 
/// constructor function direct().
class pin_direct_from_in_out_t : public pin_in_out {
private:

   pin_in_out & slave;	
	
public:

   /// construct from a pin_in_out
   pin_direct_from_in_out_t( pin_in_out & slave ): slave( slave ){}

   void write( bool v ) override {
      slave.write( v );
      slave.flush();
   }
   
   bool read() override { 
      slave.refresh();
      return slave.read();
   }
   
   void direction_set_input() override {
      slave.direction_set_input();
      slave.direction_flush();	  
   }
   
   void direction_set_output() override {
      slave.direction_set_output();
      slave.direction_flush();	 
   }
   
   void flush() override {
   }
   
   void refresh() override {  
   }
   
   void direction_flush() override {
   }
   
};  


// ==========================================================================
//
// pin_in
//
// ==========================================================================

/// a direct-effect pin_in
///
/// This is a version of pin_in where the various operations
/// have direct (immediate) effect: no refresh calls needed.
/// This have a negative effect on the execution time.
///
/// The preferred way to use this class is through the overloaded 
/// constructor function direct().
class pin_direct_from_in_t : public pin_in {
private:

   pin_in & slave;	
	
public:

   /// construct from a pin_in
   pin_direct_from_in_t( pin_in & slave ): slave( slave ){}
  
   bool read() override { 
      slave.refresh();
      return slave.read();
   }
     
   void refresh() override {  
   }
   
};  


// ==========================================================================
//
// pin_out
//
// ==========================================================================

/// a direct-effect pin_out 
///
/// This is a version of pin_out where the various operations
/// have direct (immediate) effect: no flush calls needed.
/// This have a negative effect on the execution time.
///
/// The preferred way to use this class is through the overloaded 
/// constructor function direct().
class pin_direct_from_out_t : public pin_out {
private:

   pin_out & slave;	
	
public:

   /// construct from a pin_out
   pin_direct_from_out_t( pin_out & slave ): slave( slave ){}

   void write( bool v ) override {
      slave.write( v );
	   slave.flush();
   }
      
   void flush() override {
   }
   
};  


// ==========================================================================
//
// pin_oc
//
// ==========================================================================

/// a direct-effect pin_oc
///
/// This is a version of pin_in_out where the various operations
/// have direct (immediate) effect: no refresh or flush calls needed.
/// This have a negative effect on the execution time.
///
/// The preferred way to use this class is through the overloaded 
/// constructor function direct().
class pin_direct_from_oc_t : public pin_oc {
private:

   pin_oc & slave;	
	
public:

   /// construct from a pin_oc
   pin_direct_from_oc_t( pin_oc & slave ): slave( slave ){}

   void write( bool v ) override {
      slave.write( v );
	  slave.flush();
   }
   
   bool read() override { 
      slave.refresh();
      return slave.read();
   }
      
   void flush() override {
   }
   
   void refresh() override {  
   }
   
};  


// ===========================================================================
//
// constructor functions
//
// ===========================================================================

/// return the direct-acting version of a pin
///@{ 
pin_direct_from_oc_t      direct( pin_oc & p );
pin_direct_from_in_out_t  direct( pin_in_out & p );
pin_direct_from_out_t     direct( pin_out & p );
pin_direct_from_in_t      direct( pin_in & p );
///@}


// ===========================================================================
//
// implementations
//
// ===========================================================================

#ifdef _HWLIB_ONCE

pin_direct_from_out_t direct( pin_out & p ){
   return pin_direct_from_out_t( p );
}   

pin_direct_from_in_t direct( pin_in & p ){
   return pin_direct_from_in_t( p );
}   

pin_direct_from_in_out_t direct( pin_in_out & p ){
   return pin_direct_from_in_out_t( p );
}   

pin_direct_from_oc_t direct( pin_oc & p ){
   return pin_direct_from_oc_t( p );
}   

#endif // _HWLIB_ONCE

}; // namespace hwlib
