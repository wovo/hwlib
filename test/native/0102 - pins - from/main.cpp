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

void test_pin_in_out_from_in_out(){
   hwlib::pin_in_out_store s;
   hwlib::pin_in_out_from_in_out_t p = hwlib::pin_in_out_from( s );
   
   HWLIB_TEST_EQUAL( s.value,                false );
   HWLIB_TEST_EQUAL( s.is_output,            false );
   HWLIB_TEST_EQUAL( s.is_input,             false );
   HWLIB_TEST_EQUAL( s.read_count,           0 );   
   HWLIB_TEST_EQUAL( s.write_count,          0 );   
   HWLIB_TEST_EQUAL( s.direction_set_count,  0 );
   HWLIB_TEST_EQUAL( s.flush_count,          0 );
   HWLIB_TEST_EQUAL( s.refresh_count,        0 ); 
   
   p.write( 1 );
   HWLIB_TEST_EQUAL( s.read(),               1 );
   HWLIB_TEST_EQUAL( s.value,                1 );
   HWLIB_TEST_EQUAL( s.is_output,            false );
   HWLIB_TEST_EQUAL( s.is_input,             false );
   HWLIB_TEST_EQUAL( s.read_count,           1 );   
   HWLIB_TEST_EQUAL( s.write_count,          1 );   
   HWLIB_TEST_EQUAL( s.direction_set_count,  0 );
   HWLIB_TEST_EQUAL( s.flush_count,          0 );
   HWLIB_TEST_EQUAL( s.refresh_count,        0 ); 

   p.write( 0 );
   p.write( 0 );
   HWLIB_TEST_EQUAL( s.read(),               0 );
   HWLIB_TEST_EQUAL( s.value,                0 );
   HWLIB_TEST_EQUAL( s.is_output,            false );
   HWLIB_TEST_EQUAL( s.is_input,             false );
   HWLIB_TEST_EQUAL( s.read_count,           2 );   
   HWLIB_TEST_EQUAL( s.write_count,          3 );   
   HWLIB_TEST_EQUAL( s.direction_set_count,  0 );
   HWLIB_TEST_EQUAL( s.flush_count,          0 );
   HWLIB_TEST_EQUAL( s.refresh_count,        0 ); 

   p.refresh();
   HWLIB_TEST_EQUAL( s.value,                0 );
   HWLIB_TEST_EQUAL( s.is_output,            false );
   HWLIB_TEST_EQUAL( s.is_input,             false );
   HWLIB_TEST_EQUAL( s.read_count,           2 );   
   HWLIB_TEST_EQUAL( s.write_count,          3 );   
   HWLIB_TEST_EQUAL( s.direction_set_count,  0 );
   HWLIB_TEST_EQUAL( s.flush_count,          0 );
   HWLIB_TEST_EQUAL( s.refresh_count,        1 ); 
     
   p.flush();
   HWLIB_TEST_EQUAL( s.value,                0 );
   HWLIB_TEST_EQUAL( s.is_output,            false );
   HWLIB_TEST_EQUAL( s.is_input,             false );
   HWLIB_TEST_EQUAL( s.read_count,           2 );   
   HWLIB_TEST_EQUAL( s.write_count,          3 );   
   HWLIB_TEST_EQUAL( s.direction_set_count,  0 );
   HWLIB_TEST_EQUAL( s.flush_count,          1 );
   HWLIB_TEST_EQUAL( s.refresh_count,        1 ); 
     
   p.direction_set_input();
   HWLIB_TEST_EQUAL( s.value,                0 );
   HWLIB_TEST_EQUAL( s.is_output,            false );
   HWLIB_TEST_EQUAL( s.is_input,             1 );
   HWLIB_TEST_EQUAL( s.read_count,           2 );   
   HWLIB_TEST_EQUAL( s.write_count,          3 );   
   HWLIB_TEST_EQUAL( s.direction_set_count,  1 );
   HWLIB_TEST_EQUAL( s.flush_count,          1 );
   HWLIB_TEST_EQUAL( s.refresh_count,        1 ); 
     
   p.direction_set_output();
   HWLIB_TEST_EQUAL( s.value,                0 );
   HWLIB_TEST_EQUAL( s.is_output,            1 );
   HWLIB_TEST_EQUAL( s.is_input,             0 );
   HWLIB_TEST_EQUAL( s.read_count,           2 );   
   HWLIB_TEST_EQUAL( s.write_count,          3 );   
   HWLIB_TEST_EQUAL( s.direction_set_count,  2 );
   HWLIB_TEST_EQUAL( s.flush_count,          1 );
   HWLIB_TEST_EQUAL( s.refresh_count,        1 ); 
     
}

