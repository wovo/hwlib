// ==========================================================================
//
// File      : hwlib-port-from-port.hpp
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
// port_out_from
//
// ==========================================================================

/// a port_out constructed from a oc
///
/// The preferred way to use this class is through the overloaded 
/// constructor function port_out_from().
class port_out_from_oc_t : public port_out {
private:
	
   port_oc & slave;
   
public:

   /// construct from a port_oc
   port_out_from_oc_t( port_oc & slave ): slave( slave ){}
   
   uint_fast8_t number_of_pins() override {
      return slave.number_of_pins();
   }   
   
   void write( uint_fast16_t x ) override {
      slave.write( x );
   }	  
   
   void flush() override {
      slave.flush();       
   }
   
};	

/// a port_out constructed from a port_out
///
/// The preferred way to use this class is through the overloaded 
/// constructor function port_out_from().
class port_out_from_out_t : public port_out {
private:
	
   port_out & slave;
   
public:

   /// construct from a port_out
   port_out_from_out_t( port_out & slave ): slave( slave ){}
   
   uint_fast8_t number_of_pins() override {
      return slave.number_of_pins();
   }

   void write( uint_fast16_t x ) override {
      slave.write( x );
   }	

   void flush() override {
      slave.flush();       
   }
   
};	

/// a port_out constructed from a port_in_out
///
/// The preferred way to use this class is through the overloaded 
/// constructor function port_out_from().
class port_out_from_in_out_t : public port_out {
private:
	
   port_in_out & slave;
   
public:

   /// construct from a port_in_out
   port_out_from_in_out_t( port_in_out & slave ): slave( slave ){
      slave.direction_set_output();	   
      slave.direction_flush();	   
   }
   
   uint_fast8_t number_of_pins() override {
      return slave.number_of_pins();
   }   
   
   void write( uint_fast16_t x ) override {
      slave.write( x );
   }

   void flush() override {
      slave.flush();       
   }
   
};	

/// return a port_out from another type of port
///@{ 
port_out_from_oc_t      port_out_from( port_oc & slave );
port_out_from_out_t     port_out_from( port_out & slave );
port_out_from_in_out_t  port_out_from( port_in_out & slave );
///@}


// ==========================================================================
//
// port_in_from
//
// ==========================================================================

/// a port_in constructed from a port_oc
///
/// The preferred way to use this class is through the overloaded 
/// constructor function port_in_from().
class port_in_from_oc_t : public port_in {
private:
	
   port_oc & slave;
   
public:

   /// construct from a port_oc
   port_in_from_oc_t( port_oc & slave ): slave( slave ){
     slave.write( 0xFF );	     
	  slave.flush();
   }
   
   uint_fast8_t number_of_pins() override {
      return slave.number_of_pins();
   }   
    
   uint_fast16_t read() override {
      return slave.read();
   }	  
      
   void refresh() override {
      slave.refresh();       
   }
   
};	

/// a port_in constructed from a port_in
///
/// The preferred way to use this class is through the overloaded 
/// constructor function port_in_from().
class port_in_from_in_t : public port_in {
private:
	
   port_in & slave;
   
public:

   /// construct from a port_in
   port_in_from_in_t( port_in & slave ): slave( slave ){}
    
   uint_fast8_t number_of_pins() override {
      return slave.number_of_pins();
   }	
	
   uint_fast16_t read() override {
      return slave.read();
   }	  
      
   void refresh() override {
      slave.refresh();       
   }
};	

/// a port_in constructed from a port_in_out
///
/// The preferred way to use this class is through the overloaded 
/// constructor function port_in_from().
class port_in_from_in_out_t : public port_in {
private:
	
   port_in_out & slave;
   
public:

   /// construct from a port_in_out
   port_in_from_in_out_t( port_in_out & slave ): slave( slave ){
      slave.direction_set_input(); 	 
      slave.direction_flush();	  
   }
   
   uint_fast8_t number_of_pins() override {
      return slave.number_of_pins();
   }
   
   uint_fast16_t read() override {
      return slave.read();
   }	  
      
   void refresh() override {
      slave.refresh();       
   }	  
};	

/// return a port_out from another type of port
///@{ 
port_in_from_oc_t      port_in_from( port_oc & slave );
port_in_from_in_t      port_in_from( port_in & slave );
port_in_from_in_out_t  port_in_from( port_in_out & slave );
///@}


// ==========================================================================
//
// port_in_out_from
//
// ==========================================================================

