// ==========================================================================
//
// File      : hwlib-pin.hpp
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
   
/// input/output pin interface
/// 
/// This class abstracts the interface for an input/output pin.
class pin_in_out : public noncopyable  {
public:

   /// set the direction of a pin to input
   /// 
   /// Calling this function sets the pin identified by p to input.
   ///
   /// The actual changing of the direction can be postponed to the
   /// next direction_output_flush(0 call.
   virtual void direction_set_input() = 0;

   /// read the pin
   /// 
   /// This function returns the level of the pin.
   /// When the pin level is high the value true is returned,
   /// when the pin level is low the value false is returned.
   ///
   /// The value that is read might be a buffered value, 
   /// read no later than the last refresh() call.
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
   ///
   /// The actual changing of the direction can be postponed to the
   /// next direction_output_flush(0 call.   
   virtual void direction_set_output() = 0;
   
   /// flush the direction
   ///
   /// Calling this function flushes the direction as set by the last
   /// call to direction_set_input() or direction_set_output() to the pin.
   virtual void direction_flush() = 0;
   
   /// write the pin
   /// 
   /// This function sets the level of the pin to
   /// the value v. A value of true makes the pin high, a value of
   /// false makes it low.
   ///
   /// The actual effect on the pin might be postponed until the
   /// next flush() call.
   virtual void write( bool x ) = 0;   
 
   /// flush the pin buffer
   /// 
   /// This function flushes the pin write buffer: if the buffered value
   /// has not yet been written it is written to the pin.
   /// When the value has been written, it might be written again.
   ///
   /// The pin write buffer might also be flushed as a side-effect of 
   /// other operations.   
   virtual void flush() = 0;
   
};   


// ==========================================================================
//
// pin_in
//
// ==========================================================================	


/// input pin interface
/// 
/// This class abstracts the interface for an input-only pin.
class pin_in : public noncopyable {
public:

   /// @copydoc pin_in_out::read()
   virtual bool read() = 0;
   
   /// @copydoc pin_in_out::refresh()  
   virtual void refresh(){ }

};


// ==========================================================================
//
// pin_out
//
// ==========================================================================	
	

/// output pin interface
/// 
/// This class abstracts the interface for an output-only pin.
class pin_out : public noncopyable {
public:

   /// @copydoc pin_in_out::write()  
   virtual void write( bool x ) = 0;  
   
   /// @copydoc pin_in_out::flush() 
   virtual void flush() = 0; 

};


// ==========================================================================
//
// pin_oc
//
// ==========================================================================	
	
/// open-collector input/output pin interface
/// 
/// This class abstracts the interface for 
/// an open-collector input/output pin.
class pin_oc : public noncopyable {
public:

   /// read the pin
   /// 
   /// @copydoc pin_in_out::read()
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
   /// @copydoc pin_in_out::write()    
   /// 
   /// This function sets the level of the pin to
   /// the value v. A value of true makes the pin high-impedance
   /// (presumably pulled high by a pull-up resistor),
   ///  a value of false makes it low.  
   virtual void write( bool x ) = 0;   
   
   /// @copydoc pin_in_out::flush()  
   virtual void flush() = 0;    
   
};

}; // namespace hwlib
