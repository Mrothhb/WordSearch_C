/*
 * Filename: findCommand.c
 * Author: Matt Roth
 * UserId: cs30xgs
 * Date: May 1, 2019
 * Sources of help: Textbook, cse 30 website, lecture notes, discussion notes.
 */

#include <stdio.h>
#include <string.h>
#include "pa2.h"

/*
 * Function Name: findCommand()
 * Function Prototype:  int findCommand( const char * cmdString, 
 *                                            const char * commands[] );
 * Description:  This function will look for the given cmdString in commands and
 *               return its index.
 * Parameters:   cmdString the string to search for, commands[] the string array
 *               to search containing the possible string.
 * Side Effects: The index of the string in the array that matches the cmdString
                 will be returned. 
 * Error Conditions: If cmdString, commands[] are NULL or the string isnt found.
 *                    
 * Return Value: index of string or, -1,     
 */

int findCommand( const char * cmdString, const char * commands[] ) {

  int i = 0;
  int found = -1;   // the return parameter determining if string is found 

  // Null check to see if the parameters are NULL value 
  if( cmdString == NULL || commands == NULL ) {
    return found = -1;
  }

  // Search the entire array for the string, until NULL is found
  while( commands[i] != NULL ) {

    // Determine if the string is matching 
    found = strcmp( cmdString, commands[i]);
    
    // The string was found and return the index of the string 
    if( found == 0 ) {
      return i;
    }
    
    i++;
  }
  // The string was not found return failure
  found = -1;
  return found;
}
