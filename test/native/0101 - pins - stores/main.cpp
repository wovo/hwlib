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

void test_in_out_store(){
   hwlib::pin_in_out_store p;
   
   HWLIB_TEST_EQUAL( p.value,                false );
   HWLIB_TEST_EQUAL( p.is_output,            false );
   HWLIB_TEST_EQUAL( p.is_input,             false );
   HWLIB_TEST_EQUAL( p.read_count,           0 );   
   HWLIB_TEST_EQUAL( p.write_count,          0 );   
   HWLIB_TEST_EQUAL( p.direction_set_count,  0 );
   HWLIB_TEST_EQUAL( p.flush_count,          0 );
   HWLIB_TEST_EQUAL( p.refresh_count,        0 );
   
   p.direction_set_output();
   
   HWLIB_TEST_EQUAL( p.value,                false );
   HWLIB_TEST_EQUAL( p.is_output,            true );
   HWLIB_TEST_EQUAL( p.is_input,             false );
   HWLIB_TEST_EQUAL( p.read_count,           0 );   
   HWLIB_TEST_EQUAL( p.write_count,          0 );   
   HWLIB_TEST_EQUAL( p.direction_set_count,  1 );
   HWLIB_TEST_EQUAL( p.flush_count,          0 );
   HWLIB_TEST_EQUAL( p.refresh_count,        0 ); 
  
   p.direction_set_input();
   
   HWLIB_TEST_EQUAL( p.value,                false );
   HWLIB_TEST_EQUAL( p.is_output,            false );
   HWLIB_TEST_EQUAL( p.is_input,             true );
   HWLIB_TEST_EQUAL( p.read_count,           0 );   
   HWLIB_TEST_EQUAL( p.write_count,          0 );   
   HWLIB_TEST_EQUAL( p.direction_set_count,  2 );
   HWLIB_TEST_EQUAL( p.flush_count,          0 );
   HWLIB_TEST_EQUAL( p.refresh_count,        0 );   
   
   p.write( 1 );
   
   HWLIB_TEST_EQUAL( p.value,                1 );
   HWLIB_TEST_EQUAL( p.is_output,            false );
   HWLIB_TEST_EQUAL( p.is_input,             true );
   HWLIB_TEST_EQUAL( p.read_count,           0 );   
   HWLIB_TEST_EQUAL( p.write_count,          1 );   
   HWLIB_TEST_EQUAL( p.direction_set_count,  2 );
   HWLIB_TEST_EQUAL( p.flush_count,          0 );
   HWLIB_TEST_EQUAL( p.refresh_count,        0 );   
   
   HWLIB_TEST_EQUAL( p.read(),               1 );
   HWLIB_TEST_EQUAL( p.read_count,           1 );   
   
   p.write( 0 );
   
   HWLIB_TEST_EQUAL( p.value,                0 );
   HWLIB_TEST_EQUAL( p.is_output,            false );
   HWLIB_TEST_EQUAL( p.is_input,             true );
   HWLIB_TEST_EQUAL( p.read_count,           1 );   
   HWLIB_TEST_EQUAL( p.write_count,          2 );   
   HWLIB_TEST_EQUAL( p.direction_set_count,  2 );
   HWLIB_TEST_EQUAL( p.flush_count,          0 );
   HWLIB_TEST_EQUAL( p.refresh_count,        0 );   
   
   HWLIB_TEST_EQUAL( p.read(),               0 );
   HWLIB_TEST_EQUAL( p.read_count,           2 );     
   
   p.flush();
   
   HWLIB_TEST_EQUAL( p.value,                0 );
   HWLIB_TEST_EQUAL( p.is_output,            false );
   HWLIB_TEST_EQUAL( p.is_input,             true );
   HWLIB_TEST_EQUAL( p.read_count,           2 );   
   HWLIB_TEST_EQUAL( p.write_count,          2 );   
   HWLIB_TEST_EQUAL( p.direction_set_count,  2 );
   HWLIB_TEST_EQUAL( p.flush_count,          1 );
   HWLIB_TEST_EQUAL( p.refresh_count,        0 );   
   
   p.refresh();
   
   HWLIB_TEST_EQUAL( p.value,                0 );
   HWLIB_TEST_EQUAL( p.is_output,            false );
   HWLIB_TEST_EQUAL( p.is_input,             true );
   HWLIB_TEST_EQUAL( p.read_count,           2 );   
   HWLIB_TEST_EQUAL( p.write_count,          2 );   
   HWLIB_TEST_EQUAL( p.direction_set_count,  2 );
   HWLIB_TEST_EQUAL( p.flush_count,          1 );
   HWLIB_TEST_EQUAL( p.refresh_count,        1 );  

   p.value = 1;
   
   HWLIB_TEST_EQUAL( p.read(),               1 );
   HWLIB_TEST_EQUAL( p.read_count,           3 );   

   
}

