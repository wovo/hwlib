// ==========================================================================
//
// File      : hwlib-port.hpp
// Part of   : hwlib library for V1OOPC and V1IPAS
// Copyright : wouter@voti.nl 2016
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================
/// @file

#ifndef HWLIB_PORT_H
#define HWLIB_PORT_H

#include "hwlib-pin.hpp"
#include "hwlib-pin-dummies.hpp"
#include "hwlib-wait.hpp"

namespace hwlib {
   
// ==========================================================================
//
// input port
//
// ==========================================================================

/// input port interface
//
/// This is the interface of an input-only port.
class port_in {
 public:

   /// get number of pins
   //
   /// This function returns the number of pins in the port.
   virtual uint_fast8_t number_of_pins() = 0;
   
   /// read from the port
   //
   /// This function reads and returns the pins that are part of the port, 
   /// which might be be from a read buffer.
   /// The lowest bit of the result reflects the first pin of the port, etc.
   virtual uint_fast8_t get() = 0;         

   /// read from the port buffer
   //
   /// This function reads and returns the pins that are part of the port.
   /// The lowest bit of the result reflects the first pin of the port, etc.
   virtual uint_fast8_t get_buffered() = 0;     

   
   /// refresh the port buffer
   //
   /// This function refreshed the contents of the read buffer that might
   /// be used by get_buffered() with a value read from the pins. 
   ///
   /// The read buffer might also be refreshed as a side-effect of 
   /// other operations.
   virtual void refresh(){ }

};

/// input port from input pins
//
/// This class implements an input-only port made from port up to 8 pins.
class port_in_from_pins : public port_in {
private:
   
   uint_fast8_t _number_of_pins;  

   // 8 must match the number of parameters of the constructor
   pin_in * pins[ 8 ];   
   
public:

   /// construct a port_out from up to 8 pin_outs
   //
   /// This constructor creates a port_out from up to 8 pin_in pins.
   /// The first pin is the lowest pin in the port, etc.
   port_in_from_pins(
      pin_in & p0 = pin_in_dummy,
      pin_in & p1 = pin_in_dummy,
      pin_in & p2 = pin_in_dummy,
      pin_in & p3 = pin_in_dummy,
      pin_in & p4 = pin_in_dummy,
      pin_in & p5 = pin_in_dummy,
      pin_in & p6 = pin_in_dummy,
      pin_in & p7 = pin_in_dummy
   ):
      pins{ &p0, &p1, &p2, &p3, &p4, &p5, &p6, &p7 }
   {
      for( _number_of_pins = 0; _number_of_pins < 8; ++_number_of_pins ){
         if( pins[ _number_of_pins ] == & pin_in_dummy ){
             break;
         }            
      }
   }            

   uint_fast8_t number_of_pins() override {
      return _number_of_pins;               
   }   
   
   uint_fast8_t get() override {
      uint_fast8_t result = 0;
      for( uint_fast8_t i = _number_of_pins -1; i >=0; --i ){
         result = result << 1;
         if( pins[ i ]->get() ){
            result |= 0x01;            
         }
       }         
       return result;
   }

};

/// invert an input port
//
/// This decorator inverts the result 
/// of read operations on an input port:
/// When a value would be returned by the original port, the
/// inverted port returns the value with all bits inverted.
class port_in_invert : public port_in {
private:
   port_in & port;
   
public:

   /// construct an inverted input port
   //
   /// This constructor creates an inverted input port from an
   /// existing input port.
   port_in_invert( port_in & port ): 
      port( port ){}

   uint_fast8_t number_of_pins() override {
      return port.number_of_pins();               
   }  
   
   uint_fast8_t get() override {
      return port.get() ^ -1;      
   }   
   
   uint_fast8_t get_buffered() override {
      return port.get_buffered() ^ -1;      
   }   
  
   void refresh() override {
      port.refresh();      
   }   
   
};


// ==========================================================================
//
// output port
//
// ==========================================================================

/// output port interface
//
/// This is the interface of an output-only port.
class port_out {
 public:

   /// get number of pins
   //
   /// This function returns the number of pins in the port.
   virtual uint_fast8_t number_of_pins() = 0;
   
