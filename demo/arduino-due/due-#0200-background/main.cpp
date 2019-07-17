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
      
   void work() override{
      if( hwlib::now_us() > toggle_moment )      {
         toggle_moment += interval;
         state = ! state;
         pin.write( state );
      }
   }
};

int main( void ){
   auto led = hwlib::target::pin_out( 1, 27 );
   blinker blink_led( led, 100'000 );
   for(;;){
      hwlib::wait_ms( 1'000 );
   }
}  