void test_pin_in_out_from_oc(){
   hwlib::pin_oc_store s;
   hwlib::pin_in_out_from_oc_t p = hwlib::pin_in_out_from( s );
   
   HWLIB_TEST_EQUAL( s.value,                false );
   HWLIB_TEST_EQUAL( s.read_count,           0 );   
   HWLIB_TEST_EQUAL( s.write_count,          0 );   
   HWLIB_TEST_EQUAL( s.flush_count,          0 );
   HWLIB_TEST_EQUAL( s.refresh_count,        0 ); 
   
   p.write( 1 );
   HWLIB_TEST_EQUAL( s.read(),               1 );
   HWLIB_TEST_EQUAL( s.value,                1 );
   HWLIB_TEST_EQUAL( s.read_count,           1 );   
   HWLIB_TEST_EQUAL( s.write_count,          1 );   
   HWLIB_TEST_EQUAL( s.flush_count,          0 );
   HWLIB_TEST_EQUAL( s.refresh_count,        0 ); 

   p.write( 0 );
   p.write( 0 );
   HWLIB_TEST_EQUAL( s.read(),               0 );
   HWLIB_TEST_EQUAL( s.value,                0 );
   HWLIB_TEST_EQUAL( s.read_count,           2 );   
   HWLIB_TEST_EQUAL( s.write_count,          3 );   
   HWLIB_TEST_EQUAL( s.flush_count,          0 );
   HWLIB_TEST_EQUAL( s.refresh_count,        0 ); 

   p.refresh();
   HWLIB_TEST_EQUAL( s.value,                0 );
   HWLIB_TEST_EQUAL( s.read_count,           2 );   
   HWLIB_TEST_EQUAL( s.write_count,          3 );   
   HWLIB_TEST_EQUAL( s.flush_count,          0 );
   HWLIB_TEST_EQUAL( s.refresh_count,        1 ); 
     
   p.flush();
   HWLIB_TEST_EQUAL( s.value,                0 );
   HWLIB_TEST_EQUAL( s.read_count,           2 );   
   HWLIB_TEST_EQUAL( s.write_count,          3 );   
   HWLIB_TEST_EQUAL( s.flush_count,          1 );
   HWLIB_TEST_EQUAL( s.refresh_count,        1 ); 

   // input => slave pin must go high
   p.direction_set_input();
   HWLIB_TEST_EQUAL( s.value,                1 ); 
   HWLIB_TEST_EQUAL( s.read_count,           2 );   
   HWLIB_TEST_EQUAL( s.write_count,          4 );    
   HWLIB_TEST_EQUAL( s.flush_count,          1 );
   HWLIB_TEST_EQUAL( s.refresh_count,        1 ); 
   
   // no-op for an input
   p.write( 0 );
   HWLIB_TEST_EQUAL( s.value,                1 ); 
   HWLIB_TEST_EQUAL( s.read_count,           2 );   
   HWLIB_TEST_EQUAL( s.write_count,          4 );   
   HWLIB_TEST_EQUAL( s.flush_count,          1 );
   HWLIB_TEST_EQUAL( s.refresh_count,        1 ); 

   p.direction_set_output();
   p.write( 0 );
   HWLIB_TEST_EQUAL( s.value,                0 );
   HWLIB_TEST_EQUAL( s.read_count,           2 );   
   HWLIB_TEST_EQUAL( s.write_count,          5 );   
   HWLIB_TEST_EQUAL( s.flush_count,          1 );
   HWLIB_TEST_EQUAL( s.refresh_count,        1 );   
   
   p.write( 1 );
   HWLIB_TEST_EQUAL( s.value,                1 );
   HWLIB_TEST_EQUAL( s.read_count,           2 );   
   HWLIB_TEST_EQUAL( s.write_count,          6 );   
   HWLIB_TEST_EQUAL( s.flush_count,          1 );
   HWLIB_TEST_EQUAL( s.refresh_count,        1 );    
  
   p.write( 0 );
   HWLIB_TEST_EQUAL( s.value,                0 );
   HWLIB_TEST_EQUAL( s.read_count,           2 );   
   HWLIB_TEST_EQUAL( s.write_count,          7 );   
   HWLIB_TEST_EQUAL( s.flush_count,          1 );
   HWLIB_TEST_EQUAL( s.refresh_count,        1 );      
}

int main(){
   test_pin_in_out_from_in_out();
   test_pin_in_out_from_oc();
   hwlib::test_end();
}   