   /// write to the port
   //
   /// This function writes to the pins that are part of the port.
   /// The lowest bit is written to the first pin of the port, etc.   
   virtual void set( uint_fast8_t x ) = 0;     

   /// write to the port buffer
   //
   /// This function writes to the port buffer.
   /// This might write the buffered values to the pins.
   virtual void set_buffered( uint_fast8_t x ) = 0;
   
   /// flush the port buffer
   //
   /// This function flushes the port write buffer: if a buffered value
   /// has not yet been written it is written to the pin.
   /// When the value has been written, it might be written again.
   ///
   /// The pin write buffer might also be flushed as a side-effect of 
   /// other operations.
   virtual void flush(){ }      

};

/// output port from output pins
//
/// This class implements an output-only port made from port up to 8 pins.
class port_out_from_pins : public port_out {
private:
   
   uint_fast8_t _number_of_pins;  

   // 8 must match the number of parameters of the constructor
   pin_out * pins[ 8 ];   
   
public:

   /// construct a port_out from up to 8 pin_outs
   //
   /// This constructor creates a port_out from up to 8 pin_out pins.
   /// The first pin is the lowest pin in the port, etc.
   port_out_from_pins(
      pin_out & p0 = pin_out_dummy,
      pin_out & p1 = pin_out_dummy,
      pin_out & p2 = pin_out_dummy,
      pin_out & p3 = pin_out_dummy,
      pin_out & p4 = pin_out_dummy,
      pin_out & p5 = pin_out_dummy,
      pin_out & p6 = pin_out_dummy,
      pin_out & p7 = pin_out_dummy
   ):
      pins{ &p0, &p1, &p2, &p3, &p4, &p5, &p6, &p7 }
   {
      for( _number_of_pins = 0; _number_of_pins < 8; ++_number_of_pins ){
         if( pins[ _number_of_pins ] == & pin_out_dummy ){
             break;
         }            
      }
   }            

   uint_fast8_t number_of_pins() override {
      return _number_of_pins;               
   }   
   
   void set( uint_fast8_t x ) override {
      for( uint_fast8_t i = 0; i < _number_of_pins; i++ ){
         pins[ i ]->set( ( x & 0x01 ) != 0 );
         x = x >> 1;
      }         
   }

};

/// invert an output port
//
/// This decorator inverts the effect 
/// of write operations to an output port:
/// When a value is written to this inverted output port, the
/// inverse of that value is written to the original port.
class port_out_invert : public port_out {
private:
   port_out & port;
   
public:

   /// construct an inverted output port
   //
   /// This constructor creates an inverted output port from an
   /// existing output port.
   port_out_invert( port_out &port ): 
      port( port ){}

   uint_fast8_t number_of_pins() override {
      return port.number_of_pins();               
   }  
   
   void set( uint_fast8_t x ) override {
      port.set( x ^ -1 );      
   }   
   
   void set_buffered( uint_fast8_t x ) override { 
      port.set_buffered( x ^ -1 );
   }   
   
   void flush() override {
      port.flush();      
   }      
   
};


// ==========================================================================
//
// input / output port
//
// ==========================================================================

/// input / output port interface
//
/// This is the interface of an input / output port.
class port_in_out {
 public:

   /// get number of pins
   //
   /// This function returns the number of pins in the port.
   virtual uint_fast8_t number_of_pins() = 0;
   
   /// set the direction of the port to input.
   //
   /// Calling this function sets all pins of the port to input.
   virtual void direction_set_input() = 0;   
   
   /// read from the port
   //
   /// This function reads and returns the pins that are part of the port.
   /// The lowest bit of the result reflects the first pin of the port, etc.
   ///
   /// Before calling this function the port direction must have been 
   /// set to input by calling port_direction_set_input().     
   virtual uint_fast8_t get() = 0;     

   /// read from the port buffer
   //
   /// This function reads and returns the pins that are part of the port.
   /// The lowest bit of the result reflects the first pin of the port, etc.
   virtual uint_fast8_t get_buffered() = 0;     
   
