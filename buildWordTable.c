/*
 * Filename: buildWordTable.c
 * Author: Matt Roth
 * UserId: cs30xgs
 * Date: TODO
 * Sources of help: Textbook, cse 30 website, lecture notes, discussion notes.
 */
#include <stdio.h>
#include "pa3.h"
#include "pa3Strings.h"
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

/*
 * Function Name: buildWordTable()
 * Function Prototype: int buildWordTable( wordTable_t * table,
 *                     unsigned int size );
 * Description: This function will create a wordTable that will contain 
 *              wordData structs holding words, counts, and hashvalues.
 * Parameters:  table -  the wordTable.
 *              size  -  the size of the data files in directory.  
 * Side Effects: The wordTable will be created with initialized values.
 * Error Conditions: Error opening file, tokenizing, parsing, and adding word.
 *                    
 * Return Value: -1 on failure and 0 on success.
 */
int buildWordTable( wordTable_t * table, unsigned int size ) {

  char letter;                
  char path[BUFSIZ];            // The path to build for opening files
  FILE *fp;
  char buffer[BUFSIZ];
  unsigned int line_num = 1;    // Tracking the line number
  int success = 0;
  unsigned int index = 0;
  char i;                       // The letter to increment in the for loop


  // Iterate through all the letters in the directory and open each file 
  for( i = FIRST_LETTER; i <= LAST_LETTER; i++ ) {

    // Set the letter to the index of i for the first file to open
    letter = i;
    line_num = 1;
    snprintf(path, BUFSIZ, STR_PATH_JOIN, DEFAULT_DATA_DIR, letter, size );
    errno = 0;

    // Open the file from the generated path 
    fp = fopen( path, READ_ONLY);

    // Check if the file opening was successful 
    if( errno != 0 || fp == NULL ) {

      fprintf(stderr, STR_ERR_OPENING_FILE, path, strerror(errno) );
      continue;
    }

    // Add each word and its data from the file to the table 
    while( fgets(buffer, BUFSIZ, fp) != NULL ) {

      char * pos = strchr( buffer, NEWLINE_CHAR );

      if( pos != NULL ) {
        *pos = '\0';
      }

      // Parse the data from the file 
      char * word = strtok( buffer, DELIMS );
      char * decadeStr = strtok( NULL, DELIMS );
      char * countStr = strtok( NULL, DELIMS );

      // Check if the parsing was unsuccessful 
      if( word == NULL || decadeStr ==  NULL || countStr == NULL ) {

        fprintf( stderr, STR_ERR_PARSING_LINE, line_num, path, buffer ); 
        continue;
      }

      char * endPtr;
      errno = 0;

      // Convert the parsed strings from file into usigned longs 
      unsigned int decade = strtoul( decadeStr, &endPtr, DECADE_BASE );

      // Check if the conversion to unsigned long was unsuccesful 
      if( errno != 0 || *endPtr != '\0' ) {

        fprintf( stderr, STR_ERR_PARSING_LINE, line_num, path, buffer); 
        continue;
      }

      unsigned int count = strtoul( countStr, &endPtr, COUNT_BASE );

      // Check if the count is larger than max size
      if( count >= ULONG_MAX ) {
        count = ULONG_MAX;
      }

      // Check if the conversion to unsigned long was unsuccesful 
      if( *endPtr != '\0' ) {

        fprintf( stderr, STR_ERR_PARSING_LINE, line_num, path, buffer ); 
        continue;
      }

      // Store the data in the table 
      index = findSlotIndex( word, table->numSlots );

      success = addWordCount( &table->slotPtr[index], word, decade, count );

      // Check if adding the wordData was successful
      if( success == -1 ) {
        fclose(fp);
        return -1;
      }

      // Increment the line number 
      ++line_num;
    }

    fclose(fp);
  }


  return 0;
}

