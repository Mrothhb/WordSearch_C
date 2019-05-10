/*
 * Filename: testaddWordCount.c
 * Author: TODO
 * UserId: TODO
 * Date: TODO
 * Sources of help: TODO
 */

#include <stdio.h>
#include <string.h>

#include "pa3.h"
#include "test.h"

/*
 * Unit Test for addWordCount.c
 *
 * int addWordCount( tableSlot_t * slot, const char * word,
 *                   unsigned int decade, unsigned int count );
 *
 * Increments the corresponding word's decade's count by the count parameter.
 *
 * If the slot does not have a wordData_t struct for the word, then reallocates
 * space for another in the wordDataPtr. Otherwise, just increments the
 * decade's index in the counts array of the existing struct.
 *
 * Returns -1 on memory allocation error, otherwise returns 0.
 */
void testaddWordCount() {
  // Initialize an empty slot.
  tableSlot_t slot = {
    .wordDataPtr = NULL,
    .numWords = 0
  };

  const char * word;
  unsigned int decade;
  unsigned int decadeIdx;
  unsigned int count;

  // Adding word to an empty slot.
  word = "hello";
  decade = 1820;
  decadeIdx = (decade - MIN_DECADE) / YEARS_IN_DECADE;
  count = 420;

  TEST( addWordCount( &slot, word, decade, count ) == 0 );  
  TEST( slot.numWords == 1 );
  TEST( strncmp( slot.wordDataPtr[0].word, word, MAX_WORD_SIZE ) == 0 );
  TEST( slot.wordDataPtr[0].counts[decadeIdx] == count );

  // Adding a new word, should resize the array.
  // "apple" sorted into index 0 before "hello" due to compareWordData.
  word = "apple";
  decade = 1800;
  decadeIdx = (decade - MIN_DECADE) / YEARS_IN_DECADE;
  count = 1;

  TEST( addWordCount( &slot, word, decade, count ) == 0 );  
  TEST( slot.numWords == 2 );
  TEST( strncmp( slot.wordDataPtr[0].word, word, MAX_WORD_SIZE ) == 0 );
  TEST( slot.wordDataPtr[0].counts[decadeIdx] == count );

  /*
   * TODO: YOU MUST WRITE MORE TEST CASES FOR FULL POINTS!
   *
   * Some things to think about are error cases, extreme cases, normal cases,
   * abnormal cases, etc.
   */
}


int main( void ) {

  fprintf( stderr, "Running tests for addWordCount.c...\n" );
  testaddWordCount();
  fprintf( stderr, "Done running tests!\n" );

  return 0;
}
