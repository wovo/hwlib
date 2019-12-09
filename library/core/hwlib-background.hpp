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

/// background processing
//
/// This class implements run-to-completion style background processing.
///
/// A class that needs background processing must inherit from background
/// and implement the work function. This work function will be called
/// from the wait_s(), wait_ms(), wait_us() etc. functions.
///
/// When an application contains background work, 
/// all plain wait functions can take longer than the specified time, 
/// up to the run time of the longest runtime of the work() functions.
///
/// No background work will be done from delay calls made while
/// a work() function is running.
///
/// For all background jobs: be careful to preserve the object!
///
class background : public noncopyable {
private:

   static background * first;
   static background * current;
   static bool running;
   background * next;	

public:

   /// background constructor
   ///
   /// The constructor will add this backround item 
   /// to the list of backround items.
   background():
	  next( first )
   {
      first = this;	  
   }
   
   /// background destructor
   ///
   /// The destructor will remove this backround item 
   /// from the list of backround items.
   ~background(){
	   
      // find the pointer that points to us
      for( background **p = &first; *p != nullptr; p = &(*p)->next ){
         if( (*p) == this ){
			 
			//remove us from the list:
			// make it point to the next background itenm
            (*p) = next;
            return;			
		 }
	  }		  
   }

   /// background work function
   ///
   /// This function will be called to do backround work for its class.
   virtual void work() = 0;   	 
   
   /// do background work
   ///
   /// This function is called by the wait functions to do background work.
   static void do_background_work(){
	 
      // do not run any background work when called from background
	  // work: this would seriously impact stack use and delay granularity
	  if( running ){
         return;
      }		 
	   
      // if no current work object, start at the start of the list
      if( current == nullptr ){
         current = first;
      }
	  
	  // if there is a current work item
      if( current != nullptr ){
		  
		 // run it	  
		 running = true;
         current->work();
         running = false;
		 
		 // next time, it is the turn of the next work item in the list
		 current = current->next;
	  }		  
   }
   
   /// keep doing background work
   ///
   /// Call this function instead of terminating the application
   /// to continue performing the background work.
   static void HWLIB_NORETURN run(){
      for(;;){
         do_background_work();       
      }
   }
   
};

// ===========================================================================
//
// implementations
//
// ===========================================================================

#ifdef _HWLIB_ONCE

background * background::first   = nullptr;
background * background::current = nullptr;
bool         background::running = false;

#endif // #ifdef _HWLIB_ONCE

}; // namespace hwlib
