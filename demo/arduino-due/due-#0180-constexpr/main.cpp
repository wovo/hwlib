#include "hwlib.hpp"

namespace target = hwlib::target;

constexpr double pow( double v, int n ){
   return ( n == 0 ) 
      ? 1 
      : v * pow( v, n - 1 );
}

constexpr int fac( int n ){
   return ( n ==  0 ) 
      ? 1 
      : n * fac( n - 1 );
}

constexpr double sine( double angle ){
   double value = 0;
   for( int i = 1; i < 10; i += 2 ){
      value += (( i % 4 ) == 1 ? 1 : -1 ) * pow( angle, i ) / fac( i );
   }   
   return value;
}

constexpr double pi = 3.14;

constexpr int height = static_cast< int >( 1000 * sine( 2 * pi / 12 ));

int main( void ){
    
   // wait for the terminal emulator to start up
   hwlib::wait_ms( 1'000 );

   hwlib::cout << "1000 * sin( 30 ) = " << height << "\n";

}
