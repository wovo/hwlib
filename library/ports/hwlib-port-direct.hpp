// ==========================================================================
//
// File      : hwlib-port-direct.hpp
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
// port_in_out
//
// ==========================================================================	
	
/// a direct-effect port_in_out 
///
/// This is a version of port_in_out where the various operations
/// have direct (immediate) effect: no refresh or flush calls needed.
/// This have a negative effect on the execution time.
///
/// The preferred way to use this class is through the overloaded 
/// constructor function direct().
class port_direct_from_in_out_t : public port_in_out {
private:

   port_in_out & slave;	
	
public:

   /// construct from a port_in_out
   port_direct_from_in_out_t( port_in_out & slave ): slave( slave ){}
   
   uint_fast8_t number_of_pins(){
      return slave.number_of_pins();
   }	  
   
   void write( uint_fast16_t  v ) override {
      slave.write( v );
      slave.flush();
   }
   
   uint_fast16_t read() override { 
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
// port_in
//
// ==========================================================================

/// a direct-effect port_in
///
/// This is a version of port_in where the various operations
/// have direct (immediate) effect: no refresh calls needed.
/// This have a negative effect on the execution time.
///
/// The preferred way to use this class is through the overloaded 
/// constructor function direct().
class port_direct_from_in_t : public port_in {
private:

   port_in & slave;	
	
public:

   /// construct from a port_in
   port_direct_from_in_t( port_in & slave ): slave( slave ){}
  
   uint_fast8_t number_of_pins(){
      return slave.number_of_pins();
   }	  
   
   uint_fast16_t  read() override { 
      slave.refresh();
      return slave.read();
   }
     
   void refresh() override {  
   }
   
};  


// ==========================================================================
//
// port_out
//
// ==========================================================================

/// a direct-effect port_out 
///
/// This is a version of port_out where the various operations
/// have direct (immediate) effect: no flush calls needed.
/// This have a negative effect on the execution time.
///
/// The preferred way to use this class is through the overloaded 
/// constructor function direct().
class port_direct_from_out_t : public port_out {
private:

   port_out & slave;	
	
public:

   /// construct from a port_out
   port_direct_from_out_t( port_out & slave ): slave( slave ){}

   uint_fast8_t number_of_pins(){
      return slave.number_of_pins();
   }	  
   
   void write( uint_fast16_t  v ) override {
      slave.write( v );
	  slave.flush();
   }
      
   void flush() override {
   }
   
};  


// ==========================================================================
//
// port_oc
//
// ==========================================================================

/// a direct-effect port_oc
///
/// This is a version of port_in_out where the various operations
/// have direct (immediate) effect: no refresh or flush calls needed.
/// This have a negative effect on the execution time.
///
/// The preferred way to use this class is through the overloaded 
/// constructor function direct().
class port_direct_from_oc_t : public port_oc {
private:

   port_oc & slave;	
	
public:

   /// construct from a port_oc
   port_direct_from_oc_t( port_oc & slave ): slave( slave ){}

   uint_fast8_t number_of_pins(){
      return slave.number_of_pins();
   }	  
   
   void write( uint_fast16_t  v ) override {
      slave.write( v );
	  slave.flush();
   }
   
   uint_fast16_t read() override { 
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

/// return the direct-acting of a port
///@{ 
port_direct_from_oc_t      direct( port_oc & p );
port_direct_from_in_out_t  direct( port_in_out & p );
port_direct_from_out_t     direct( port_out & p );
port_direct_from_in_t      direct( port_in & p );
///@}


// ===========================================================================
//
// implementations
//
// ===========================================================================

#ifdef _HWLIB_ONCE

port_direct_from_out_t direct( port_out & p ){
   return port_direct_from_out_t( p );
}   

port_direct_from_in_t direct( port_in & p ){
   return port_direct_from_in_t( p );
}   

port_direct_from_in_out_t direct( port_in_out & p ){
   return port_direct_from_in_out_t( p );
}   

port_direct_from_oc_t direct( port_oc & p ){
   return port_direct_from_oc_t( p );
}   

#endif // _HWLIB_ONCE

}; // namespace hwlib
