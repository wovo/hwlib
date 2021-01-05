#include "hwlib.hpp"
#include "windows.h"

int main(int argc, char **argv){
    
   // the window in which we want to print the line
   hwlib::target::window w( hwlib::xy( 128, 64 ));    
   w.clear();
    
   hwlib::line line( hwlib::xy( 20, 20 ), hwlib::xy( 30, 30 ), hwlib::green );
   line.draw( w );
   
   hwlib::circle circle( hwlib::xy( 40, 40 ), 20, hwlib::blue );
   circle.draw( w );
   
   hwlib::circle circle2( hwlib::xy( 30, 10 ), 10, hwlib::red );
   circle2.draw( w );
   
   hwlib::rectangle rect1( hwlib::xy( 50, 50 ), hwlib::xy( 20, 10 ), hwlib::yellow );
   rect1.draw( w );
   
   w.flush();
   
   // keep the window around until we close it
   for(;;){ w.poll(); }       
}

