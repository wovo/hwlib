// ==========================================================================
//
// hwlib test.
//
// This causes some trouble with the MingW linker, because it doesn't
// handle weak definitions. Hence being weak is sufficient for an embedded
// build, but not for a windows-hosted build.
//
// (c) Wouter van Ooijen (wouter@voti.nl) 2017
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt) 
//
// ==========================================================================

// test the pin stores (which are itself meant for testing...)

#include "hwlib.hpp"

void test_in_out( hwlib::pin_in_out_dummy_t & d ){  
   (void) d.read();
   d.write( d.read() );
   d.direction_set_input();
   d.direction_set_output();
   d.refresh();
   d.flush();
}

void test_in( hwlib::pin_in_dummy_t & d ){  
   (void) d.read();
   d.refresh();
}

void test_out( hwlib::pin_out_dummy_t & d ){  
   d.write( 0 );
   d.flush();
}

void test_oc( hwlib::pin_oc_dummy_t & d ){  
   (void) d.read();
   d.write( d.read() );
   d.refresh();
   d.flush();
}

int main(){
   test_in_out( hwlib::pin_in_out_dummy );
   hwlib::pin_in_out_dummy_t p1;
   test_in_out( p1 );
   HWLIB_TEST_EQUAL( sizeof( p1 ), sizeof( void * ) );
   
   test_in( hwlib::pin_in_dummy );
   hwlib::pin_in_dummy_t p2;
   test_in( p2 );
   HWLIB_TEST_EQUAL( sizeof( p2 ), sizeof( void * ) );
   
   test_out( hwlib::pin_out_dummy );
   hwlib::pin_out_dummy_t p3;
   test_out( p3 );
   HWLIB_TEST_EQUAL( sizeof( p3 ), sizeof( void * ) );
   
   test_oc( hwlib::pin_oc_dummy );
   hwlib::pin_oc_dummy_t p4;
   test_oc( p4 );
   HWLIB_TEST_EQUAL( sizeof( p4 ), sizeof( void * ) );
   
   hwlib::test_end();
}   

