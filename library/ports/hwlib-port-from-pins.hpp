// ==========================================================================
//
// File      : hwlib-port-from-pins.hpp
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
/// in_out
//
// ==========================================================================

/// port_in_out from pins class
///
/// This class implements an input-only port made from port up to 10 pins.
class port_in_out_from_pins_t : public port_in_out {
private:

   static constexpr int max_pins = 16;

   uint_fast8_t _number_of_pins;  

   pin_in_out * pins[ max_pins ];   
   
public:

   /// construct a port_out from up to 16 pin_outs
   ///
   /// This constructor creates a port_out from up to 16 pin_in pins.
   /// The first pin is the lowest pin in the port, etc.
   port_in_out_from_pins_t(
      pin_in_out & p0 = pin_in_out_dummy,
      pin_in_out & p1 = pin_in_out_dummy,
      pin_in_out & p2 = pin_in_out_dummy,
      pin_in_out & p3 = pin_in_out_dummy,
      pin_in_out & p4 = pin_in_out_dummy,
      pin_in_out & p5 = pin_in_out_dummy,
      pin_in_out & p6 = pin_in_out_dummy,
      pin_in_out & p7 = pin_in_out_dummy,
      pin_in_out & p8 = pin_in_out_dummy,
      pin_in_out & p9 = pin_in_out_dummy,
      pin_in_out & p10 = pin_in_out_dummy,
      pin_in_out & p11 = pin_in_out_dummy,
      pin_in_out & p12 = pin_in_out_dummy,
      pin_in_out & p13 = pin_in_out_dummy,
      pin_in_out & p14 = pin_in_out_dummy,
      pin_in_out & p15 = pin_in_out_dummy
   ):
      pins{ 
         &p0, &p1, &p2, &p3, &p4, &p5, &p6, &p7, 
         &p8, &p9, &p10, &p11, &p12, &p13, &p14, &p15 }
   {
      for( _number_of_pins = 0; _number_of_pins < max_pins; ++_number_of_pins ){
         if( pins[ _number_of_pins ] == & pin_in_out_dummy ){
             break;
         }            
      }
   }            

   uint_fast8_t number_of_pins() override {
      return _number_of_pins;               
   }   
   
   void direction_set_input() override {
      for( uint_fast8_t i = 0; i < _number_of_pins; i++ ){
         pins[ i ]->direction_set_input();
      }
   }
   
    void direction_set_output() override {
      for( uint_fast8_t i = 0; i < _number_of_pins; i++ ){
         pins[ i ]->direction_set_output();
      }
   }
   
   void direction_flush() override {
      for( uint_fast8_t i = 0; i < _number_of_pins; i++ ){
         pins[ i ]->direction_flush();
      }
   }
   
   uint_fast16_t read() override {
      uint_fast8_t result = 0;
      for( int_fast8_t i = _number_of_pins -1; i >=0; --i ){
         result = result << 1;
         if( pins[ i ]->read() ){
            result |= 0x01;            
         }
       }         
       return result;
   }
   
   void refresh() override {
      for( uint_fast8_t i = 0; i < _number_of_pins; i++ ){
         pins[ i ]->refresh();
      }         
   }      
   
   void write( uint_fast16_t x ) override {
      for( uint_fast8_t i = 0; i < _number_of_pins; i++ ){
         pins[ i ]->write( ( x & 0x01 ) != 0 );
         x = x >> 1;
      }         
   }   

  void flush() override {
      for( uint_fast8_t i = 0; i < _number_of_pins; i++ ){
         pins[ i ]->flush();
      }         
   }   

};


// ==========================================================================
//  
// in
//
// ==========================================================================

/// input port from input pins
//
/// This class implements an input-only port made from port up to 16 pins.
class port_in_from_pins_t : public port_in {
private:

   static constexpr int max_pins = 16;
   
   uint_fast8_t _number_of_pins;  

   pin_in * pins[ max_pins ];   
   
public:

