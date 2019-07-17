#include "hwlib.hpp"

class blinker : public hwlib::background {
private:
   hwlib::pin_out & pin;    
   uint_fast64_t interval;
   uint_fast64_t toggle_moment;
   bool state;

public:    

   blinker( hwlib::pin_out & pin, uint_fast64_t interval  ):
      pin( pin ), 
      interval( interval ), 
      toggle_moment( hwlib::now_us() ),
      state( false )
   {}
      
   void work() override {
      if( hwlib::now_us() > toggle_moment ){
         toggle_moment += interval;
         state = ! state;
         pin.write( state );
         pin.flush();
      }
   }
};

int main( void ){
   auto led = hwlib::target::pin_out( hwlib::target::pins::led );
   blinker blink_led( led, 200'000 );
   for(;;){
      hwlib::wait_ms( 1'000 );
   }
}  
