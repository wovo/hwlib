// ==========================================================================
//
// File      : hwlib-stream-mux.hpp
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

class ostream_prefix : ostream {
private:

   ostream & minion;
   const char marker;

public:

   ostream_mux( ostream & minion, char marker ): 
      minion( minion ), marker( marker )
   {}

   void putc( char c ) override {
      minion.putc( marker );
      minion.putc( c );
   }
 
   void flush() override {
      minion.flush();
   }

}; // class ostream_prefix

class istream_mux : ostream {
private:

   ostream & minion;

public:

   ostream_mux( ostream & minion ): minion( minion ){}

   void putc( char x ) override {
   }
 
   void flush() override {
   }

}; // class ostream_mux
   
}; // namespace hwlib
