#include "hwlib.hpp"

namespace hwlib {
    
}

class blinker3 : public hwlib::background {
private:
   hwlib::pin_out & pin;    
   uint_fast64_t interval;
   uint_fast64_t toggle_moment;
   bool state;

public:    

   blinker3( hwlib::pin_out & pin, uint_fast64_t interval  ):
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
    
   auto led1   = hwlib::target::pin_out{ hwlib::target::pins::d6  };
   auto led2   = hwlib::target::pin_out{ hwlib::target::pins::d7  };
   auto led3   = hwlib::target::pin_out{ hwlib::target::pins::d8  };
   auto led4   = hwlib::target::pin_out{ hwlib::target::pins::d9  };
   auto led5   = hwlib::target::pin_out{ hwlib::target::pins::d10 };
   auto led6   = hwlib::target::pin_out{ hwlib::target::pins::d11 };
   auto led7   = hwlib::target::pin_out{ hwlib::target::pins::d12 };
   auto led8   = hwlib::target::pin_out{ hwlib::target::pins::d13 };
   auto leds   = hwlib::port_out_from( led1, led2, led3, led4, led5, led6, led7, led8 );
   //hwlib::kitt( leds );
   
   hwlib::blinker b1( led1, 200'000 );
   hwlib::blinker b2( led2, 230'000 );
   hwlib::blinker b3( led3, 180'000 );
   hwlib::blinker b4( led4, 420'000 );
   hwlib::blinker b5( led5, 190'000 );
   hwlib::blinker b6( led6, 330'000 );   
   hwlib::blinker b7( led7, 150'000 );
   hwlib::blinker b8( led8, 380'000 );
   
   hwlib::background::run();
}   