   /// \brief
   /// construct a port_out from up to 16 pin_outs
   /// \details
   /// This constructor creates a port_out from up to 16 pin_in pins.
   /// The first pin is the lowest pin in the port, etc.
   port_in_from_pins_t(
      pin_in & p0 = pin_in_dummy,
      pin_in & p1 = pin_in_dummy,
      pin_in & p2 = pin_in_dummy,
      pin_in & p3 = pin_in_dummy,
      pin_in & p4 = pin_in_dummy,
      pin_in & p5 = pin_in_dummy,
      pin_in & p6 = pin_in_dummy,
      pin_in & p7 = pin_in_dummy,
	  pin_in & p8 = pin_in_dummy,
      pin_in & p9 = pin_in_dummy,
      pin_in & p10 = pin_in_dummy,
      pin_in & p11 = pin_in_dummy,
      pin_in & p12 = pin_in_dummy,
      pin_in & p13 = pin_in_dummy,
      pin_in & p14 = pin_in_dummy,
      pin_in & p15 = pin_in_dummy							 
   ):
      pins{ 
         &p0, &p1, &p2, &p3, &p4, &p5, &p6, &p7, 
         &p8, &p9, &p10, &p11, &p12, &p13, &p14, &p15 }
   {
      for( _number_of_pins = 0; _number_of_pins < max_pins; ++_number_of_pins ){
         if( pins[ _number_of_pins ] == & pin_in_dummy ){
             break;
         }            
      }
   }            

   uint_fast8_t number_of_pins() override {
      return _number_of_pins;               
   }   
   
   uint_fast16_t read() override {
      uint_fast8_t result = 0;  
      for( int_fast8_t i = _number_of_pins -1; i >=0; --i ){
         result = result << 1;
         if( pins[ i ]->read() ){
            result |= 0x01;            
         }
       }          
       return result;
   }
   
  void refresh() override {
      for( uint_fast8_t i = 0; i < _number_of_pins; i++ ){
         pins[ i ]->refresh();
      }         
   }    

};

// ==========================================================================
//  
// port_out
//
// ==========================================================================

/// output port from output pins class
///
/// This class implements an output-only port made from port up to 16 pins.
class port_out_from_pins_t : public port_out {
private:

   static constexpr int max_pins = 16;
   
   uint_fast8_t _number_of_pins;  

   pin_out * pins[ max_pins ];   
   
public:

   /// \brief
   /// construct a port_out from up to 8 pin_outs
   /// \details
   /// This constructor creates a port_out from up to 8 pin_out pins.
   /// The first pin is the lowest pin in the port, etc.
   port_out_from_pins_t(
      pin_out & p0 = pin_out_dummy,
      pin_out & p1 = pin_out_dummy,
      pin_out & p2 = pin_out_dummy,
      pin_out & p3 = pin_out_dummy,
      pin_out & p4 = pin_out_dummy,
      pin_out & p5 = pin_out_dummy,
      pin_out & p6 = pin_out_dummy,
      pin_out & p7 = pin_out_dummy,
      pin_out & p8 = pin_out_dummy,
      pin_out & p9 = pin_out_dummy,
      pin_out & p10 = pin_out_dummy,
      pin_out & p11 = pin_out_dummy,
      pin_out & p12 = pin_out_dummy,
      pin_out & p13 = pin_out_dummy,
      pin_out & p14 = pin_out_dummy,
      pin_out & p15 = pin_out_dummy	
   ):
      pins{ 
         &p0, &p1, &p2, &p3, &p4, &p5, &p6, &p7, 
         &p8, &p9, &p10, &p11, &p12, &p13, &p14, &p15 }
   {
      for( _number_of_pins = 0; _number_of_pins < max_pins; ++_number_of_pins ){
         if( pins[ _number_of_pins ] == & pin_out_dummy ){
             break;
         }            
      }
   }            

   uint_fast8_t number_of_pins() override {
      return _number_of_pins;               
   }   
   
   void write( uint_fast16_t x ) override {
      for( uint_fast8_t i = 0; i < _number_of_pins; i++ ){
         pins[ i ]->write( ( x & 0x01 ) != 0 );
         x = x >> 1;
      }         
   }
   
   void flush() override {
      for( uint_fast8_t i = 0; i < _number_of_pins; i++ ){
         pins[ i ]->flush();
      }         
   }    

};

/// output port from oc pins class
///
/// This class implements an output-only port made from port up to 8 oc pins.
class port_out_from_pins_oc_t : public port_out {
private:

   static constexpr int max_pins = 16;
   
   uint_fast8_t _number_of_pins;  

   // 8 must match the number of parameters of the constructor
   pin_oc * pins[ max_pins ];   
   
public:

