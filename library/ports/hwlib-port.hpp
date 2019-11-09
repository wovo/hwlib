// ==========================================================================
//
// File      : hwlib-port.hpp
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
// input / output port
//
// ==========================================================================


/// input / output port interface
/// 
/// This is the interface of an input / output port.
class port_in_out : public noncopyable {
public:

   /// get number of pins
   /// 
   /// This function returns the number of pins in the port.
   virtual uint_fast8_t number_of_pins() = 0;
   
   /// set the direction of the port to input.
   /// 
   /// Calling this function sets all pins of the port to input.
   virtual void direction_set_input() = 0;   
   
   /// read from the port
   /// 
   /// This function reads and returns the pins that are part of the port.
   /// The lowest bit of the result reflects the first pin of the port, etc.
   ///
   /// Before calling this function the port direction must have been 
   /// set to input by calling port_direction_set_input().     
   virtual uint_fast16_t read() = 0;         
   
   /// refresh the port buffer
   /// 
   /// This function refreshed the contents of the read buffer that might
   /// be used by get_buffered() with a value read from the pins. 
   ///
   /// The read buffer might also be refreshed as a side-effect of 
   /// other operations.
   virtual void refresh() = 0;

   /// set the direction of the port to output
   /// 
   /// Calling this function sets all pins of the port to output.
   virtual void direction_set_output() = 0;

   /// write to the port
   /// 
   /// This function writes to the pins that are part of the port.
   /// The lowest bit is written to the first pin of the port, etc.
   ///
   /// Before calling this function the port direction must have been 
   /// set to output by calling direction_set_output().    
   virtual void write( uint_fast16_t x ) = 0;     
   
   /// flush the port buffer
   /// 
   /// This function flushes the port write buffer: if a buffered value
   /// has not yet been written it is written to the pin.
   /// When the value has been written, it might be written again.
   ///
   /// The pin write buffer might also be flushed as a side-effect of 
   /// other operations.
   virtual void flush() = 0;  
   
   /// flush the direction
   ///
   /// Calling this function flushes the direction as set by the last
   /// call to direction_set_input() or direction_set_output() to the port.
   virtual void direction_flush() = 0;

};
   
   
// ==========================================================================
//
// input port
//
// ==========================================================================

/// input port interface
/// 
/// This is the interface of an input-only port.
class port_in : public noncopyable {
public:

   /// @copydoc port_in_out::number_of_pins()
   virtual uint_fast8_t number_of_pins() = 0;
   
   /// @copydoc port_in_out::read()
   virtual uint_fast16_t read() = 0; 

   /// @copydoc port_in_out::refresh()
   virtual void refresh() = 0;

};


// ==========================================================================
//
// output port
//
// ==========================================================================

/// output port interface
/// 
/// This is the interface of an output-only port.
class port_out : public noncopyable {
public:

   /// @copydoc port_in_out::number_of_pins()
   virtual uint_fast8_t number_of_pins() = 0;
   
   /// @copydoc port_in_out::write( uint_fast8_t x )
   virtual void write( uint_fast16_t x ) = 0;     
   
   /// @copydoc port_in_out::flush()
   virtual void flush() = 0;      

};


// ==========================================================================
//
// oc port
//
// ==========================================================================

/// open-collector interface
/// 
/// This is the interface of an open-collector port.
class port_oc : public noncopyable {
public:

   /// @copydoc port_in_out::number_of_pins()
   virtual uint_fast8_t number_of_pins() = 0;   
   
   /// @copydoc port_in_out::read()
   virtual uint_fast16_t read() = 0;      

   /// @copydoc port_in_out::write() 
   virtual void write( uint_fast16_t x ) = 0;     

   /// @copydoc port_in_out::refresh()
   virtual void refresh() = 0;   
   
   /// @copydoc port_in_out::flush()
   virtual void flush() = 0;      

};

}; // namespace hwlib
