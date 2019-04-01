// ==========================================================================
//
// File      : hwlib-native.hpp
// Part of   : C++ hwlib library for close-to-the-hardware OO programming
// Copyright : wouter@voti.nl 2017-2019
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

// this file contains Doxygen lines
/// @file

#ifndef HWLIB_NATIVE_H
#define HWLIB_NATIVE_H

#define _HWLIB_TARGET_WAIT_US_BUSY
#include HWLIB_INCLUDE( ../hwlib-all.hpp )
#include <iostream>
#include <Windows.h>
#include <SFML/Graphics.hpp>

namespace hwlib {
	
namespace target {
   
class window : public hwlib::window {
private:

   int m;
   sf::RenderWindow w;
   sf::Image image;
   
public:   

   window( xy size, int m = 5 ):
      hwlib::window( size ),
      m( m ),
      w( sf::VideoMode( m * size.x, m * size.y ), "HWLIB-SFML window" )
   {
      image.create( m * size.x, m * size.y );
      clear();
      flush();
   }	
   
   window( int x, int y, int m = 5 ): window( xy( x, y ), m ){}	
   
   void poll(){
      if ( w.isOpen() ){
        sf::Event event;
        while (w.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                w.close();
        }
      }	   
   }
   
   void write_implementation( 
      xy pos, 
      color col
   ) override {
      for( int x = 0; x < m; ++x ){
         for( int y = 0; y < m; ++y ){
            image.setPixel( 
               x + m * pos.x, y + m * pos.y, 
               ( col != hwlib::black ) ? sf::Color::Black : sf::Color::White );
         }
      }   
   }
   
   void flush() override {
	   w.clear();
      
sf::Texture texture;
texture.loadFromImage(image);
sf::Sprite sprite;
sprite.setTexture(texture, true);
w.draw(sprite);      
      
      w.display();
	   poll();
   }
   
}; // class window
	
};	// namespace target

#ifdef _HWLIB_ONCE

uint64_t now_ticks(){
   // https://stackoverflow.com/questions/1695288/getting-the-current-time-in-milliseconds-from-the-system-clock-in-windows	 
   
   FILETIME ft_now;
   GetSystemTimeAsFileTime( &ft_now );
   uint64_t ll_now = (LONGLONG)ft_now.dwLowDateTime + ((LONGLONG)(ft_now.dwHighDateTime) << 32LL);   
   return ll_now / 10;
}   

uint64_t ticks_per_us(){
   return 1;
}   

uint64_t now_us(){
   return now_ticks() / ticks_per_us();
}   

void wait_us_busy( int_fast32_t n ){
   auto end = now_us() + n;
   while( now_us() < end ){}
}

/*

void wait_ns( int_fast32_t n ){
   wait_us( n / 1'000 );
}

void wait_us( int_fast32_t n ){
   
}

void wait_ms( int_fast32_t n ){
   wait_us( n * 1'000 );
}

uint_fast64_t now_us(){
   return 0;
}   
 
*/

void uart_putc( char c ){
   std::cout << c << std::flush;
}

char uart_getc(){
   return std::getchar();   
}

bool HWLIB_WEAK uart_char_available(){
   return 1;
}

void *__gxx_personality_v0;

#endif // #ifdef HBLIB_ONCE

}; // namespace hwlib

#endif // HWLIB_NATIVE_H