// ==========================================================================
//
// File      : hwlib-port-all.hpp
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
// port_out
//
// ==========================================================================

/// pin class that writes to a pins in a port
class all_from_port_out_t : public pin_out {
private:
 
   port_out & slave;
   
public:

   /// construct a pin_out from a port_out
   /// 
   /// This pin_out writes to all pins in the port.
   all_from_port_out_t( port_out & slave ): slave( slave ) {}        
   
   void write( bool x ) override {
      slave.write( x ? 0xFF : 0x0 );       
   }
   
   void flush() override {
      slave.flush();                
   }

};


// ===========================================================================
//
// constructor functions
//
// ===========================================================================

/// return a pin that writes to all pins in the port
all_from_port_out_t all( port_out & slave );


// ===========================================================================
//
// implementations
//
// ===========================================================================

#ifdef _HWLIB_ONCE

all_from_port_out_t all( port_out & slave ){
   return all_from_port_out_t( slave );
}   

#endif // _HWLIB_ONCE

}; // namespace hwlib