   /// construct a port_out from up to 8 pin_oc's
   /// 
   /// This constructor creates a port_out from up to 8 pin_out pins.
   /// The first pin is the lowest pin in the port, etc.
   port_out_from_pins_oc_t(
      pin_oc & p0 = pin_oc_dummy,
      pin_oc & p1 = pin_oc_dummy,
      pin_oc & p2 = pin_oc_dummy,
      pin_oc & p3 = pin_oc_dummy,
      pin_oc & p4 = pin_oc_dummy,
      pin_oc & p5 = pin_oc_dummy,
      pin_oc & p6 = pin_oc_dummy,
      pin_oc & p7 = pin_oc_dummy,
      pin_oc & p8 = pin_oc_dummy,
      pin_oc & p9 = pin_oc_dummy,
      pin_oc & p10 = pin_oc_dummy,
      pin_oc & p11 = pin_oc_dummy,
      pin_oc & p12 = pin_oc_dummy,
      pin_oc & p13 = pin_oc_dummy,
      pin_oc & p14 = pin_oc_dummy,
      pin_oc & p15 = pin_oc_dummy	
   ):
      pins{ 
         &p0, &p1, &p2, &p3, &p4, &p5, &p6, &p7, 
         &p8, &p9, &p10, &p11, &p12, &p13, &p14, &p15 }
   {
      for( _number_of_pins = 0; _number_of_pins < max_pins; ++_number_of_pins ){
         if( pins[ _number_of_pins ] == & pin_oc_dummy ){
             break;
         }            
      }
   }            

   uint_fast8_t number_of_pins() override {
      return _number_of_pins;               
   }   
   
   void write( uint_fast16_t x ) override {
      for( uint_fast8_t i = 0; i < _number_of_pins; i++ ){
         pins[ i ]->write( ( x & 0x01 ) != 0 );
         x = x >> 1;
      }         
   }
   
   void flush() override {
      for( uint_fast8_t i = 0; i < _number_of_pins; i++ ){
         pins[ i ]->flush();
      }         
   } 

};

// ==========================================================================
//  
// port_oc
//
// ==========================================================================

/// oc port from oc pins class
//
/// This class implements an oc made from port up to 8 oc pins.
class port_oc_from_pins_t : public port_oc {
private:
   
   static constexpr int max_pins = 16;

   uint_fast8_t _number_of_pins;  

   // 8 must match the number of parameters of the constructor
   pin_oc * pins[ max_pins ];   
   
public:

   /// construct a port_oc from up to 8 pin_oc
   //
   /// This constructor creates a port_oc from up to 8 pin_oc pins.
   /// The first pin is the lowest pin in the port, etc.
   port_oc_from_pins_t(
      pin_oc & p0 = pin_oc_dummy,
      pin_oc & p1 = pin_oc_dummy,
      pin_oc & p2 = pin_oc_dummy,
      pin_oc & p3 = pin_oc_dummy,
      pin_oc & p4 = pin_oc_dummy,
      pin_oc & p5 = pin_oc_dummy,
      pin_oc & p6 = pin_oc_dummy,
      pin_oc & p7 = pin_oc_dummy,
      pin_oc & p8 = pin_oc_dummy,
      pin_oc & p9 = pin_oc_dummy,
      pin_oc & p10 = pin_oc_dummy,
      pin_oc & p11 = pin_oc_dummy,
      pin_oc & p12 = pin_oc_dummy,
      pin_oc & p13 = pin_oc_dummy,
      pin_oc & p14 = pin_oc_dummy,
      pin_oc & p15 = pin_oc_dummy
   ):
      pins{ 
         &p0, &p1, &p2, &p3, &p4, &p5, &p6, &p7, 
         &p8, &p9, &p10, &p11, &p12, &p13, &p14, &p15 }
   {
      for( _number_of_pins = 0; _number_of_pins <  max_pins; ++_number_of_pins ){
         if( pins[ _number_of_pins ] == & pin_oc_dummy ){
             break;
         }            
      }
   }            

   uint_fast8_t number_of_pins() override {
      return _number_of_pins;               
   }   
   
   uint_fast16_t read() override {
      uint_fast8_t result = 0;
      for( int_fast8_t i = _number_of_pins -1; i >=0; --i ){
         result = result << 1;
         if( pins[ i ]->read() ){
            result |= 0x01;            
         }
       }         
       return result;
   }
   
