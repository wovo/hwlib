// ==========================================================================
//
// File      : hwlib-port-invert.hpp
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
// in_out
//
// ==========================================================================

/// invert an input/input port
///
/// This decorator class inverts the result 
/// of read and write operations on an input port:
/// - When a value would be returned by the original port, the
///   inverted port returns the value with all bits inverted.
/// - When a value is written to the inverted output port, the
/// inverse of that value is written to the original port.
class port_invert_from_in_out_t : public port_in_out {
private:

   port_in_out & port;
   
public:

   /// construct an inverted input/output port
   /// 
   /// This constructor creates an inverted input/output port from an
   /// existing input/output port.
   port_invert_from_in_out_t( port_in_out & port ): 
      port( port ){}
      
   void direction_set_input() override {
      port.direction_set_input();
   }
   
    void direction_set_output() override {
      port.direction_set_output();
   }      

   uint_fast8_t number_of_pins() override {
      return port.number_of_pins();               
   }  
   
   uint_fast16_t read() override {
      return port.read() ^ -1;      
   }   
   
   void refresh() override {
      return port.refresh();      
   }   
   
   void write( uint_fast16_t x ) override {
      port.write( x ^ -1 );
   }
   
   void flush() override {
      return port.flush();      
   }     
   
   void direction_flush() override {
      return port.direction_flush();      
   }     
   
};


// ==========================================================================
//  
// in
//
// ==========================================================================

/// invert an input port
/// 
/// This decorator inverts the result 
/// of read operations on an input port:
/// When a value would be returned by the original port, the
/// inverted port returns the value with all bits inverted.
class port_invert_from_in_t : public port_in {
private:

   port_in & port;
   
public:

   /// construct an inverted input port
   /// 
   /// This constructor creates an inverted input port from an
   /// existing input port.
   port_invert_from_in_t( port_in & port ): 
      port( port ){}

   uint_fast8_t number_of_pins() override {
      return port.number_of_pins();               
   }  
   
   uint_fast16_t read() override {
      return port.read() ^ -1;      
   }   
  
   void refresh() override {
      port.refresh();      
   }   
   
};


// ==========================================================================
//  
// out
//
// ==========================================================================

/// invert an output port
/// 
/// This decorator inverts the effect 
/// of write operations to an output port:
/// When a value is written to this inverted output port, the
/// inverse of that value is written to the original port.
class port_invert_from_out_t : public port_out {
private:

   port_out & port;
   
public:

   /// \brief
   /// construct an inverted output port
   /// \details
   /// This constructor creates an inverted output port from an
   /// existing output port.
   port_invert_from_out_t( port_out &port ): 
      port( port ){}

   uint_fast8_t number_of_pins() override {
      return port.number_of_pins();               
   }  
   
   void write( uint_fast16_t x ) override {
      port.write( x ^ -1 );      
   }   
   
   void flush() override {
      port.flush();      
   }      
   
};

// ==========================================================================
//  
// oc
//
// ==========================================================================

/// invert an open-collector port
/// 
/// This decorator inverts the result 
/// of read and write operations on an input port:
/// - When a value would be returned by the original port, the
///   inverted port returns the value with all bits inverted.
/// - When a value is written to the inverted output port, the
/// inverse of that value is written to the original port.
class port_invert_from_oc_t : public port_oc {
private:

   port_oc & port;
   
public:

   /// construct an inverted open-collector port
   /// 
   /// This constructor creates an inverted open-collector port from an
   /// existing open-collector port.
   port_invert_from_oc_t( port_oc & port ): 
      port( port ){}    

   uint_fast8_t number_of_pins() override {
      return port.number_of_pins();               
   }  
   
   uint_fast16_t read() override {
      return port.read() ^ -1;      
   }   
   
   void refresh() override {
      return port.refresh();      
   }      
   
   void write( uint_fast16_t x ) override {
      port.write( x ^ -1 );
   }
   
   void flush() override {
      return port.flush();      
   }     
};


// ===========================================================================
//
// constructor functions
//
// ===========================================================================

/// return the inverse of a port
///@{ 
port_invert_from_oc_t      invert( port_oc & p );
port_invert_from_in_out_t  invert( port_in_out & p );
port_invert_from_out_t     invert( port_out & p );
port_invert_from_in_t      invert( port_in & p );
///@}


// ===========================================================================
//
// implementations
//
// ===========================================================================

#ifdef _HWLIB_ONCE

port_invert_from_out_t invert( port_out & p ){
   return port_invert_from_out_t( p );
}   

port_invert_from_in_t invert( port_in & p ){
   return port_invert_from_in_t( p );
}   

port_invert_from_in_out_t invert( port_in_out & p ){
   return port_invert_from_in_out_t( p );
}   

port_invert_from_oc_t invert( port_oc & p ){
   return port_invert_from_oc_t( p );
}   

#endif // _HWLIB_ONCE

}; // namespace hwlib
