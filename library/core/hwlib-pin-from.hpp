// ==========================================================================
//
// File      : hwlib-pin-from.hpp
// Part of   : C++ hwlib library for close-to-the-hardware OO programming
// Copyright : wouter@voti.nl 2017
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

class pin_out_from_oc_t : public pin_out {
   pin_oc & slave;
   
public:
   pin_out_from_oc_t( pin_oc & slave ): slave( slave ){}
   
   void write( bool x ) override {
      slave.write( x );
   }	  
   
   void flush() override {
      slave.flush();       
   }
};	

class pin_out_from_out_t : public pin_out {
   pin_out & slave;
   
public:
   pin_out_from_out_t( pin_out & slave ): slave( slave ){}
   
   void write( bool x ) override {
      slave.write( x );
   }	

     void flush() override {
      slave.flush();       
   }
};	

class pin_out_from_in_out_t : public pin_out {
   pin_in_out & slave;
   
public:
   pin_out_from_in_out_t( pin_in_out & slave ): slave( slave ){
      slave.direction_set_output();	   
   }
   
   void write( bool x ) override {
      slave.write( x );
   }

   void flush() override {
      slave.flush();       
   }
};	

pin_out_from_oc_t      pin_out_from( pin_oc & slave );
pin_out_from_out_t     pin_out_from( pin_out & slave );
pin_out_from_in_out_t  pin_out_from( pin_in_out & slave );

#ifdef HWLIB_ONCE

pin_out_from_oc_t pin_out_from( pin_oc & slave ){
   return pin_out_from_oc_t( slave );
}

pin_out_from_out_t pin_out_from( pin_out & slave ){
   return pin_out_from_out_t( slave );
}

pin_out_from_in_out_t pin_out_from( pin_in_out & slave ){
   return pin_out_from_in_out_t( slave );
}

#endif


// ==========================================================================
//
// pin_in_out_from
//
// ==========================================================================

class pin_in_out_from_oc_t : public pin_in_out {
   pin_oc & slave;
   bool is_output;
   
public:
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
};	

class pin_in_out_from_in_out_t : public pin_in_out {
   pin_in_out & slave;
   
public:
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
};	

pin_in_out_from_oc_t      pin_in_out_from( pin_oc & slave );
pin_in_out_from_in_out_t  pin_in_out_from( pin_in_out & slave );

#ifdef HWLIB_ONCE

pin_in_out_from_oc_t pin_in_out_from( pin_oc & slave ){
   return pin_in_out_from_oc_t( slave );
}

pin_in_out_from_in_out_t pin_in_out_from( pin_in_out & slave ){
   return pin_in_out_from_in_out_t( slave );
}

#endif


// ==========================================================================
//
// pin_oc_from
//
// ==========================================================================

class pin_oc_from_oc_t : public pin_oc {
   pin_oc & slave;
   
public:
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

class pin_oc_from_in_out_t : public pin_oc {
   pin_in_out & slave;
   
public:
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
      slave.flush();       
   }
   
   void refresh() override {
      slave.refresh();       
   }   
};	

pin_oc_from_oc_t      pin_oc_from( pin_oc & slave );
pin_oc_from_in_out_t  pin_oc_from( pin_in_out & slave );

#ifdef HWLIB_ONCE

pin_oc_from_oc_t pin_oc_from( pin_oc & slave ){
   return pin_oc_from_oc_t( slave );
}

pin_oc_from_in_out_t pin_oc_from( pin_in_out & slave ){
   return pin_oc_from_in_out_t( slave );
}

#endif

}; // namespace hwlib