   /// refresh the port buffer
   //
   /// This function refreshed the contents of the read buffer that might
   /// be used by get_buffered() with a value read from the pins. 
   ///
   /// The read buffer might also be refreshed as a side-effect of 
   /// other operations.
   virtual void refresh(){ }

   /// set the direction of the port to output
   //
   /// Calling this function sets all pins of the port to output.
   virtual void direction_set_output() = 0;

   /// write to the port
   //
   /// This function writes to the pins that are part of the port.
   /// The lowest bit is written to the first pin of the port, etc.
   ///
   /// Before calling this function the port direction must have been 
   /// set to output by calling direction_set_output().    
   virtual void set( uint_fast8_t x ) = 0;     

      /// write to the port buffer
   //
   /// This function writes to the port buffer.
   /// This might write the buffered values to the pins.
   virtual void set_buffered( uint_fast8_t x ) = 0;
   
   /// flush the port buffer
   //
   /// This function flushes the port write buffer: if a buffered value
   /// has not yet been written it is written to the pin.
   /// When the value has been written, it might be written again.
   ///
   /// The pin write buffer might also be flushed as a side-effect of 
   /// other operations.
   virtual void flush(){ }      

};


/// input/output port from input/output pins
//
/// This class implements an input-only port made from port up to 8 pins.
class port_in_out_from_pins : public port_in_out {
private:
   
   uint_fast8_t _number_of_pins;  

   // 8 must match the number of parameters of the constructor
   pin_in_out * pins[ 8 ];   
   
public:

   /// construct a port_out from up to 8 pin_outs
   //
   /// This constructor creates a port_out from up to 8 pin_in pins.
   /// The first pin is the lowest pin in the port, etc.
   port_in_out_from_pins(
      pin_in_out & p0 = pin_in_out_dummy,
      pin_in_out & p1 = pin_in_out_dummy,
      pin_in_out & p2 = pin_in_out_dummy,
      pin_in_out & p3 = pin_in_out_dummy,
      pin_in_out & p4 = pin_in_out_dummy,
      pin_in_out & p5 = pin_in_out_dummy,
      pin_in_out & p6 = pin_in_out_dummy,
      pin_in_out & p7 = pin_in_out_dummy
   ):
      pins{ &p0, &p1, &p2, &p3, &p4, &p5, &p6, &p7 }
   {
      for( _number_of_pins = 0; _number_of_pins < 8; ++_number_of_pins ){
         if( pins[ _number_of_pins ] == & pin_in_out_dummy ){
             break;
         }            
      }
   }            

   uint_fast8_t number_of_pins() override {
      return _number_of_pins;               
   }   
   
   void direction_set_input() override {
      for( uint_fast8_t i = 0; i < _number_of_pins; i++ ){
         pins[ i ]->direction_set_input();
      }
   }
   
    void direction_set_output() override {
      for( uint_fast8_t i = 0; i < _number_of_pins; i++ ){
         pins[ i ]->direction_set_output();
      }
   }
   
   uint_fast8_t get() override {
      uint_fast8_t result = 0;
      for( uint_fast8_t i = _number_of_pins -1; i >=0; --i ){
         result = result << 1;
         if( pins[ i ]->get() ){
            result |= 0x01;            
         }
       }         
       return result;
   }
   
   uint_fast8_t get_buffered() override {
      uint_fast8_t result = 0;
      for( uint_fast8_t i = _number_of_pins -1; i >=0; --i ){
         result = result << 1;
         if( pins[ i ]->get_buffered() ){
            result |= 0x01;            
         }
       }         
       return result;
   }
   
   void refresh() override {
      for( uint_fast8_t i = 0; i < _number_of_pins; i++ ){
         pins[ i ]->refresh();
      }         
   }      
   
   void set( uint_fast8_t x ) override {
      for( uint_fast8_t i = 0; i < _number_of_pins; i++ ){
         pins[ i ]->set( ( x & 0x01 ) != 0 );
         x = x >> 1;
      }         
   }   

