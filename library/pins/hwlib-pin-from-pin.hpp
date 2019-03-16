// ==========================================================================
//
// File      : hwlib-pin-from-pin.hpp
// Part of   : C++ hwlib library for close-to-the-hardware OO programming
// Copyright : wouter@voti.nl 2017-2019
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

// included only via hwlib.hpp, hence no multiple-include guard is needed

// this file contains Doxygen linesd
/// @file

namespace hwlib {
	
	
// ==========================================================================
//
// pin_out_from
//
// ==========================================================================

/// a pin_out constructed from a oc
///
/// The preferred way to use this class is through the overloaded 
/// constructor function pin_out_from().
class pin_out_from_oc_t : public pin_out {
private:
	
   pin_oc & slave;
   
public:

   /// construct from a pin_oc
   pin_out_from_oc_t( pin_oc & slave ): slave( slave ){}
   
   void write( bool x ) override {
      slave.write( x );
   }	  
   
   void flush() override {
      slave.flush();       
   }
   
};	

/// a pin_out constructed from a pin_out
///
/// The preferred way to use this class is through the overloaded 
/// constructor function pin_out_from().
class pin_out_from_out_t : public pin_out {
private:
	
   pin_out & slave;
   
public:

   /// construct from a pin_out
   pin_out_from_out_t( pin_out & slave ): slave( slave ){}
   
   void write( bool x ) override {
      slave.write( x );
   }	

     void flush() override {
      slave.flush();       
   }
   
};	

/// a pin_out constructed from a pin_in_out
///
/// The preferred way to use this class is through the overloaded 
/// constructor function pin_out_from().
class pin_out_from_in_out_t : public pin_out {
private:
	
   pin_in_out & slave;
   
public:

   /// construct from a pin_in_out
   pin_out_from_in_out_t( pin_in_out & slave ): slave( slave ){
      slave.direction_set_output();	   
      slave.direction_flush();	   
   }
   
   void write( bool x ) override {
      slave.write( x );
   }

   void flush() override {
      slave.flush();       
   }
   
};	

/// return a pin_out from another type of pin
///@{ 
pin_out_from_oc_t      pin_out_from( pin_oc & slave );
pin_out_from_out_t     pin_out_from( pin_out & slave );
pin_out_from_in_out_t  pin_out_from( pin_in_out & slave );
///@}


// ==========================================================================
//
// pin_in_from
//
// ==========================================================================

/// a pin_in constructed from a pin_oc
///
/// The preferred way to use this class is through the overloaded 
/// constructor function pin_in_from().
class pin_in_from_oc_t : public pin_in {
private:
	
   pin_oc & slave;
   
public:

   /// construct from a pin_oc
   pin_in_from_oc_t( pin_oc & slave ): slave( slave ){
      slave.write( 1 );	     
	  slave.flush();
   }
    
   bool read() override {
      return slave.read();
   }	  
      
   void refresh() override {
      slave.refresh();       
   }
   
};	

/// a pin_in constructed from a pin_in
///
/// The preferred way to use this class is through the overloaded 
/// constructor function pin_in_from().
class pin_in_from_in_t : public pin_in {
private:
	
   pin_in & slave;
   
public:

   /// construct from a pin_in
   pin_in_from_in_t( pin_in & slave ): slave( slave ){}
    
   bool read() override {
      return slave.read();
   }	  
      
   void refresh() override {
      slave.refresh();       
   }
};	

/// a pin_in constructed from a pin_in_out
///
/// The preferred way to use this class is through the overloaded 
/// constructor function pin_in_from().
class pin_in_from_in_out_t : public pin_in {
private:
	
   pin_in_out & slave;
   
public:

   /// construct from a pin_in_out
   pin_in_from_in_out_t( pin_in_out & slave ): slave( slave ){
      slave.direction_set_input(); 	 
      slave.direction_flush();	  
   }
     
   bool read() override {
      return slave.read();
   }	  
      
   void refresh() override {
      slave.refresh();       
   }	  
};	

/// return a pin_out from another type of pin
///@{ 
pin_in_from_oc_t      pin_in_from( pin_oc & slave );
pin_in_from_in_t      pin_in_from( pin_in & slave );
pin_in_from_in_out_t  pin_in_from( pin_in_out & slave );
///@}


// ==========================================================================
//
// pin_in_out_from
//
// ==========================================================================

/// a pin_in_out constructed from a pin_oc
///
/// The preferred way to use this class is through the overloaded 
/// constructor function pin_oc_from().
class pin_in_out_from_oc_t : public pin_in_out {
private:
	