   void write( uint_fast16_t x ) override {
      for( uint_fast8_t i = 0; i < _number_of_pins; i++ ){
         pins[ i ]->write( ( x & 0x01 ) != 0 );
         x = x >> 1;
      }         
   }   
  
  void refresh() override {
      for( uint_fast8_t i = 0; i < _number_of_pins; i++ ){
         pins[ i ]->refresh();
      }         
   }    
   
   void flush() override {
      for( uint_fast8_t i = 0; i < _number_of_pins; i++ ){
         pins[ i ]->flush();
      }         
   }     

};


// ===========================================================================
//
// constructor functions
//
// ===========================================================================

/// return a port from pins
///@{ 

port_in_out_from_pins_t port_in_out_from(
   pin_in_out & p0 = pin_in_out_dummy,
   pin_in_out & p1 = pin_in_out_dummy,
   pin_in_out & p2 = pin_in_out_dummy,
   pin_in_out & p3 = pin_in_out_dummy,
   pin_in_out & p4 = pin_in_out_dummy,
   pin_in_out & p5 = pin_in_out_dummy,
   pin_in_out & p6 = pin_in_out_dummy,
   pin_in_out & p7 = pin_in_out_dummy,
   pin_in_out & p8 = pin_in_out_dummy,
   pin_in_out & p9 = pin_in_out_dummy,
   pin_in_out & p10 = pin_in_out_dummy,
   pin_in_out & p11 = pin_in_out_dummy,
   pin_in_out & p12 = pin_in_out_dummy,
   pin_in_out & p13 = pin_in_out_dummy,
   pin_in_out & p14 = pin_in_out_dummy,
   pin_in_out & p15 = pin_in_out_dummy
);

port_out_from_pins_t port_out_from(
   pin_out & p0 = pin_out_dummy,
   pin_out & p1 = pin_out_dummy,
   pin_out & p2 = pin_out_dummy,
   pin_out & p3 = pin_out_dummy,
   pin_out & p4 = pin_out_dummy,
   pin_out & p5 = pin_out_dummy,
   pin_out & p6 = pin_out_dummy,
   pin_out & p7 = pin_out_dummy,
   pin_out & p8 = pin_out_dummy,
   pin_out & p9 = pin_out_dummy,
   pin_out & p10 = pin_out_dummy,
   pin_out & p11 = pin_out_dummy,
   pin_out & p12 = pin_out_dummy,
   pin_out & p13 = pin_out_dummy,
   pin_out & p14 = pin_out_dummy,
   pin_out & p15 = pin_out_dummy
);

port_out_from_pins_oc_t port_out_from(
   pin_oc & p0 = pin_oc_dummy,
   pin_oc & p1 = pin_oc_dummy,
   pin_oc & p2 = pin_oc_dummy,
   pin_oc & p3 = pin_oc_dummy,
   pin_oc & p4 = pin_oc_dummy,
   pin_oc & p5 = pin_oc_dummy,
   pin_oc & p6 = pin_oc_dummy,
   pin_oc & p7 = pin_oc_dummy,
   pin_oc & p8 = pin_oc_dummy,
   pin_oc & p9 = pin_oc_dummy,
   pin_oc & p10 = pin_oc_dummy,
   pin_oc & p11 = pin_oc_dummy,
   pin_oc & p12 = pin_oc_dummy,
   pin_oc & p13 = pin_oc_dummy,
   pin_oc & p14 = pin_oc_dummy,
   pin_oc & p15 = pin_oc_dummy
);

port_in_from_pins_t port_in_from(
   pin_in & p0 = pin_in_dummy,
   pin_in & p1 = pin_in_dummy,
   pin_in & p2 = pin_in_dummy,
   pin_in & p3 = pin_in_dummy,
   pin_in & p4 = pin_in_dummy,
   pin_in & p5 = pin_in_dummy,
   pin_in & p6 = pin_in_dummy,
   pin_in & p7 = pin_in_dummy,
   pin_in & p8 = pin_in_dummy,
   pin_in & p9 = pin_in_dummy,
   pin_in & p10 = pin_in_dummy,
   pin_in & p11 = pin_in_dummy,
   pin_in & p12 = pin_in_dummy,
   pin_in & p13 = pin_in_dummy,
   pin_in & p14 = pin_in_dummy,
   pin_in & p15 = pin_in_dummy
);

