/*
 * Filename: pa3.c
 * Author: Matt Roth
 * UserId: cs30xgs
 * Date: May22th, 2019
 * Sources of help: Textbook, cse30 website, lecture notes, discussion notes.
 */

#include <stdio.h>
#include "pa3.h"
#include "pa3Strings.h"
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <getopt.h>

/*
 * Function Name: main()
 * Function Prototype: int main( int argc, char * argv[] );
 * Description: This is the main driver of the program. Its main tasks are to
 *              parse any command line arguments that are passed in and start
 *              the user-interactive mode. 
 * Parameters: argc is the argument counter, argv is each argument from the 
 *             command line.  
 * Side Effects: The program will be executed with the respective arguments. 
 * Error Conditions: invalid amount of arguments, or invalid argument types will
 *                   return EXIT_FAILURE.
 * Return Value: EXIT_SUCCESS on success, and EXIT_FAILURE on failure.    
 */
int main( int argc, char * argv[] ) {

  unsigned int file_size = DEFAULT_FILE_SIZE;
  unsigned int numSlots = DEFAULT_NUM_SLOTS;
  int opt;
  int success = 0;
  char *endPtr;
  char * numSlotsStr = NULL;
  char * file_sizeStr = NULL;

  while( (opt = getopt( argc, argv, OPTSTRING )) != -1 ) {

    switch( opt ) {

      case HELP_FLAG:

        fprintf( stdout, STR_USAGE, argv[0], DEFAULT_DATA_DIR, MIN_NUM_SLOTS,
            MAX_NUM_SLOTS, DEFAULT_NUM_SLOTS, DEFAULT_FILE_SIZE);
        return EXIT_SUCCESS;

      case NUM_SLOTS_FLAG:

        numSlotsStr = optarg;
        break;

      case FILE_SIZE_FLAG:

        file_sizeStr = optarg;
        break;

      case '?':
      default:

        continue;
    }

  }

  if( numSlotsStr != NULL ){  
    errno = 0;
    numSlots = strtoul( numSlotsStr, &endPtr, NUM_SLOTS_BASE );

    if ( errno != 0 ) {
      fprintf( stderr, STR_ERR_CONVERTING, STR_NUM_SLOTS_ARGNAME, 
          numSlotsStr, NUM_SLOTS_BASE, strerror( errno ) );
      return EXIT_FAILURE;
    }

    if( *endPtr != '\0' ) {

      fprintf( stderr, STR_ERR_NOT_INT, STR_NUM_SLOTS_ARGNAME, numSlotsStr, 
          NUM_SLOTS_BASE );
      return EXIT_FAILURE;
    }

    if( intervalContains( MIN_NUM_SLOTS, MAX_NUM_SLOTS, numSlots )
        != INSIDE_INTERVAL ) {

      fprintf( stderr, STR_ERR_NUM_SLOTS_INTERVAL, numSlots, MIN_NUM_SLOTS,
          MAX_NUM_SLOTS );
      return EXIT_FAILURE;
    } 
  }

  if( file_sizeStr != NULL ) {
    errno = 0;
    file_size = strtoul( file_sizeStr, &endPtr, SIZE_BASE );

    if( errno != 0 ) {
      fprintf( stderr, STR_ERR_CONVERTING, STR_SIZE_ARGNAME, file_sizeStr, 
          SIZE_BASE, strerror(errno) );
      return EXIT_FAILURE;
    } 

    if( *endPtr != '\0' ) {

      fprintf( stderr, STR_ERR_NOT_INT,STR_SIZE_ARGNAME , file_sizeStr, 
          SIZE_BASE );
      return EXIT_FAILURE;
    }

    int i;
    int allowed = 0;
    int ALLOWED_SIZES[ALLOWED_FILE_SIZES_LEN] = ALLOWED_FILE_SIZES;

    for(i = 0; i < ALLOWED_FILE_SIZES_LEN; i++ ) {
      if( file_size == ALLOWED_SIZES[i] ) {
        allowed = 1;
      }
    }

    if( allowed != 1 ) {
      fprintf( stderr, STR_ERR_SIZE_INVALID, file_size );
      return EXIT_FAILURE;
    }
  }

  if( optind < argc ) {

    fprintf(stderr, STR_ERR_EXTRA_ARG, argv[optind] );
    return EXIT_FAILURE;
  }  

  wordTable_t table;

  table.numSlots = numSlots;

  table.slotPtr = calloc(table.numSlots, sizeof(wordTable_t));

  if( table.slotPtr == NULL ) {

    fprintf(stderr, STR_ERR_MEM_EXCEEDED);
    return EXIT_FAILURE;
  }  

  buildWordTable( &table, file_size );

  if( success == -1 ) {
    return EXIT_FAILURE;
  }

  interactiveLoop( &table );

  // return success
  return EXIT_SUCCESS;
}
