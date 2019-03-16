// ==========================================================================
//
// File      : hwlib-ostream.hpp
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
	
	
// ===========================================================================
//
// console input & output functions, to be implemented by the targets
//
// ===========================================================================	

/// console character output function
///
/// This is the function used for console (ostream) output.
/// The embedded targets provide an implementation that writes
/// to the serial port. 
///
/// This definition is weak, which allows 
/// an application to provide its own definition.
void uart_putc( char c );
   
/// console character input function
///
/// This is the function used for console (istream) input.
/// The embedded targets provide an implementation that reads
/// from the serial port. 
///
/// This definition is weak, which allows 
/// an application to provide its own definition.
char uart_getc();
   
/// console character available check
///
/// This is the function used to check if the console (istream) input
/// has a character available.
/// The embedded targets provide an implementation that checks
/// the serial port. 
///
/// This definition is weak, which allows 
/// an application to provide its own definition.
bool uart_char_available();


// ===========================================================================
//
// the standard input (cin) and output cout, using the console IO functions
//
// ===========================================================================
   
/// \cond INTERNAL 
   
class cout_using_uart_putc : public ostream {
public:    

   void putc( char c ) override {
      uart_putc( c );
   }
   
   void flush() override {}

};
   
class cin_using_uart_getc : public istream {
public:    

   bool char_available() override {
      return uart_char_available();      
   }   
   
   char getc() override {
      return uart_getc();
   }
   
};
   
/// \endcond    

/// embedded output console
///
/// This is the embedded work-alike for std::cout.
/// The default implementation uses uart_putc
/// to write the characters.
///
/// This definition is weak, which allows 
/// an application to provide its own definition.
extern cout_using_uart_putc cout;   
 

/// embedded input console
///
/// This is the embedded work-alike for std::cin.
/// The default implementation uses uart_getc
/// to read the characters.
///
/// This definition is weak, which allows 
/// an application to provide its own definition.
extern cin_using_uart_getc cin;    


// ===========================================================================
//
// implementations
//
// ===========================================================================

#ifdef _HWLIB_ONCE   
   
cout_using_uart_putc HWLIB_WEAK cout;   
cin_using_uart_getc HWLIB_WEAK  cin; 

#endif // _HWLIB_ONCE

}; // namespace hwlib
