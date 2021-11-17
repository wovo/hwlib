// ==========================================================================
//
// File      : hwlib-apa102.hpp
// Part of   : C++ hwlib library for close-to-the-hardware OO programming
// Copyright : wouter@voti.nl 2021
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
   

/// \brief
/// APA102 RGB LED strip
/// \details
/// This class template implements an interface to a strip
/// of APA102 GRB LEDs.
///
/// The template parameter is the number of LEDs in the strip.
///
/// The interface is buffered: all writes
/// are buffered in memory until flush() is called.
///
/// The strip must be powered with 5V.
/// Take care: the current for one LED fully on is 60 mA.
/// For a strip of more than say 10 LEDs you need to take precausions
/// for the current.
///
/// In my experience the digital inputs of an APA102 can be
/// driven by 3.3V GPIO pins.


// ==========================================================================
//
// apa102
//
// ==========================================================================

template< int n >
class apa102 : public window {
private:
   pin_out & ci;
   pin_out & di;
   std::array< hwlib::color, n > pixels;
   
   void write_byte( uint8_t b ){
      for( int i = 0; i < 8; ++i ){
         hwlib::wait_us( 1 );
         di.write( ( b & 0x80 ) != 0 ); di.flush();
         b = b << 1;
         ci.write( 0 ); ci.flush();
         hwlib::wait_us( 1 );
         ci.write( 1 ); ci.flush();
         hwlib::wait_us( 1 );
      }         
   }
   
  void write_word( uint32_t w ){
      write_byte( w >> 24 );
      write_byte( w >> 16 );
      write_byte( w >>  8 );
      write_byte( w >>  0 );
   }
   
   void write_implementation( 
      xy pos, 
      color col   
   ) override {
      pixels[ pos.x ] = col;
   }   
   
public:
   apa102( pin_out & ci, pin_out & di ):
      window( xy( n, 1 ) ), ci( ci ), di( di )
   {}
   
   void flush() override {
      write_word( 0x00000000 );
      for( auto c : pixels ){
          write_byte( 0xFF );
          write_byte( c.blue );
          write_byte( c.green );
          write_byte( c.red );
      }
      write_word( 0xFFFFFFFF );
   }
};

}; // namespace hwlib
