/*
 * Filename: testcompareWordData.c
 * Author: Matt Roth
 * UserId: cs30xgs
 * Date: May 15th, 2019
 * Sources of help: Textbook, cse 30 website, lecture notes, discussion notes.
 */

#include <stdio.h>
#include <string.h>
#include "pa3.h"
#include "test.h"

/*
 * Unit Test for compareWordData.c
 *
 * This function takes two void pointers in its signature, but you will pass in 
 * wordData_t pointers (const wordData_t *)  and compare them. This comparator 
 * should firstcompare the wordData_ts hash values. If they have the same hash
 * value, thencompare the wordData_ts words using strncmp, with the maximum 
 * number of characters to compare being MAX_WORD_SIZE
 *
 */
void testcompareWordData() {

  wordData_t word1;
  wordData_t word2;

  strncpy(word1.word, "hello", MAX_WORD_SIZE);
  strncpy(word2.word, "hello", MAX_WORD_SIZE);

  word1.hashValue = 5;
  word2.hashValue = 5;
  
  TEST( compareWordData( &word1, &word2 ) == 0 );

  
  strncpy(word1.word, "MANGO", MAX_WORD_SIZE);
  strncpy(word2.word, "TANGO", MAX_WORD_SIZE);

  word1.hashValue = 50;
  word2.hashValue = 50;
  
  TEST( compareWordData( &word1, &word2 ) == -1);

  strncpy(word1.word, "TANGO", MAX_WORD_SIZE);
  strncpy(word2.word, "MANGO", MAX_WORD_SIZE);

  word1.hashValue = 5;
  word2.hashValue = 5;
  
  TEST( compareWordData( &word1, &word2 ) == 1);


  strncpy(word1.word, "TANGO", MAX_WORD_SIZE);
  strncpy(word2.word, "MANGO", MAX_WORD_SIZE);

  word1.hashValue = 1;
  word2.hashValue = 5;
  
  TEST( compareWordData( &word1, &word2 ) == -1);
 

  strncpy(word1.word, "TANGO", MAX_WORD_SIZE);
  strncpy(word2.word, "MANGO", MAX_WORD_SIZE);

  word1.hashValue = 5;
  word2.hashValue = 1;
  
  TEST( compareWordData( &word1, &word2 ) == 1);

  strncpy(word1.word, "a", MAX_WORD_SIZE);
  strncpy(word2.word, "z", MAX_WORD_SIZE);

  word1.hashValue = 10;
  word2.hashValue = 10;
  
  TEST( compareWordData( &word1, &word2 ) == -1);

}


int main( void ) {

  fprintf( stderr, "Running tests for compareWordData.c...\n" );
  testcompareWordData();
  fprintf( stderr, "Done running tests!\n" );

  return 0;
}