/// a port_in_out constructed from a port_oc
///
/// The preferred way to use this class is through the overloaded 
/// constructor function port_oc_from().
class port_in_out_from_oc_t : public port_in_out {
private:
	
   port_oc & slave;
   uint_fast8_t is_output;
   
public:

   /// construct from a port_oc
   port_in_out_from_oc_t( port_oc & slave ): slave( slave ){}
   
   uint_fast8_t number_of_pins() override {
      return slave.number_of_pins();
   }

   void direction_set_input() override {
      is_output = false;	   
      slave.write( 0xFF );	 	  
   }	   
   
   void direction_set_output(){
      is_output = true;	   
      // nothing more to do
   }
   
   uint_fast16_t read() override {
      return slave.read();
   }	  
   
   void write( uint_fast16_t x ) override {
      if( is_output ){
         slave.write( x );
      }		 
   }

   void flush() override {
      slave.flush();       
   }
   
   void refresh() override {
      slave.refresh();       
   }
   
   void direction_flush() override {    
      slave.flush();
   }
   
};	

/// a port_in_out constructed from a port_in_out
///
/// The preferred way to use this class is through the overloaded 
/// constructor function port_oc_from().
class port_in_out_from_in_out_t : public port_in_out {
private:
	
   port_in_out & slave;
   
public:

   /// construct from a port_in_out
   port_in_out_from_in_out_t( port_in_out & slave ): slave( slave ){}
   
   uint_fast8_t number_of_pins() override {
      return slave.number_of_pins();
   }

   void direction_set_input() override {
      slave.direction_set_input();  
   }	   
   
   void direction_set_output(){
      slave.direction_set_output(); 
   }
   
   uint_fast16_t read() override {
      return slave.read();
   }	  
   
   void write( uint_fast16_t x ) override {
      slave.write( x );
   }

   void flush() override {
      slave.flush();       
   }
   
   void refresh() override {
      slave.refresh();       
   }	  

   void direction_flush() override {
      slave.direction_flush();       
   }

};	

/// return a port_out from another type of port
///@{ 
port_in_out_from_oc_t      port_in_out_from( port_oc & slave );
port_in_out_from_in_out_t  port_in_out_from( port_in_out & slave );
///@}


// ==========================================================================
//
// port_oc_from
//
// ==========================================================================

/// a port_oc constructed from a port_oc
///
/// The preferred way to use this class is through the overloaded 
/// constructor function port_oc_from().
class port_oc_from_oc_t : public port_oc {
private:
	
   port_oc & slave;
   
public:

   /// construct from a port_oc
   port_oc_from_oc_t( port_oc & slave ): slave( slave ){}
     
   uint_fast8_t number_of_pins() override {
      return slave.number_of_pins();
   }

   uint_fast16_t read() override {
      return slave.read();
   }	  
   
   void write( uint_fast16_t x ) override {
      slave.write( x );
   }

   void flush() override {
      slave.flush();       
   }
   
   void refresh() override {
      slave.refresh();       
   }
   
};	

// Unlike for pins, a port_oc can't be constructed from a port_in_out 
// because the pin direction can't be controlled individually.	

/// return a port_out from another type of port
///@{ 
port_oc_from_oc_t      port_oc_from( port_oc & slave );
///@}


// ===========================================================================
//
// implementations
//
// ===========================================================================

#ifdef _HWLIB_ONCE

// port_out_from

port_out_from_oc_t port_out_from( port_oc & slave ){
   return port_out_from_oc_t( slave );
}

port_out_from_out_t port_out_from( port_out & slave ){
   return port_out_from_out_t( slave );
}

port_out_from_in_out_t port_out_from( port_in_out & slave ){
   return port_out_from_in_out_t( slave );
}

// port_in_from

port_in_from_in_t port_in_from( port_in & slave ){
   return port_in_from_in_t( slave );
}

port_in_from_in_out_t port_in_from( port_in_out & slave ){
   return port_in_from_in_out_t( slave );
}

port_in_from_oc_t port_in_from( port_oc & slave ){
   return port_in_from_oc_t( slave );
}

// port_in_out_from

port_in_out_from_oc_t port_in_out_from( port_oc & slave ){
   return port_in_out_from_oc_t( slave );
}

port_in_out_from_in_out_t port_in_out_from( port_in_out & slave ){
   return port_in_out_from_in_out_t( slave );
}

// port_oc_from

port_oc_from_oc_t port_oc_from( port_oc & slave ){
   return port_oc_from_oc_t( slave );
}

#endif // _HWLIB_ONCE

}; // namespace hwlib
