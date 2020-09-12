/*
 * Filename: testmyURem.c
 * Author: Matt Roth
 * UserId: cs30xgs
 * Date: May 22nd, 2019
 * Sources of Help: Lecture notes, cse 30 website, texbook. 
 */ 

#include <stdio.h>

#include "pa3.h"
#include "test.h"

/*
 * Unit Test for myURem.s
 *
 * int myRem( unsigned int dividend, unsigned int divisor );
 *
 * Acts as a % operator like in C. returns the remainder of two operands.
 *
 **/
void testmyURem() {

  unsigned int i;
  unsigned int j = BUFSIZ;
  unsigned int charA = 'a'; // local variable char character a
  char charSym = 0x7E;      // local variable char hex value 
  unsigned int i_mod_j;

  TEST(myURem( -6, 3 ) == 0xFFFFFFFA % 3);   // test dividend > divisor 
  TEST(myURem( -3, 6 ) == 0xFFFFFFFD % 6);   // test dividend < divisor 
  TEST(myURem( 6, -1 ) == 6 % 0xffffffff);   // test mod one case
  TEST(myURem( 0, 6 ) == 0 % 6);   // test 0 mod with divisor case
  TEST(myURem( 2, 2 ) == 2 % 2);   // test dividend == divisor 
  TEST(myURem(charA,charSym ) == charA % charSym); // test local variables
  TEST(myURem( 10, 2 ) == 10 % 2);   // test dividend == divisor 
  TEST(myURem( -2, -2 ) == 2 % 2);   // test dividend == divisor 

  TEST(myURem( 0xFFFFFFFF,0xFFFFFFFF ) == 0xFFFFFFFF % 0xFFFFFFFF );   
  

  for ( i = 0; i < BUFSIZ; i++){
    i_mod_j = i%j;
    TEST(myURem( i, j ) == (i % j));
    printf(" i = %d \n j = %d \n i mod j = %d \n", i, j, i_mod_j);
    j--;
  }

  
}

int main( void ) {

  fprintf( stderr, "Running tests for myURem...\n" );
  testmyURem();
  fprintf( stderr, "Done running tests!\n" );

  return 0;
}
