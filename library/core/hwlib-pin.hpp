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

// included only via hwlib.hpp, hence no multiple-include guard is needed

// this file contains Doxygen lines
/// @file

namespace hwlib {
   
/// input/output pin interface
/// 
/// This class abstracts the interface for an input/output pin.
class pin_in_out {
public:

   /// set the direction of a pin to input
   /// 
   /// Calling this function sets the pin identified by p to input.
   virtual void direction_set_input() = 0;

   /// read the pin
   /// 
   /// This function returns the level of the pin.
   /// When the pin level is high the value true is returned,
   /// when the pin level is low the value false is returned.
   virtual bool read() = 0;

   /// refresh the pin buffer
   /// 
   /// This function refreshes the contents of the read buffer that might
   /// be used by a buffered read().
   ///
   /// That buffer might also be refreshed as a side-effect of other
   /// operations.   
   virtual void refresh() = 0;

   /// set the direction of a pin to output
   ///
   /// Calling this function sets the pin identified by p to output.
   virtual void direction_set_output() = 0;
   
   /// write the pin
   /// 
   /// This function sets the level of the pin to
   /// the value v. A value of true makes the pin high, a value of
   /// false makes it low.
   virtual void write( bool x ) = 0;   
   
 
   /// flush the pin buffer
   /// 
   /// This function flushes the pin write buffer: if the buffered value
   /// has not yet been written it is written to the pin.
   /// When the value has been written, it might be written again.
   ///
   /// The pin write buffer might also be fluhsed as a side-effect of 
   /// other operations.   
   virtual void flush() = 0;
   
};   

/// input pin interface
/// 
/// This class abstracts the interface for an input-only pin.
class pin_in {
public:

   /// @copydoc pin_in_out::read()
   virtual bool read() = 0;
   
   /// @copydoc pin_in_out::refresh()  
   virtual void refresh(){ }

};

/// output pin interface
/// 
/// This class abstracts the interface for an output-only pin.
class pin_out {
public:

   /// @copydoc pin_in_out::write()  
   virtual void write( bool x ) = 0;  
   
   /// @copydoc pin_in_out::flush() 
   virtual void flush() = 0; 

};

/// open-collector input/output pin interface
/// 
/// This class abstracts the interface for 
/// an open-collector input/output pin.
class pin_oc {
public:

   /// read the pin
   /// 
   /// This function returns the level of the pin.
   /// When the pin level is high the value true is returned,
   /// when the pin level is low the value false is returned.
   ///
   /// This function can be called after write( false ) has been called
   /// on the pin, but then the level will read low (false). 
   /// Call write( true ) to let the line float
   /// (presumably pulled high by a pull-up resistor)
   /// to read the level put on the line by
   /// an external device.
   virtual bool read() = 0;

   /// @copydoc pin_in_out::refresh()   
   virtual void refresh() = 0;  
   
   /// write the pin
   /// 
   /// This function sets the level of the pin to
   /// the value v. A value of true makes the pin hihg-impedance
   /// (presumably pulled high by a pull-up resistor),
   ///  a value of false makes it low.  
   virtual void write( bool x ) = 0;   
   
   /// @copydoc pin_in_out::flush()  
   virtual void flush() = 0;    
   
};

}; // namespace hwlib