void test_in_store(){
   hwlib::pin_in_store p;
   
   HWLIB_TEST_EQUAL( p.value,                false );
   HWLIB_TEST_EQUAL( p.read_count,           0 );   ;
   HWLIB_TEST_EQUAL( p.refresh_count,        0 );  
   
   p.refresh();
   
   HWLIB_TEST_EQUAL( p.value,                0 );
   HWLIB_TEST_EQUAL( p.read_count,           0 );      
   HWLIB_TEST_EQUAL( p.refresh_count,        1 );   
   
   HWLIB_TEST_EQUAL( p.read(),               0 );
   HWLIB_TEST_EQUAL( p.read_count,           1 );     
   HWLIB_TEST_EQUAL( p.refresh_count,        1 );  

   p.value = 1;   
   
   HWLIB_TEST_EQUAL( p.read(),               1 );
   HWLIB_TEST_EQUAL( p.read_count,           2 );     
   HWLIB_TEST_EQUAL( p.refresh_count,        1 );  
   
   p.value = 0;   
   
   HWLIB_TEST_EQUAL( p.read(),               0 );
   HWLIB_TEST_EQUAL( p.read_count,           3 );     
   HWLIB_TEST_EQUAL( p.refresh_count,        1 );  
   
}

void test_out_store(){
   hwlib::pin_out_store p;
   
   HWLIB_TEST_EQUAL( p.value,                false ); 
   HWLIB_TEST_EQUAL( p.write_count,          0 );   
   HWLIB_TEST_EQUAL( p.flush_count,          0 );
   
   p.write( 1 );

   HWLIB_TEST_EQUAL( p.value,                1 ); 
   HWLIB_TEST_EQUAL( p.write_count,          1 );   
   HWLIB_TEST_EQUAL( p.flush_count,          0 );
   
   p.write( 0 );

   HWLIB_TEST_EQUAL( p.value,                0 ); 
   HWLIB_TEST_EQUAL( p.write_count,          2 );   
   HWLIB_TEST_EQUAL( p.flush_count,          0 );
   
   p.flush();
   
   HWLIB_TEST_EQUAL( p.value,                0 ); 
   HWLIB_TEST_EQUAL( p.write_count,          2 );   
   HWLIB_TEST_EQUAL( p.flush_count,          1 );
   
}

void test_oc_store(){
   hwlib::pin_in_out_store p;
   
   HWLIB_TEST_EQUAL( p.value,                false );
   HWLIB_TEST_EQUAL( p.read_count,           0 );   
   HWLIB_TEST_EQUAL( p.write_count,          0 );   
   HWLIB_TEST_EQUAL( p.flush_count,          0 );
   HWLIB_TEST_EQUAL( p.refresh_count,        0 );
   
   p.refresh();
   
   HWLIB_TEST_EQUAL( p.value,                0 );
   HWLIB_TEST_EQUAL( p.read_count,           0 );    
   HWLIB_TEST_EQUAL( p.write_count,          0 ); 
   HWLIB_TEST_EQUAL( p.refresh_count,        1 );   
   
   HWLIB_TEST_EQUAL( p.read(),               0 );
   HWLIB_TEST_EQUAL( p.read_count,           1 );  
   HWLIB_TEST_EQUAL( p.write_count,          0 ); 
   HWLIB_TEST_EQUAL( p.flush_count,          0 );
   HWLIB_TEST_EQUAL( p.refresh_count,        1 );  

   p.value = 1;   
   
   HWLIB_TEST_EQUAL( p.read(),               1 );
   HWLIB_TEST_EQUAL( p.read_count,           2 );     
   HWLIB_TEST_EQUAL( p.write_count,          0 ); 
   HWLIB_TEST_EQUAL( p.flush_count,          0 );
   HWLIB_TEST_EQUAL( p.refresh_count,        1 );  
   
   p.value = 0;   
   
   HWLIB_TEST_EQUAL( p.read(),               0 );
   HWLIB_TEST_EQUAL( p.write_count,          0 ); 
   HWLIB_TEST_EQUAL( p.read_count,           3 );   
   HWLIB_TEST_EQUAL( p.flush_count,          0 );
   HWLIB_TEST_EQUAL( p.refresh_count,        1 );   

   p.write( 1 );

   HWLIB_TEST_EQUAL( p.read(),               1 );
   HWLIB_TEST_EQUAL( p.value,                1 );
   HWLIB_TEST_EQUAL( p.write_count,          1 );   
   HWLIB_TEST_EQUAL( p.read_count,           4 );   
   HWLIB_TEST_EQUAL( p.flush_count,          0 );
   HWLIB_TEST_EQUAL( p.refresh_count,        1 );   
   
   p.write( 0 );

   HWLIB_TEST_EQUAL( p.read(),               0 );
   HWLIB_TEST_EQUAL( p.value,                0 );
   HWLIB_TEST_EQUAL( p.read_count,           5 );   
   HWLIB_TEST_EQUAL( p.write_count,          2 );   
   HWLIB_TEST_EQUAL( p.flush_count,          0 );
   HWLIB_TEST_EQUAL( p.refresh_count,        1 );   
   
   p.flush();
   
   HWLIB_TEST_EQUAL( p.read(),               0 );
   HWLIB_TEST_EQUAL( p.value,                0 );
   HWLIB_TEST_EQUAL( p.read_count,           6 );   
   HWLIB_TEST_EQUAL( p.write_count,          2 );   
   HWLIB_TEST_EQUAL( p.flush_count,          1 );
   HWLIB_TEST_EQUAL( p.refresh_count,        1 );   

}

int main(){
   test_in_out_store();
   test_in_store();
   test_out_store();
   test_oc_store();
   hwlib::test_end();
}   

