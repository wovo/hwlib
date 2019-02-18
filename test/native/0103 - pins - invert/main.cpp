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

void test_invert_from_in_out(){
   hwlib::pin_in_out_store d;    
   hwlib::pin_invert_from_in_out_t p = hwlib::invert( d );

   HWLIB_TEST_EQUAL( d.value,                false );
   HWLIB_TEST_EQUAL( d.is_output,            false );
   HWLIB_TEST_EQUAL( d.is_input,             false );
   HWLIB_TEST_EQUAL( d.read_count,           0 );   
   HWLIB_TEST_EQUAL( d.write_count,          0 );   
   HWLIB_TEST_EQUAL( d.direction_set_count,  0 );
   HWLIB_TEST_EQUAL( d.flush_count,          0 );
   HWLIB_TEST_EQUAL( d.refresh_count,        0 );
   
   p.write( 1 );
   HWLIB_TEST_EQUAL( p.read(),               1 );
   HWLIB_TEST_EQUAL( d.value,                0 );
   p.write( 0 );
   HWLIB_TEST_EQUAL( p.read(),               0 );
   HWLIB_TEST_EQUAL( d.value,                1 );
   HWLIB_TEST_EQUAL( d.write_count,          2 );    
   HWLIB_TEST_EQUAL( d.read_count,           2 );    

   p.flush();   
   HWLIB_TEST_EQUAL( d.flush_count,          1 );
   HWLIB_TEST_EQUAL( d.refresh_count,        0 );
   p.refresh();   
   HWLIB_TEST_EQUAL( d.flush_count,          1 );
   HWLIB_TEST_EQUAL( d.refresh_count,        1 );
   
   HWLIB_TEST_EQUAL( d.direction_set_count,  0 );
   p.direction_set_output();
   HWLIB_TEST_EQUAL( d.is_output,            1 );
   HWLIB_TEST_EQUAL( d.is_input,             0 );
   HWLIB_TEST_EQUAL( d.direction_set_count,  1 );
   p.direction_set_input();
   HWLIB_TEST_EQUAL( d.is_output,            0 );
   HWLIB_TEST_EQUAL( d.is_input,             1 );
   HWLIB_TEST_EQUAL( d.direction_set_count,  2 );
   
}

void test_invert_from_in(){
   hwlib::pin_in_store d;    
   hwlib::pin_invert_from_in_t p = hwlib::invert( d );

   HWLIB_TEST_EQUAL( d.value,                false );
   HWLIB_TEST_EQUAL( d.read_count,           0 );    
   HWLIB_TEST_EQUAL( d.refresh_count,        0 );
   
   d.value = 0;
   HWLIB_TEST_EQUAL( p.read(),               1 );
   d.value = 1;
   HWLIB_TEST_EQUAL( p.read(),               0 );
   HWLIB_TEST_EQUAL( d.read_count,           2 );    

   HWLIB_TEST_EQUAL( d.refresh_count,        0 );
   p.refresh();   
   HWLIB_TEST_EQUAL( d.refresh_count,        1 );
      
}

void test_invert_from_out(){
   hwlib::pin_out_store d;    
   hwlib::pin_invert_from_out_t p = hwlib::invert( d );

   HWLIB_TEST_EQUAL( d.value,                false );  
   HWLIB_TEST_EQUAL( d.write_count,          0 );   
   HWLIB_TEST_EQUAL( d.flush_count,          0 );
   
   p.write( 1 );
   HWLIB_TEST_EQUAL( d.value,                0 );
   p.write( 0 );
   HWLIB_TEST_EQUAL( d.value,                1 );
   HWLIB_TEST_EQUAL( d.write_count,          2 );    

   HWLIB_TEST_EQUAL( d.flush_count,          0 );
   p.flush();   
   HWLIB_TEST_EQUAL( d.flush_count,          1 );
   
}

void test_invert_from_oc(){
   hwlib::pin_oc_store d;    
   hwlib::pin_invert_from_oc_t p = hwlib::invert( d );

   HWLIB_TEST_EQUAL( d.value,                false );
   HWLIB_TEST_EQUAL( d.read_count,           0 );   
   HWLIB_TEST_EQUAL( d.write_count,          0 );   
   HWLIB_TEST_EQUAL( d.flush_count,          0 );
   HWLIB_TEST_EQUAL( d.refresh_count,        0 );
   
   p.write( 1 );
   HWLIB_TEST_EQUAL( p.read(),               1 );
   HWLIB_TEST_EQUAL( d.value,                0 );
   p.write( 0 );
   HWLIB_TEST_EQUAL( p.read(),               0 );
   HWLIB_TEST_EQUAL( d.value,                1 );
   HWLIB_TEST_EQUAL( d.write_count,          2 );    
   HWLIB_TEST_EQUAL( d.read_count,           2 );    

   p.flush();   
   HWLIB_TEST_EQUAL( d.flush_count,          1 );
   HWLIB_TEST_EQUAL( d.refresh_count,        0 );
   p.refresh();   
   HWLIB_TEST_EQUAL( d.flush_count,          1 );
   HWLIB_TEST_EQUAL( d.refresh_count,        1 );
    
}

int main(){
   test_invert_from_in_out();
   test_invert_from_in();
   test_invert_from_out();
   test_invert_from_oc();
   hwlib::test_end();
}   

