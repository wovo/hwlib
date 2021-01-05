#include "hwlib.hpp"

int main( void ){
	
   namespace target = hwlib::target;   
   
   // wait for the terminal emulator to start up
   hwlib::wait_ms( 1'000 );
   
   hwlib::cout << "matrix keypad robot arm control demo " << "\n";   

   auto out0 = target::pin_oc( target::pins::a4 );
   auto out1 = target::pin_oc( target::pins::a5 );
   auto out2 = target::pin_oc( target::pins::a6 );
   auto out3 = target::pin_oc( target::pins::a7 );

   auto in0  = target::pin_in( target::pins::a0 );
   auto in1  = target::pin_in( target::pins::a1 );
   auto in2  = target::pin_in( target::pins::a2 );
   auto in3  = target::pin_in( target::pins::a3 );
   
   in0.pullup_enable();
   in1.pullup_enable();
   in2.pullup_enable();
   in3.pullup_enable();
   
   auto out_port = hwlib::port_oc_from( out0, out1, out2, out3 );
   auto in_port  = hwlib::port_in_from( in0,  in1,  in2,  in3  );
   auto matrix   = hwlib::matrix_of_switches( out_port, in_port );
   auto keypad   = hwlib::keypad< 16 >( matrix, "123A456B789C*0#D" );   
	
   auto servo_1_pin = hwlib::target::pin_out( hwlib::target::pins::d6 );
   auto servo_1 = hwlib::servo_background( servo_1_pin );
   auto servo_2_pin = hwlib::target::pin_out( hwlib::target::pins::d7 );
   auto servo_2 = hwlib::servo_background( servo_2_pin );
   
   struct {
	  int index; 
      char key;
	  hwlib::servo & servo;
	  const char * name;
      int degrees;      
   } servos[] = { 
	   { 0, '1', servo_1, "1 table", 1500 },
       { 1, '2', servo_2, "2 shoulder", 1500 }
   };	   
   int selected = 0;
   
   for(;;){
      auto last = selected;
      for( auto & s : servos ){
         s.servo.write_us( s.degrees );
         if( keypad.is_pressed( s.key )){
            selected = s.index;
         }
      }
	  if( selected != last ){                                        
         hwlib::cout << "select servo " << servos[ selected ].name << "\n";
	  }
	  
	  int d = 0;
	  if( keypad.is_pressed( 'A' )){
		 d = 10;
      }		 
	  if( keypad.is_pressed( 'B' )){
		 d = 1;
      }		 
	  if( keypad.is_pressed( 'C' )){
		 d = -1;
      }	  
	  if( keypad.is_pressed( 'D' )){
         d = -10;
      }
	  if( d != 0 ){
         auto & s = servos[ selected ];
		 s.degrees += d;
		 if( s.degrees < 500 ) s.degrees = 500;
		 if( s.degrees > 2500 ) s.degrees = 2500;
		 hwlib::cout << s.degrees << "\n" ;		  
      }
      hwlib::wait_ms( 10 );
   }

}  