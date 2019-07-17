// ==========================================================================
//
// File      : hwlib-background.hpp
// Part of   : C++ hwlib library for close-to-the-hardware OO programming
// Copyright : wouter@voti.nl 2017-2019
//
// Distributed under the Boost Software License, Version 1.0.
// (Sepair	e accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

// included only via hwlib.hpp, hence no multiple-include guard is needed

// this file contains Doxygen lines
/// @file

namespace hwlib {


// ==========================================================================
//
// background
//
// ==========================================================================

class background;

class background {
private:

   static background * first;
   background * next;	

public:

   virtual void work() = 0;   	 
   
   background(){
      next = first;
      first = this;	  
   }
   
   ~background(){
      for( background *p = first; p != nullptr; p = p->next ){
         if( p->next == this ){
            p->next = next;
            return;			
		 }
	  }		  
   }

   static void do_background_work(){
      static bool active = false;;
      if( active ){
		  return;
      }
      active = true;	  
      for( background *p = first; p != nullptr; p = p->next ){
         p->work();
	  }		  
	  active = false;
   }	   
   
};

// ===========================================================================
//
// implementations
//
// ===========================================================================

#ifdef _HWLIB_ONCE

background * background::first = nullptr;

#endif // #ifdef _HWLIB_ONCE



}; // namespace hwlib
