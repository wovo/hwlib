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
/// Note: the constructor of a bckground object must take care not to
/// invoke waiting while the object construction isn't yet finished.
///
class background_base : public noncopyable {
private:

   static background_base * first;
   static background_base * current;
   static bool running;
   background_base * next;	

public:

   /// background constructor
   ///
   /// The constructor will add this backround item 
   /// to the list of background items.
   background_base():
	  next( first )
   {
      first = this;	  
   }
   
   /// background destructor
   ///
   /// The destructor will remove this background item 
   /// from the list of background items.
   ~background_base(){
	   
      // find the pointer that points to us
      for( background_base **p = &first; *p != nullptr; p = &(*p)->next ){
         if( (*p) == this ){
			 
            //remove us from the list:
            // make it point to the next background item
            (*p) = next;
            return;			
		 }
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

   /// do background work
   ///
   /// This function is called by the wait functions to do background work.
   static void do_background_work(){
	 
      // do not run any background work when called from background work:
      // this would seriously impact stack use and delay granularity
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
         current->base_work();
         running = false;
		 
		 // next time round, it is the turn of the next work item in the list
		 current = current->next;
	  }		  
   }
   
protected:

   virtual void base_work() = 0;    
   
};

class background : public background_base {
private:

   void base_work() override {
      work();
   }

    
public:    
   /// background work function
   ///
   /// This function will be called to do backround work for its class.
   virtual void work() = 0;     

};

// cyclic dependency...
uint_fast64_t now_us();

class periodic : public background_base {
private:    

   const uint_fast64_t period;
   uint_fast64_t next_moment;
   
private:

   void base_work() override {
      auto now = now_us();       
      if( now > next_moment ){
          next_moment += period;
          work();
      }    
   }

    
public:    

   periodic( uint_fast64_t period ):
      period( period ), next_moment( now_us() )
   {}
    
   /// background work function
   ///
   /// This function will be called to do backround work for its class.
   virtual void work() = 0;           
   
};

// ===========================================================================
//
// implementations
//
// ===========================================================================

#ifdef _HWLIB_ONCE

background_base * background_base::first   = nullptr;
background_base * background_base::current = nullptr;
bool              background_base::running = false;

#endif // #ifdef _HWLIB_ONCE

}; // namespace hwlib
