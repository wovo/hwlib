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

namespace hwlib {
    
// https://github.com/jprodgers/LoLshield

class lol_shield : public window, public background {
    uint16_t buffer[ 9 ];
    int row = 0;
    
    hwlib::target::pin_out row1;
    hwlib::port_out row_pins;
    
    hwlib::target::pin_out col1;
    hwlib::port_cout column_pins;
    
public:

   lol_shield():
      window( xy( 9, 11 ),
      
      row1(),
      row_pouins( row1 ),
      
      col1(),
      column_pins( col1 )
   {}
   
   void write_implementation( xy pos, color col ) override {
       if( col == white ){
           buffer[ pos. x ] |= ( 1 << pos.y );
       } else{
           buffer[ pos. x ] &= ~( 1 << pos.y );
       }
   }
   
   void flush() override {}
   
   void work() override {
      row = ( row + 1 ) % 9;
      columns 
   }   

};

};

int main( void ){
   auto led = hwlib::target::pin_out( hwlib::target::pins::led );
   blinker blink_led( led, 200'000 );
   for(;;){
      hwlib::wait_ms( 1'000 );
   }
}  
