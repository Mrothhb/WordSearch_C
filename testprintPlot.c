/*
 * Filename: testprintPlot.c
 * Author: Matt Roth
 * UserId: cs30xgs
 * Date: May 17th, 2019
 * Sources of help: Textbook, cse 30 website, lecture notes, discussion notes.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pa3.h"
#include "test.h"

/*
 * Unit Test for printPlot.c
 *
 * int printPlot void printPlot( char plotArr[PLOT_ROWS][PLOT_COLS], unsigned 
 *    int minCount,unsigned int maxCount ); 
 */
void testprintPlot() {

  char plotArr[PLOT_ROWS][PLOT_COLS];
  unsigned int decade = 1920;
  unsigned int index;
  unsigned int count;

  wordData_t word_data;

  index = ( decade - MIN_DECADE) / YEARS_IN_DECADE;

  word_data.counts[0] = 0;
  word_data.counts[1] = 2000000;
  word_data.counts[2] = 3000000;
  word_data.counts[3] = 4500000;
  word_data.counts[4] = 6600000;
  word_data.counts[7] = 7000000;
  word_data.counts[8] = 8000000;
  word_data.counts[9] = 9000000;
  word_data.counts[5] = 1000000;


  buildPlot( plotArr, &word_data, 0,  9000000 );

  printPlot( plotArr, 0, 9000000 );
  
}

int main( void ) {

  fprintf( stderr, "Running tests for printPlot.c...\n" );
  testprintPlot();
  fprintf( stderr, "Done running tests!\n" );

  return 0;
}
