/*
 * Filename: interactiveLoop.c
 * Author: Matt Roth
 * UserId: cs30xgs
 * Date: May 22, 2019
 * Sources of help: Textbook, cse 30 website, lecture notes, discussion notes.
 */

#include <stdio.h>
#include "pa3.h"
#include "pa3Strings.h"
#include <string.h>

/*
 * Function Name: interactiveLoop()
 * Function Prototype: void interactiveLoop( const wordTable_t * table );
 * Description: This function will allow the user to interactively interact
 *              with the program through commands to print specific data to 
 *              stdout, such as a graph or table.
 * Parameters: table - the table to manipulate for words and data.   
 * Side Effects: None.
 * Error Conditions: Handled case  by case below.
 *                    
 * Return Value: None. 
 */
void interactiveLoop( const wordTable_t * table ) {

  int valid_check = 0;  
  int command_index;

  // Create a buffer to read in strings from terminal  
  char buffer[BUFSIZ];  

  //  The array of commands the user might enter
  const char * LIST_COMMANDS[] = COMMANDS;

  // Check if input is coming from stdin or from an input file 
  valid_check = shouldPrompt(); 

  // Print the prompt 
  if( valid_check ) {

    fprintf( stdout, STR_HELP ); 
  }

  // Start the loop for all possible commands a user might enter 
  for(PRINT_PROMPT; fgets( buffer, BUFSIZ, stdin ); PRINT_PROMPT ) {

    // Set the newline character to Null 
    char * pos = strchr( buffer, '\n' );

    if( pos != NULL ) {
      *pos = '\0';
    }

    // parse the commands from the string input by the user 
    char * commandName = strtok( buffer, DELIMS );

    // If no arguments are input then reprommpt the user for input 
    if( !(commandName )) {
      continue;
    }

    // Find the corresponding command entered by the user 
    else {

      command_index = findCommand(commandName, LIST_COMMANDS);

      // If the user entered an invalid command name print the error message 
      if( command_index == INVALID_ENTRY){
        fprintf( stdout, STR_ERR_BAD_COMMAND );
        continue;
      }

      // Determine which command name was entered  
      switch( command_index ) {

        // Print the list of options again 
        case HELP:
          fprintf( stdout, STR_HELP );
          break;

        // check if data or plot was an argument 
        case DATA:
        case PLOT: {

          // Parse the argument following the the command
          char * argument = strtok( NULL, DELIMS );


          // check if the argument is missing 
          if( !argument ) {

            fprintf(stdout, STR_ERR_COMMAND_MISSING_ARG );
            break;
          }

          // Check if there is trailing arguments  
          if( strtok(NULL, DELIMS )!= NULL ) {

            fprintf(stdout, STR_ERR_COMMAND_EXTRA_ARG);
            continue;
          }

          // Create a wordData_t struct pointer for bsearch   
          wordData_t * found;
          unsigned int index; 

          // Create a wordData_T on the stack 
          wordData_t wordData;

          // Populate the wordData_t with the word, decade and count
          createWordData( &wordData, argument, MIN_DECADE, 0 );

          index = findSlotIndex( argument, table->numSlots );

          // Use a binary search to find the wordData 
          found =  bsearch( &wordData, &table->slotPtr->wordDataPtr[index], 
            table->slotPtr->numWords, sizeof(wordData_t), compareWordData );

          if( found == NULL ) {

            fprintf(stdout, STR_NO_DATA );
            continue;
          } 

          // Determine the min and max count of all decades in the word
          unsigned int minCount = 0;
          unsigned int maxCount = 0;
          char plotArr[PLOT_ROWS][PLOT_COLS];
          int j;
          // Set the min and max count for the word 
          for( j = 0; j < NUM_OF_DECADES; j++ ) {

            if( found->counts[j] >= maxCount ) {
              maxCount = found->counts[j];
            }
            if( found->counts[j] <= minCount ) {
              minCount = found->counts[j];
            }
          }
          
          // Build the plot with the data from the word
          buildPlot( plotArr, found, minCount, maxCount );

          printPlot( plotArr, minCount, maxCount );
          
          // Print the data from the word in tabular format
          printData( found );

          break;
        }  
      }
    }
  }

  // Print the final exit prompt
  fprintf(stdout, STR_END_PROMPT);
}
