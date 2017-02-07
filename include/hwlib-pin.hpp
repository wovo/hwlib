// ==========================================================================
//
// File      : hwlib-pin.hpp
// Part of   : hwlib library for V1OOPC and V1IPAS
// Copyright : wouter@voti.nl 2016
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================
/// @file

#ifndef HWLIB_PIN_H
#define HWLIB_PIN_H

#include "hwlib-wait.hpp"

namespace hwlib {

/// input pin interface
//
/// This class abstracts the interface for an input-only pin.
class pin_in {
public:

   /// read the pin
   //
   /// This function returns the level of the pin.
   /// When the pin level is high the value true is returned,
   /// when the pin level is low the value false is returned.
   virtual bool get() = 0;
   
   /// read the pin buffer
   //
   /// This function returns the level of the pin, which might
   /// be be from a read buffer.
   /// When the pin level in the buffer is high the value true is returned,
   /// when the pin level in the buffer is low the value false is returned.
   virtual bool get_buffered(){ return get(); }

   /// refresh the pin buffer
   //
   /// This function refreshed the contents of the read buffer that might
   /// be used by get_buffered() with a value read from the pin. 
   ///
   /// The pin read buffer might also be refreshed as a side-effect of 
   /// other operations.
   virtual void refresh(){ }

};

/// output pin interface
//
/// This class abstracts the interface for an output-only pin.
class pin_out {
public:

   /// write the pin
   //
   /// This function sets the level of the pin to
   /// the value v. A value of true makes the pin high, a value of
   /// false makes it low.
   virtual void set( bool v ) = 0;
   
   /// write the pin bufferd
   //
   /// This function sets the pin bit in the write buffer to the value of v.
   /// This might write that value to the pin.
   virtual void set_buffered( bool v ){ set( v ); }
   
   /// flush the pin buffer
   //
   /// This function flushes the pin write buffer: if the buffered value
   /// has not yet been written it is written to the pin.
   /// When the value has been written, it might be written again.
   ///
   /// The pin write buffer might also be flushed as a side-effect of 
   /// other operations.
   virtual void flush(){ }   

};

/// input/output pin interface
//
/// This class abstracts the interface for an input/output pin.
class pin_in_out {
public:

   /// set the direction of a pin to input.
   //
   /// Calling this function sets the pin identified by p to input.
   virtual void direction_set_input() = 0;

   /// read the pin
   //
   /// This function returns the level of the pin.
   /// When the pin level is high the value true is returned,
   /// when the pin level is low the value false is returned.
   ///
   /// Before calling this function the pin direction must have been 
   /// set to input by calling direction_set_input().   
   virtual bool get() = 0;
   
   /// read the pin buffer
   //
   /// This function returns the level of the pin, which might
   /// be be from a read buffer.
   /// When the pin level in the buffer is high the value true is returned,
   /// when the pin level in the buffer is low the value false is returned.
   virtual bool get_buffered(){ return get(); }

   /// refresh the pin buffer
   //
   /// This function refreshed the contents of the read buffer that might
   /// be used by get_buffered() with a value read from the pin. 
   ///
   /// The pin read buffer might also be refreshed as a side-effect of 
   /// other operations.   
   virtual void refresh(){ }   

   /// set the direction of a pin to output
   //
   /// Calling this function sets the pin identified by p to output.
   virtual void direction_set_output() = 0;

   /// write the pin
   //
   /// This function sets the level of the pin to
   /// the value v. A value of true makes the pin high, a value of
   /// false makes it low.
   ///
   /// Before calling this function the pin direction must have been 
   /// set to output by calling direction_set_output().   
   virtual void set( bool x ) = 0;   
   
   /// write the pin bufferd
   //
   /// This function sets the pin bit in the write buffer to the value of v.
   /// This might write that value to the pin.
   virtual void set_buffered( bool v ){ set( v ); }
   
   /// flush the pin buffer
   //
   /// This function flushes the pin write buffer: if the buffered value
   /// has not yet been written it is written to the pin.
   /// When the value has been written, it might be written again.
   ///
   /// The pin write buffer might also be fluhsed as a side-effect of 
   /// other operations.   
   virtual void flush(){ }     
   
};

/// open-collector input/output pin interface
//
/// This class abstracts the interface for 
/// an open-collector input/output pin.
class pin_oc {
public:

   /// read the pin
   //
   /// This function returns the level of the pin.
   /// When the pin level is high the value true is returned,
   /// when the pin level is low the value false is returned.
   ///
   /// This function can be called after set( false ) has been called
   /// on the pin, but then the level will read low (false). 
   /// Call set( true ) to let the line float
   /// (presumably pulled high by a pull-up resistor)
   /// to read the level put on the line by
   /// an external device.
   virtual bool get() = 0;
   
   /// read the pin buffer
   //
   /// This function returns the level of the pin, which might
   /// be be from a read buffer.
   /// When the pin level in the buffer is high the value true is returned,
   /// when the pin level in the buffer is low the value false is returned.
   virtual bool get_buffered(){ return get(); }

   /// refresh the pin buffer
   //
   /// This function refreshed the contents of the read buffer that might
   /// be used by get_buffered() with a value read from the pin. 
   ///
   /// The pin read buffer might also be refreshed as a side-effect of 
   /// other operations.   
   virtual void refresh(){ }  
   
   /// write the pin
   //
   /// This function sets the level of the pin to
   /// the value v. A value of true makes the pin hihg-impedance
   /// (presumably pulled high by a pull-up resistor),
   ///  a value of false makes it low.  
   virtual void set( bool x ) = 0; 
   
   /// write the pin bufferd
   //
   /// This function sets the pin bit in the write buffer to the value of v.
   /// This might write that value to the pin.
   virtual void set_buffered( bool v ){ set( v ); }
   
   /// flush the pin buffer
   //
   /// This function flushes the pin write buffer: if the buffered value
   /// has not yet been written it is written to the pin.
   /// When the value has been written, it might be written again.
   ///
   /// The pin write buffer might also be flushed as a side-effect of 
   /// other operations.   
   virtual void flush(){ }     
};

}; // namespace hwlib

#endif // HWLIB_PIN_H