// ==========================================================================
//
// File      : hwlib-matrix-keypad.hpp
// Part of   : C++ hwlib library for close-to-the-hardware OO programming
// Copyright : wouter@voti.nl 2016-2019
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
   
/// matrix of switches (keypad) interface
//
/// This class interfaces to a matrix of keys (switches).
class matrix_of_switches {
private:

   port_direct_from_oc_t  output;
   port_direct_from_in_t  input;

public:

   /// the number of columns and rows
   xy size;

   /// create a matrix interface from the row and column pins
   //
   /// This constructor creates a matrix interface from the
   /// ports that contain the pins that connect to the columns (x direction) 
   /// and the columns (y direction).
   /// The column pins must be an open-collector port,
   /// the row pins must be an input port that has (internal or external)
   /// pull-up resistors.
   matrix_of_switches( port_oc & output, port_in & input ):
      output( output ), 
      input( input ),
      size( output.number_of_pins(), input.number_of_pins() )
   {}

   /// test whether a particular switch is closed
   //
   /// This function returns whether the switch at column x
   /// and row y is closed.
   /// It doesn't suppress bouncing.
   bool switch_is_closed_at( xy v ){
       
      // make (only) the x'th output pin low 
      output.write( ~ ( 0x01 << v.x ));

      // wait for the input level to settle
      wait_us( 1'000 );
      
      // returns whether the y'th input pin is low
      return ( input.read() & ( 0x01 << v.y )) == 0;
   }
   
}; // class class matrix_of_switches

/// istream from a matrix_of_switches
//
/// This class template turns a keypad matrix into an istream
/// (a character input stream).
/// The template parameter is the number of characters in
/// the translation string.
template< int N >
class keypad : public istream {
private:
   matrix_of_switches & matrix;
   char translation[ N ];
   char previous = '\0';
   char buffer = '\0';
   long long int last_timestamp;

public:

   /// create a keypad from a switch matrix and a translation string
   //
   /// The translation string translates a pressed key to a character.
   /// The characters in the string correspond to the keys starting
   /// at the top left (1,1), proceeding colum-first.
   /// Excess characters in the translation string are ignored,
   /// and excess keys are translated to '\0'.
   keypad( 
      matrix_of_switches & matrix,
      const char *translation_string
    ):
      matrix( matrix ),
      last_timestamp( now_us() )
    {
       // fill the translation string, add \0's when the
       // tr parameter is exhausted 
       for( uint_fast8_t i = 0; i < N; ++i ){
           if( *translation_string != '\0' ){
               translation[ i ] = *translation_string++;
           } else {
               translation[ i ] = '\0';
           }
       }    
    }  
    
    /// return whether the requested key is pressed
    //
    /// This function repports whether the key corresponding
	/// to the indicated character is pressed.
	///
    /// This function does not suppress bouncing.
    bool is_pressed( char c ){
       for( auto v : all( matrix.size )){
          if( c == translation[ v.x + matrix.size.x * v.y ] ){
             if( matrix.switch_is_closed_at( v )){
                return true;
             }
          }
       }
       return false;
    }

    /// return a press character or '\0' for none
    //
    /// This function returns the character corresponding to 
    /// a switch that is closed, or '\0' when no switch
    /// is closed (or a switch is closed that has no
    /// translation).
	///
    /// This function does not suppress bouncing.
    char pressed(){
       for( auto v : all( matrix.size )){
          if( matrix.switch_is_closed_at( v )){
             return translation[ v.x + matrix.size.x * v.y ];
          }
       }
       return '\0';
    }
    
    /// return whether a character is available
    //
    /// This function checks whether a next character is available.
    /// When it returns true, an (immediately) following getc() call
    /// will not block. 
    bool char_available() override {
       if( ( last_timestamp + 50'000ULL ) > now_us() ){
          return false;
       }
       last_timestamp = now_us();
       
       buffer = pressed();
       if( buffer == '\0' ){
          previous = '\0';
          return false;
       }
       return buffer != previous;
    }
    
    /// return the next available character
    //
    /// This function returns the next available character,
    /// if necessary it will block waiting for it.
    /// Bouncing is suppressed by checking the keypad matrix
    /// at most once every 50 ms.
    char getc() override {
       if( buffer == '\0' ) {
          while( ! char_available() ){
             wait_ms( 1 );
          }
       }
    
       previous = buffer;
       buffer = '\0';
       return previous;
    }
    
}; // class keypad  
   
}; // namespace hwlib
