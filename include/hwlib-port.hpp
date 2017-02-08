// ==========================================================================
//
// File      : hwlib-port.hpp
// Part of   : C++ hwlib library for close-to-the-hardware OO programming
// Copyright : wouter@voti.nl 2017
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

// this file contains Doxygen lines
/// @file

#ifndef HWLIB_PORT_H
#define HWLIB_PORT_H

#include <stdint.h>

namespace hwlib {
   
    
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
   virtual uint_fast8_t get( 
      buffering buf = buffering::unbuffered 
   ) = 0;         
   
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
   virtual void set( 
      uint_fast8_t x, 
      buffering buf = buffering::unbuffered 
   ) = 0;     
   
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

   /// @copydoc port_in_out::number_of_pins()
   virtual uint_fast8_t number_of_pins() = 0;
   
   /// @copydoc port_in_out::get()
   virtual uint_fast8_t get( 
      buffering buf = buffering::unbuffered 
   ) = 0; 

   /// @copydoc port_in_out::refresh()
   virtual void refresh(){ }

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

   /// @copydoc port_in_out::number_of_pins()
   virtual uint_fast8_t number_of_pins() = 0;
   
   /// @copydoc port_in_out::set()
   virtual void set( 
      uint_fast8_t x, 
      buffering buf = buffering::unbuffered 
   ) = 0;     
   
   /// @copydoc port_in_out::flush()
   virtual void flush(){ }      

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

   /// @copydoc port_in_out::number_of_pins()
   virtual uint_fast8_t number_of_pins() = 0;   
   
   /// @copydoc port_in_out::get()
   virtual uint_fast8_t get( 
      buffering buf = buffering::unbuffered 
   ) = 0;      

   /// @copydoc port_in_out::set() 
   virtual void set( 
      uint_fast8_t x, 
      buffering buf = buffering::unbuffered 
   ) = 0;     

   /// @copydoc port_in_out::refresh()
   virtual void refresh(){ }   
   
   /// @copydoc port_in_out::flush()
   virtual void flush(){ }      

};

}; // namespace hwlib

#endif // HWLIB_PORT_H