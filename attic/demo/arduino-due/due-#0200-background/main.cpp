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
   
   auto led1   = hwlib::target::pin_out{ hwlib::target::pins::d6  };
   auto led2   = hwlib::target::pin_out{ hwlib::target::pins::d7  };
   auto led3   = hwlib::target::pin_out{ hwlib::target::pins::d8  };
   auto led4   = hwlib::target::pin_out{ hwlib::target::pins::d9  };
   auto led5   = hwlib::target::pin_out{ hwlib::target::pins::d10 };
   auto led6   = hwlib::target::pin_out{ hwlib::target::pins::d11 };
   auto led7   = hwlib::target::pin_out{ hwlib::target::pins::d12 };
   auto led8   = hwlib::target::pin_out{ hwlib::target::pins::d13 };
   auto leds   = hwlib::port_out_from( led1, led2, led3, led4, led5, led6, led7, led8 );   
   
   blinker blink_led( led, 100'000 );
   for(;;){
      hwlib::wait_ms( 1'000 );
   }
}  