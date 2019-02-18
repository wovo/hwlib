// ==========================================================================
//
// File      : hwlib-port-decorators.hpp
// Part of   : C++ hwlib library for close-to-the-hardware OO programming
// Copyright : wouter@voti.nl 2017
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
/// \brief
/// invert an input/input port
/// \details
/// This decorator inverts the result 
/// of read and write operations on an input port:
/// - When a value would be returned by the original port, the
///   inverted port returns the value with all bits inverted.
/// - When a value is written to the inverted output port, the
/// inverse of that value is written to the original port.
//
// ==========================================================================

class port_in_out_invert : public port_in_out {
private:
   port_in_out & port;
   
public:

   /// \brief
   /// construct an inverted input/output port
   /// \details
   /// This constructor creates an inverted input/output port from an
   /// existing input/output port.
   port_in_out_invert( port_in_out & port ): 
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
   
   uint_fast8_t read() override {
      return port.read() ^ -1;      
   }   
   
   void refresh() override {
      return port.refresh();      
   }   
   
   void write( uint_fast8_t x ) override {
      port.write( x ^ -1 );
   }
   
   void flush() override {
      return port.flush();      
   }     
   
};


// ==========================================================================
//  
/// \brief
/// invert an input port
/// \details
/// This decorator inverts the result 
/// of read operations on an input port:
/// When a value would be returned by the original port, the
/// inverted port returns the value with all bits inverted.
//
// ==========================================================================

class port_in_invert : public port_in {
private:
   port_in & port;
   
public:

   /// \brief
   /// construct an inverted input port
   /// \details
   /// This constructor creates an inverted input port from an
   /// existing input port.
   port_in_invert( port_in & port ): 
      port( port ){}

   uint_fast8_t number_of_pins() override {
      return port.number_of_pins();               
   }  
   
   uint_fast8_t read() override {
      return port.read() ^ -1;      
   }   
  
   void refresh() override {
      port.refresh();      
   }   
   
};


// ==========================================================================
//  
/// \brief
/// invert an output port
/// \details
/// This decorator inverts the effect 
/// of write operations to an output port:
/// When a value is written to this inverted output port, the
/// inverse of that value is written to the original port.
// ==========================================================================

class port_out_invert : public port_out {
private:
   port_out & port;
   
public:

   /// \brief
   /// construct an inverted output port
   /// \details
   /// This constructor creates an inverted output port from an
   /// existing output port.
   port_out_invert( port_out &port ): 
      port( port ){}

   uint_fast8_t number_of_pins() override {
      return port.number_of_pins();               
   }  
   
   void write( uint_fast8_t x ) override {
      port.write( x ^ -1 );      
   }   
   
   void flush() override {
      port.flush();      
   }      
   
};


// ==========================================================================
//  
/// \brief
/// invert an open-collector port
/// \details
/// This decorator inverts the result 
/// of read and write operations on an input port:
/// - When a value would be returned by the original port, the
///   inverted port returns the value with all bits inverted.
/// - When a value is written to the inverted output port, the
/// inverse of that value is written to the original port.
// ==========================================================================

class port_oc_invert : public port_oc {
private:
   port_oc & port;
   
public:

   /// \brief
   /// construct an inverted open-collector port
   /// \details
   /// This constructor creates an inverted open-collector port from an
   /// existing open-collector port.
   port_oc_invert( port_oc & port ): 
      port( port ){}    

   uint_fast8_t number_of_pins() override {
      return port.number_of_pins();               
   }  
   
   uint_fast8_t read() override {
      return port.read() ^ -1;      
   }   
   
   void refresh() override {
      return port.refresh();      
   }      
   
   void write( uint_fast8_t x ) override {
      port.write( x ^ -1 );
   }
   
   void flush() override {
      return port.flush();      
   }     
};

}; // namespace hwlib
