// ==========================================================================
//
// File      : hwlib-pin-store.hpp
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
    
	
/// a pin_in_out that stores its state and operation counts
///
/// A pin_in_out_store is useful for tests.
class pin_in_out_store : public pin_in_out {
public:

   /// the current pin level
   bool value = false;
   
   /// true iff the current direction is output
   bool is_output = false;
   
   /// true iff the current direction is input
   bool is_input = false;

   /// incremented on each read() call
   int read_count = 0;   
   
   /// incremented on each write() call
   int write_count = 0;   
   
   /// incremented on direction_set_input() & direction_setOutput() calls
   int direction_set_count = 0;
   
   /// incremenst on each flush() call
   int flush_count = 0;

   /// incremenst on each refresh() call
   int refresh_count = 0;
   
   /// incremenst on each direction_flush() call
   int direction_flush_count = 0;

   /// set the current pin level
   void write( bool v ) override {
      ++write_count;
      value = v;
   }
   
   /// returns the current pin level
   bool read() override { 
      ++read_count;
      return value; 
   }
   
   /// set the direction flags to indicate input
   void direction_set_input() override {
      ++direction_set_count;	   
      is_input = true;	   
      is_output = false;	   
   }
   
   /// set the direction flags to indicate output
   void direction_set_output() override {
      ++direction_set_count;	   
	  is_input = false;
      is_output = true;	   
   }
   
   /// increment the flush count
   void flush() override {
      ++flush_count;
   }
   
   /// increment the refresh count
   void refresh() override {
      ++refresh_count;	   
   }
   
   /// increment the direction_flush count
   void direction_flush() override {
      ++direction_flush_count;	   
   }
   
};  


/// a pin_in_out that stores its state and operation counts
///
/// A pin_in_store is useful for tests.
class pin_in_store : public pin_in {
public:

   /// the current pin level
   bool value = false;
   
   /// incremented on each read() call
   int read_count = 0;     

   /// incremenst on each refresh() call
   int refresh_count = 0;
    
   /// returns the current pin level
   bool read() override { 
      ++read_count;
      return value; 
   }
   
   /// increment the refresh count
   void refresh() override {
      ++refresh_count;	   
   }
   
};   


/// a pin_in_out that stores its state and operation counts
///
/// A pin_out_store is useful for tests.
class pin_out_store : public pin_out {
public:

   /// the current pin level
   bool value = false;
 
   /// incremented on each write() call
   int write_count = 0;   

   /// incremenst on each flush() call
   int flush_count = 0;
   
   /// set the current pin level
   void write( bool v ) override {
      ++write_count;
      value = v;
   }
   
   /// increment the flush count
   void flush() override {
      ++flush_count;
   }

};   


/// a pin_in_out that stores its state and operation counts
///
/// A pin_oc_store is useful for tests.
class pin_oc_store : public pin_oc {
public:

   /// the current pin level
   bool value = false;

   /// incremented on each read() call
   int read_count = 0;   

   /// incremented on each write() call
   int write_count = 0;   

   /// incremenst on each flush() call
   int flush_count = 0;

   /// incremenst on each refresh() call
   int refresh_count = 0;
   
   /// set the current pin level
   void write( bool v ) override {
      ++write_count;
      value = v;
   }
   
   /// returns the current pin level
   bool read() override { 
      ++read_count;
      return value; 
   }
   
   /// increment the flush count
   void flush() override {
      ++flush_count;
   }
   
   /// increment the refresh count
   void refresh() override {
      ++refresh_count;	   
   } 
   
};   

}; // namespace hwlib
