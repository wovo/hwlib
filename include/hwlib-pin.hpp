// ==========================================================================
//
// File      : hwlib-pin.hpp
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

#ifndef HWLIB_PIN_H
#define HWLIB_PIN_H

#include "hwlib-common.hpp"

namespace hwlib {
   
/// \brief   
/// input/output pin interface
/// \details
/// This class abstracts the interface for an input/output pin.
class pin_in_out {
public:

   /// \brief
   /// set the direction of a pin to input.
   /// \details
   /// Calling this function sets the pin identified by p to input.
   virtual void direction_set_input() = 0;

   /// read the pin
   ///
   /// This function returns the level of the pin.
   /// When the pin level is high the value true is returned,
   /// when the pin level is low the value false is returned.
   virtual bool get( 
      buffering buf = buffering::unbuffered 
   ) = 0;

   /// \brief
   /// refresh the pin buffer
   /// \details
   /// This function refreshes the contents of the read buffer that might
   /// be used by a buffered get().
   ///
   /// That buffer might also be refreshed as a side-effect of other
   /// operations.   
   virtual void refresh(){ }   

   /// set the direction of a pin to output
   ///
   /// Calling this function sets the pin identified by p to output.
   virtual void direction_set_output() = 0;
   
   /// \brief
   /// write the pin
   /// \details
   /// This function sets the level of the pin to
   /// the value v. A value of true makes the pin high, a value of
   /// false makes it low.
   virtual void set( 
      bool x, 
      buffering buf = buffering::unbuffered 
   ) = 0;   
   
   /// \brief   
   /// flush the pin buffer
   /// \details
   /// This function flushes the pin write buffer: if the buffered value
   /// has not yet been written it is written to the pin.
   /// When the value has been written, it might be written again.
   ///
   /// The pin write buffer might also be fluhsed as a side-effect of 
   /// other operations.   
   virtual void flush(){ }     
   
};   

/// \brief
/// input pin interface
/// \details
/// This class abstracts the interface for an input-only pin.
class pin_in {
public:

   /// @copydoc pin_in_out::get()
   virtual bool get( 
      buffering buf = buffering::unbuffered 
   ) = 0;
   
   /// @copydoc pin_in_out::refresh()  
   virtual void refresh(){ }

};

/// \brief
/// output pin interface
/// \details
/// This class abstracts the interface for an output-only pin.
class pin_out {
public:

   /// @copydoc pin_in_out::set()  
   virtual void set( 
      bool x, 
      buffering buf = buffering::unbuffered 
   ) = 0;  
   
   /// @copydoc pin_in_out::flush() 
   virtual void flush(){ }   

};

/// \brief
/// open-collector input/output pin interface
/// \details
/// This class abstracts the interface for 
/// an open-collector input/output pin.
class pin_oc {
public:

   /// \brief
   /// read the pin
   /// \details
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
   virtual bool get( 
      buffering buf = buffering::unbuffered 
   ) = 0;

   /// @copydoc pin_in_out::refresh()   
   virtual void refresh(){ }  
   
   /// \brief   
   /// write the pin
   /// \details
   /// This function sets the level of the pin to
   /// the value v. A value of true makes the pin hihg-impedance
   /// (presumably pulled high by a pull-up resistor),
   ///  a value of false makes it low.  
   virtual void set( 
      bool x, 
      buffering buf = buffering::unbuffered 
   ) = 0;   
   
   /// @copydoc pin_in_out::flush()  
   virtual void flush(){ }     
   
};

}; // namespace hwlib

#endif // HWLIB_PIN_H