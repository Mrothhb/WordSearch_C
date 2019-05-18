/*
 * Filename: testfindSlotIndex.c
 * Author: Matt Roth
 * UserId: cs30xgs
 * Date: May 17th, 2019
 * Sources of Help: Lecture notes, cse 30 website, texbook. 
 */ 

#include <stdio.h>
#include "pa3.h"
#include "test.h"

/*
 * Unit Test for findSlotIndex.s
 *
 * unsigned int findSlotIndex( const char * wordStr, size_t numSlots );
 * This function will calculate the index into the slot array for the string 
 * wordStrin a slot array of size numSlots.  
 *
 **/
void testfindSlotIndex() {

  size_t test_size = 5;
  size_t test_size_large = 500;
  size_t test_size_small = 1;
  size_t test_size_default = 50;
  size_t test_zero = 0;
  size_t test_negative = -1;

  const char * str = "the";
  const char * str2 = "123FOUR";
  const char * str3 = "TestThisString 0";
  const char * str4 = "anotherTestString";
  const char * str5 = "q";
  const char * str6 = "#$&$*(#&21";
  const char * str7 = "           ";
  
  unsigned int hash = computeHash( str );

  unsigned int rem = myURem( hash, test_size ); 

  unsigned int slotIndex;

  /**Testing**/
  slotIndex = findSlotIndex(str, test_size);
  TEST( slotIndex == rem );

  hash = computeHash( str2 );
  rem = myURem( hash, test_size );
  slotIndex = findSlotIndex(str2, test_size);
  TEST( slotIndex == rem );

  
  hash = computeHash( str3 );
  rem = myURem( hash, test_size_large );
  slotIndex = findSlotIndex(str3, test_size_large);
  TEST( slotIndex == rem );

  
  hash = computeHash( str4 );
  rem = myURem( hash, test_size_small );
  slotIndex = findSlotIndex(str3, test_size_small);
  TEST( slotIndex == rem );

  hash = computeHash( str5 );
  rem = myURem( hash, test_size_default );
  slotIndex = findSlotIndex(str5, test_size_default);
  TEST( slotIndex == rem );

  hash = computeHash( str6 );
  rem = myURem( hash, test_size_default );
  slotIndex = findSlotIndex(str6, test_size_default);
  TEST( slotIndex == rem );

  hash = computeHash( str7 );
  rem = myURem( hash, test_size_default );
  slotIndex = findSlotIndex(str7, test_size_default);
  TEST( slotIndex == rem );

  hash = computeHash( "hello" );
  rem = myURem( hash, test_zero );
  slotIndex = findSlotIndex("hello", test_zero);
  TEST( slotIndex == rem );


  hash = computeHash( "hello" );
  rem = myURem( hash, test_negative );
  slotIndex = findSlotIndex("hello", test_negative);
  TEST( slotIndex == rem );

}

int main( void ) {

  fprintf( stderr, "Running tests for findSlotIndex...\n" );
  testfindSlotIndex();
  fprintf( stderr, "Done running tests!\n" );

  return 0;
}
