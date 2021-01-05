#include <iostream>

#pragma GCC diagnostic ignored "-Wparentheses"
#pragma GCC optimize ("rtti")

#include <boost/units/systems/si.hpp>
#include <boost/units/systems/cgs/length.hpp>
#include <boost/units/io.hpp>

const auto meter = 1.0 * boost::units::si::meter;
const auto s     = 1.0 * boost::units::si::second;

void print( decltype( meter / s ) v ){
    std::cout << "velocity = " << v << "\n";
}

int main(){

   auto gravity = 10.0 * meter / ( s * s );
   auto duration = 2.0 * s;
   
   print( gravity * duration );

}
