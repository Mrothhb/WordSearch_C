/*
 * Filename: pa3.c
 * Author: Matt Roth
 * UserId: cs30xgs
 * Date: May 22nd, 2019
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

  // Default values for the wordTable_t
  unsigned int file_size = DEFAULT_FILE_SIZE;       
  unsigned int numSlots = DEFAULT_NUM_SLOTS;
  int opt;
  int success = 0;
  char *endPtr;

  // Parsing strings from the command line for conversion
  char * numSlotsStr = NULL;
  char * file_sizeStr = NULL;

  // Parse the flags from the command line 
  while( (opt = getopt( argc, argv, OPTSTRING )) != -1 ) {

    switch( opt ) {

      // Help flag has been parsed
      case HELP_FLAG:

        fprintf( stdout, STR_USAGE, argv[0], DEFAULT_DATA_DIR, MIN_NUM_SLOTS,
            MAX_NUM_SLOTS, DEFAULT_NUM_SLOTS, DEFAULT_FILE_SIZE );
        return EXIT_SUCCESS;

      // numSlots flag has been parsed
      case NUM_SLOTS_FLAG:

        numSlotsStr = optarg;
        break;

      // size flag has been parsed
      case FILE_SIZE_FLAG:

        file_sizeStr = optarg;
        break;

      // The flag parsed was not recognized continue reading from command line
      default:

        continue;
    }
  }

  // Check the numSlots flag for errors 
  if( numSlotsStr != NULL ){

    errno = 0;

    // Convert the numSlots string parsed from the command line to an int 
    numSlots = strtoul( numSlotsStr, &endPtr, NUM_SLOTS_BASE );

    if ( errno != 0 ) {

      fprintf( stderr, STR_ERR_CONVERTING, STR_NUM_SLOTS_ARGNAME, 
          numSlotsStr, NUM_SLOTS_BASE, strerror( errno ) );
      return EXIT_FAILURE;
    }

    // Check for invalid argument flag
    if( *endPtr != '\0' ) {

      fprintf( stderr, STR_ERR_NOT_INT, STR_NUM_SLOTS_ARGNAME, numSlotsStr, 
          NUM_SLOTS_BASE );
      return EXIT_FAILURE;
    }

    // Check for out of range values 
    if( intervalContains( MIN_NUM_SLOTS, MAX_NUM_SLOTS, numSlots )
        != INSIDE_INTERVAL ) {

      fprintf( stderr, STR_ERR_NUM_SLOTS_INTERVAL, numSlots, MIN_NUM_SLOTS,
          MAX_NUM_SLOTS );
      return EXIT_FAILURE;
    } 
  }

  // Check the size flag for errors
  if( file_sizeStr != NULL ) {

    errno = 0;

    // Convert the size from a string to an int 
    file_size = strtoul( file_sizeStr, &endPtr, SIZE_BASE );

    if( errno != 0 ) {

      fprintf( stderr, STR_ERR_CONVERTING, STR_SIZE_ARGNAME, file_sizeStr, 
          SIZE_BASE, strerror(errno) );
      return EXIT_FAILURE;
    } 

    // Check for an invalid argument 
    if( *endPtr != '\0' ) {

      fprintf( stderr, STR_ERR_NOT_INT,STR_SIZE_ARGNAME , file_sizeStr, 
          SIZE_BASE );
      return EXIT_FAILURE;
    }

    // Check if the size was within the range of allowable sizes
    int i;
    int allowed = 0;
    int ALLOWED_SIZES[ALLOWED_FILE_SIZES_LEN] = ALLOWED_FILE_SIZES;

    // Iterate through the sizes and check fo valid size 
    for(i = 0; i < ALLOWED_FILE_SIZES_LEN; i++ ) {

      if( file_size == ALLOWED_SIZES[i] ) {

        allowed = 1;
      }
    }

    // If the size is not within the range of allowable sizes return error 
    if( allowed != 1 ) {
      fprintf( stderr, STR_ERR_SIZE_INVALID, file_size );
      return EXIT_FAILURE;
    }
  }

  // Check for extra arguments 
  if( optind < argc ) {

    fprintf( stderr, STR_ERR_EXTRA_ARG, argv[optind] );
    return EXIT_FAILURE;
  }  

  // Create a wordTable on the stack for searching the table 
  wordTable_t table;

  table.numSlots = numSlots;

  // Allocate memory dynamically from the heap an zero initialize everything 
  table.slotPtr = calloc( table.numSlots, table.numSlots * 
    sizeof(wordTable_t) );

  if( table.slotPtr == NULL ) {

    fprintf( stderr, STR_ERR_MEM_EXCEEDED );
    return EXIT_FAILURE;
  }  

  // Build the wordTable 
  success = buildWordTable( &table, file_size );

  if( success == -1 ) {

    free( table.slotPtr );
    return EXIT_FAILURE;
  }

  // Start the user interactive process
  interactiveLoop( &table );


  // free all dynamically allocated memory 
  int slotIDX = 0;
  while( slotIDX < table.numSlots ) {

    if( table.slotPtr[slotIDX].wordDataPtr ) {
      free( table.slotPtr[slotIDX].wordDataPtr );
    }  
    ++slotIDX;
  }  
      
  free( table.slotPtr );

  return EXIT_SUCCESS;
}
