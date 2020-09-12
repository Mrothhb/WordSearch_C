/*
 * Filename: addWordCount.c
 * Author: Matt Roth
 * UserId: cs30xgs
 * Date: May 22nd, 2019
 * Sources of help: Textbook, cse 30 website, lecture notes, discussion notes.
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pa3.h"
#include "pa3Strings.h"

/*
 * Function Name: addWordCount()
 * Function Prototype:  int addWordCount( tableSlot_t * slot, const char * word,
 *                      unsigned int decade, unsigned int count);
 * Description:  This function will add the count for the wordand the decade to 
 *               the tableSlot.
 * Parameters:   slot - the slot to store the wordData
 *               word - the word to store in the wordData
 *               decade - the decade the word count will be associated with
 *               count -  the count of the word occurences to store in wordData.
 * Side Effects: None.
 *
 * Error Conditions: If failure return -1.
 *                    
 * Return Value: 0 or -1 for error.     
 */
int addWordCount( tableSlot_t * slot, const char * word, unsigned int decade, 
    unsigned int count ) {

  // Create a wordData_t struct pointer for bsearch   
  wordData_t * found;
  unsigned int index; 

  // Create a wordData_T on the stack 
  wordData_t wordData;

  // Calculate the index of the decade and poplulate the wordData_t  
  index = ( decade - MIN_DECADE ) / YEARS_IN_DECADE;

  createWordData( &wordData, word, decade, count );

  // Use a binary search to find the wordData 
  found =  bsearch( &wordData, slot->wordDataPtr, slot->numWords, 
      sizeof(wordData_t), compareWordData );

  // If the wordData had been found insert the new count at index
  if( found != NULL ) {
    
    found->counts[index] += count;
    return 0;
  }

  // The wordData was not found, create a new one 
  else if( found == NULL ) {
    
    // Allocate additional space in memory to insert the new wordData_t struct
    wordData_t * returnPtr = realloc (slot->wordDataPtr, (slot->numWords + 1)
                                                    * sizeof(wordData_t));
    //  Check if the realloc was unsuccesful                                   
    if(returnPtr == NULL) {
      
      // Free the memory for the pointer in the slot  
      free( slot->wordDataPtr );
      slot->wordDataPtr = NULL;
      fprintf( stderr, STR_ERR_MEM_EXCEEDED );
      return -1;
    }
    
    // Insert the wordData at the new segment of allocated memory
    returnPtr[slot->numWords] = wordData;
    slot->numWords = slot->numWords + 1;

    // Set the wordDataPtr now to the realloc returnPtr and sort the array 
    slot->wordDataPtr = returnPtr;
    qsort( slot->wordDataPtr, slot->numWords, sizeof(wordData_t), 
            compareWordData );
   }

   return 0;
}