   void set_buffered( uint_fast8_t x ) override {
      for( uint_fast8_t i = 0; i < _number_of_pins; i++ ){
         pins[ i ]->set_buffered( ( x & 0x01 ) != 0 );
         x = x >> 1;
      }         
   }   
  void flush() override {
      for( uint_fast8_t i = 0; i < _number_of_pins; i++ ){
         pins[ i ]->flush();
      }         
   }   

};

/// invert an input/input port
//
/// This decorator inverts the result 
/// of read and write operations on an input port:
/// - When a value would be returned by the original port, the
///   inverted port returns the value with all bits inverted.
/// - When a value is written to the inverted output port, the
/// inverse of that value is written to the original port.
class port_in_out_invert : public port_in_out {
private:
   port_in_out & port;
   
public:

   /// construct an inverted input/output port
   //
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
   
   uint_fast8_t get() override {
      return port.get() ^ -1;      
   }   
   
   uint_fast8_t get_buffered() override {
      return port.get_buffered() ^ -1;      
   }   
   
   void refresh() override {
      return port.refresh();      
   }   
   
   void set( uint_fast8_t x ) override {
      port.set( x ^ -1 );
   }
   
   void set_buffered( uint_fast8_t x ) override {
      port.set_buffered( x ^ -1 );
   }
   
   void flush() override {
      return port.flush();      
   }     
   
};

// ==========================================================================
//
// oc port
//
// ==========================================================================

/// open-collector interface
//
/// This is the interface of an open-collector port.
class port_oc {
 public:

   /// get number of pins
   //
   /// This function returns the number of pins in the port.
   virtual uint_fast8_t number_of_pins() = 0;   
   
   /// read from the port
   //
   /// This function reads and returns the pins that are part of the port.
   /// The lowest bit of the result reflects the first pin of the port, etc.
   ///
   /// Pins that have been written as 0 will very likley read as 0 too.
   /// To read the external input to a pin, 
   /// the pin must first be written as 1.
   virtual uint_fast8_t get() = 0;       

   /// read from the port buffer
   //
   /// This function reads and returns the pins that are part of the port.
   /// The lowest bit of the result reflects the first pin of the port, etc.
   virtual uint_fast8_t get_buffered() = 0;  

   /// write to the port
   //
   /// This function writes to the pins that are part of the port.
   /// The lowest bit is written to the first pin of the port, etc.  
   virtual void set( uint_fast8_t x ) = 0;    

   /// write to the port buffer
   //
   /// This function writes to the port buffer.
   /// This might write the buffered values to the pins.
   virtual void set_buffered( uint_fast8_t x ) = 0;
   
   /// refresh the port buffer
   //
   /// This function refreshed the contents of the read buffer that might
   /// be used by get_buffered() with a value read from the pins. 
   ///
   /// The read buffer might also be refreshed as a side-effect of 
   /// other operations.
   virtual void refresh(){ }   
   
   /// flush the port buffer
   //
   /// This function flushes the port write buffer: if a buffered value
   /// has not yet been written it is written to the pin.
   /// When the value has been written, it might be written again.
   ///
   /// The pin write buffer might also be flushed as a side-effect of 
   /// other operations.
   virtual void flush(){ }      

};


/// invert an open-collector port
//
/// This decorator inverts the result 
/// of read and write operations on an input port:
/// - When a value would be returned by the original port, the
///   inverted port returns the value with all bits inverted.
/// - When a value is written to the inverted output port, the
/// inverse of that value is written to the original port.
class port_oc_invert : public port_oc {
private:
   port_oc & port;
   
public:

   /// construct an inverted open-collector port
   //
   /// This constructor creates an inverted open-collector port from an
   /// existing open-collector port.
   port_oc_invert( port_oc & port ): 
      port( port ){}    

   uint_fast8_t number_of_pins() override {
      return port.number_of_pins();               
   }  
   
   uint_fast8_t get() override {
      return port.get() ^ -1;      
   }   
   
   uint_fast8_t get_buffered() override {
      return port.get_buffered() ^ -1;      
   }   
   
   void refresh() override {
      return port.refresh();      
   }      
   
   void set( uint_fast8_t x ) override {
      port.set( x ^ -1 );
   }
   
   void set_buffered( uint_fast8_t x ) override {
      port.set_buffered( x ^ -1 );
   }
   
   void flush() override {
      return port.flush();      
   }     
};

}; // namespace hwlib

#endif // HWLIB_PORT_H