   pin_oc & slave;
   bool is_output;
   
public:

   /// construct from a pin_oc
   pin_in_out_from_oc_t( pin_oc & slave ): slave( slave ){}
   
   void direction_set_input() override {
      is_output = false;	   
      slave.write( 1 );	 	  
   }	   
   
   void direction_set_output(){
      is_output = true;	   
      // nothing more to do
   }
   
   bool read() override {
      return slave.read();
   }	  
   
   void write( bool x ) override {
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

/// a pin_in_out constructed from a pin_in_out
///
/// The preferred way to use this class is through the overloaded 
/// constructor function pin_oc_from().
class pin_in_out_from_in_out_t : public pin_in_out {
private:
	
   pin_in_out & slave;
   
public:

   /// construct from a pin_in_out
   pin_in_out_from_in_out_t( pin_in_out & slave ): slave( slave ){}
   
   void direction_set_input() override {
      slave.direction_set_input();  
   }	   
   
   void direction_set_output(){
      slave.direction_set_output(); 
   }
   
   bool read() override {
      return slave.read();
   }	  
   
   void write( bool x ) override {
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

/// return a pin_out from another type of pin
///@{ 
pin_in_out_from_oc_t      pin_in_out_from( pin_oc & slave );
pin_in_out_from_in_out_t  pin_in_out_from( pin_in_out & slave );
///@}


// ==========================================================================
//
// pin_oc_from
//
// ==========================================================================

/// a pin_oc constructed from a pin_oc
///
/// The preferred way to use this class is through the overloaded 
/// constructor function pin_oc_from().
class pin_oc_from_oc_t : public pin_oc {
private:
	
   pin_oc & slave;
   
public:

   /// construct from a pin_oc
   pin_oc_from_oc_t( pin_oc & slave ): slave( slave ){}
     
   bool read() override {
      return slave.read();
   }	  
   
   void write( bool x ) override {
      slave.write( x );
   }

   void flush() override {
      slave.flush();       
   }
   
   void refresh() override {
      slave.refresh();       
   }
   
};	

/// a pin_oc constructed from a pin_in_out
///
/// The preferred way to use this class is through the overloaded 
/// constructor function pin_oc_from().
class pin_oc_from_in_out_t : public pin_oc {
private:
	
   pin_in_out & slave;
   
public:

   /// construct from a pin_in_out
   pin_oc_from_in_out_t( pin_in_out & slave ): slave( slave ){}
  
   bool read() override {
      return slave.read();
   }	  
   
   void write( bool x ) override {
      if( x ){
         slave.direction_set_input(); 
      } else {		  
         slave.direction_set_output(); 
         slave.write( 0 );
      }		 
   }	  
   
   void flush() override {
	  slave.direction_flush();
      slave.flush();       
   }
   
   void refresh() override {
      slave.refresh();       
   }   
   
};	

/// return a pin_out from another type of pin
///@{ 
pin_oc_from_oc_t      pin_oc_from( pin_oc & slave );
pin_oc_from_in_out_t  pin_oc_from( pin_in_out & slave );
///@}

// ===========================================================================
//
// implementations
//
// ===========================================================================

#ifdef _HWLIB_ONCE

// pin_out_from

pin_out_from_oc_t pin_out_from( pin_oc & slave ){
   return pin_out_from_oc_t( slave );
}

pin_out_from_out_t pin_out_from( pin_out & slave ){
   return pin_out_from_out_t( slave );
}

pin_out_from_in_out_t pin_out_from( pin_in_out & slave ){
   return pin_out_from_in_out_t( slave );
}

// pin_in_from

pin_in_from_in_t pin_in_from( pin_in & slave ){
   return pin_in_from_in_t( slave );
}

pin_in_from_in_out_t pin_in_from( pin_in_out & slave ){
   return pin_in_from_in_out_t( slave );
}

pin_in_from_oc_t pin_in_from( pin_oc & slave ){
   return pin_in_from_oc_t( slave );
}

// pin_in_out_from

pin_in_out_from_oc_t pin_in_out_from( pin_oc & slave ){
   return pin_in_out_from_oc_t( slave );
}

pin_in_out_from_in_out_t pin_in_out_from( pin_in_out & slave ){
   return pin_in_out_from_in_out_t( slave );
}

// pin_oc_from

pin_oc_from_oc_t pin_oc_from( pin_oc & slave ){
   return pin_oc_from_oc_t( slave );
}

pin_oc_from_in_out_t pin_oc_from( pin_in_out & slave ){
   return pin_oc_from_in_out_t( slave );
}

#endif // _HWLIB_ONCE

}; // namespace hwlib
