#include "hwlib.hpp"

#pragma GCC diagnostic ignored "-Wparentheses"
#pragma GCC optimize ("rtti")

#include <boost/units/systems/si.hpp>
#include <boost/units/systems/si/prefixes.hpp>
#include <boost/units/io.hpp>

const auto meter = boost::units::si::meter;

int main( void ){
    
   // wait for the terminal emulator to start up
   hwlib::wait_ms( 1'000 );

   auto m1 = 10 * meter;
   
   hwlib::cout << m1 << "\n" << hwlib::flush;

}
