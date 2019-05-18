/*
 * Filename: printData.c
 * Author: Matt Roth
 * UserId: cs30xgs
 * Date: TODO
 * Sources of help: Textbook, cse 30 website, lecture notes, discussion notes.
 */
#include <stdio.h>
#include "pa3.h"
#include "pa3Strings.h"

/*
 * Function Name: printData()
 * Function Prototype: void printData( const wordData_t * word );
 * Description: This function prints out the word statistics in a tabular format
 *              for the given wordData_t to stdout. 
 * Parameters:  word -  the wordData_t to access for data to display.
 * Side Effects: The data will be printed to stdout in tabular form.
 * Error Conditions: None.
 *                    
 * Return Value: None.     
 */
void printData( const wordData_t * word ){

  unsigned int decade = 0;
  unsigned int hi_decade = 0;
  unsigned int hi_count = 0;
  unsigned int hi_count2 = 0;
  int i;

  // Print the header 
  fprintf( stdout, STR_STATS_HEADER );

  // 
  for ( i = 0; i < NUM_OF_DECADES; i++ ) {

    decade = ( i * YEARS_IN_DECADE ) + MIN_DECADE;

    if( word->counts[i] > hi_count ) {

      hi_count = word->counts[i];
      hi_decade = decade;
    }

    else if( word->counts[i] == hi_count ) {

      hi_count2 = word->counts[i];
      hi_decade = decade;
    }

    fprintf(stdout, STR_STATS_FMT_COUNT, decade, word->counts[i]);
  }


  if( hi_count == 0 ) {

    fprintf(stdout, STR_NO_HIGH_COUNT, word->word );
  }
  else if( hi_count2 ) {

    fprintf(stdout, STR_HIGH_COUNT, word->word, STR_MOST_RECENT, 
        hi_decade, hi_count);     
  }
  else {

    fprintf( stdout, STR_HIGH_COUNT, word->word, "", hi_decade, hi_count );
  }
}