port_oc_from_pins_t port_oc_from(
   pin_oc & p0 = pin_oc_dummy,
   pin_oc & p1 = pin_oc_dummy,
   pin_oc & p2 = pin_oc_dummy,
   pin_oc & p3 = pin_oc_dummy,
   pin_oc & p4 = pin_oc_dummy,
   pin_oc & p5 = pin_oc_dummy,
   pin_oc & p6 = pin_oc_dummy,
   pin_oc & p7 = pin_oc_dummy,
   pin_oc & p8 = pin_oc_dummy,
   pin_oc & p9 = pin_oc_dummy,
   pin_oc & p10 = pin_oc_dummy,
   pin_oc & p11 = pin_oc_dummy,
   pin_oc & p12 = pin_oc_dummy,
   pin_oc & p13 = pin_oc_dummy,
   pin_oc & p14 = pin_oc_dummy,
   pin_oc & p15 = pin_oc_dummy
);

///@}


// ===========================================================================
//
// implementations
//
// ===========================================================================

#ifdef _HWLIB_ONCE   
   
port_in_out_from_pins_t port_in_out_from(
   pin_in_out & p0,
   pin_in_out & p1,
   pin_in_out & p2,
   pin_in_out & p3,
   pin_in_out & p4,
   pin_in_out & p5,
   pin_in_out & p6,
   pin_in_out & p7, 
   pin_in_out & p8,
   pin_in_out & p9,
   pin_in_out & p10,
   pin_in_out & p11,
   pin_in_out & p12,
   pin_in_out & p13,
   pin_in_out & p14,
   pin_in_out & p15 
){
   return port_in_out_from_pins_t( 
      p0, p1, p2, p3, p4, p5, p6, p7, 
      p8, p9, p10, p11, p12, p13, p14, p15 );
}

port_out_from_pins_oc_t port_out_from(
   pin_oc & p0,
   pin_oc & p1,
   pin_oc & p2,
   pin_oc & p3,
   pin_oc & p4,
   pin_oc & p5,
   pin_oc & p6,
   pin_oc & p7, 
   pin_oc & p8,
   pin_oc & p9,
   pin_oc & p10,
   pin_oc & p11,
   pin_oc & p12,
   pin_oc & p13,
   pin_oc & p14,
   pin_oc & p15
){
   return port_out_from_pins_oc_t( 
      p0, p1, p2, p3, p4, p5, p6, p7, 
      p8, p9, p10, p11, p12, p13, p14, p15 );
}

port_out_from_pins_t port_out_from(
   pin_out & p0,
   pin_out & p1,
   pin_out & p2,
   pin_out & p3,
   pin_out & p4,
   pin_out & p5,
   pin_out & p6,
   pin_out & p7, 
   pin_out & p8,
   pin_out & p9,
   pin_out & p10,
   pin_out & p11,
   pin_out & p12,
   pin_out & p13,
   pin_out & p14,
   pin_out & p15
){
   return port_out_from_pins_t( 
      p0, p1, p2, p3, p4, p5, p6, p7, 
      p8, p9, p10, p11, p12, p13, p14, p15 );
}

port_in_from_pins_t port_in_from(
   pin_in & p0,
   pin_in & p1,
   pin_in & p2,
   pin_in & p3,
   pin_in & p4,
   pin_in & p5,
   pin_in & p6,
   pin_in & p7, 
   pin_in & p8,
   pin_in & p9,
   pin_in & p10,
   pin_in & p11,
   pin_in & p12,
   pin_in & p13,
   pin_in & p14,
   pin_in & p15
){
   return port_in_from_pins_t( 
      p0, p1, p2, p3, p4, p5, p6, p7, 
      p8, p9, p10, p11, p12, p13, p14, p15 );
}

port_oc_from_pins_t port_oc_from(
   pin_oc & p0,
   pin_oc & p1,
   pin_oc & p2,
   pin_oc & p3,
   pin_oc & p4,
   pin_oc & p5,
   pin_oc & p6,
   pin_oc & p7,
   pin_oc & p8,
   pin_oc & p9,
   pin_oc & p10,
   pin_oc & p11,
   pin_oc & p12,
   pin_oc & p13,
   pin_oc & p14,
   pin_oc & p15 
){
   return port_oc_from_pins_t( 
      p0, p1, p2, p3, p4, p5, p6, p7, 
      p8, p9, p10, p11, p12, p13, p14, p15 );
}

#endif // _HWLIB_ONCE


}; // namespace hwlib
