/*
 * Filename: testbuildWordTable.c
 * Author: Matt Roth
 * UserId: cs30xgs
 * Date: May 17th, 2019
 * Sources of help: Textbook, cse 30 website, lecture notes, discussion notes.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pa3.h"

/*
 * Unit Test for buildWordTable.c
 */
void testbuildWordTable() {

  int i;

  wordTable_t table;
  tableSlot_t slot;

  table.numSlots = 1; 
  slot.wordDataPtr = NULL;
  slot.numWords = 0;
  table.slotPtr = &slot;

  unsigned int size = 1;

  buildWordTable( &table, size );    

  for( i = 0; i < 26; i++){ 

    printf( "%s \n\n", slot.wordDataPtr[i].word);
  } 
}

int main( void ) {

  fprintf( stderr, "Running tests for buildWordTable.c...\n" );
  testbuildWordTable();
  fprintf( stderr, "Done running tests!\n" );

  return 0;
}
