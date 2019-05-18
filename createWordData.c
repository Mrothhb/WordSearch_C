/*
 * Filename: createWordData.c
 * Author: Matt Roth
 * UserId: cs30xgs
 * Date: May 15th, 2019
 * Sources of help: Textbook, cse 30 website, lecture notes, discussion notes.
 */

#include <stdio.h>
#include <string.h>
#include "pa3.h"

/*
 * Function Name: createWordData()
 * Function Prototype:  void createWordData( wordData_t * wordData, const char 
 *                      wordStr, unsigned int decade, unsigned int count );
 * Description: Populates the fields of the wordDatastruct to represent the word
 *              in wordStr, initializes all values in counts, and computes the 
 *              hash value. 
 * Parameters:  wordData - the pointer to the struct
 *              wordStr  - the string to copy into the struct.
 *              decade   - the decade of the word.
 *              count    - the count of the word.
 * Side Effects: The struct wordData_t will be initialized with the data.
 * Error Conditions: None.
 *                    
 * Return Value: None.     
 */

void createWordData( wordData_t * wordData, const char * wordStr,
    unsigned int decade, unsigned int count) {
  int i;
  unsigned int index;
  
  // If void pointer or wordStr is Null return 
  if( !wordData || !wordStr ) {
    return;
  }   
  
  // Calculate the index of the decade 
  index  = ( decade - MIN_DECADE ) / YEARS_IN_DECADE;
  
  // Copy the word and insert the new word into the wordData_t 
  strncpy( wordData->word, wordStr, MAX_WORD_SIZE);
   
  // Null terminate the string 
  if(MAX_WORD_SIZE > 0) {
    wordData->word[MAX_WORD_SIZE-1] = '\0';
  }
  
  // Initialize all the counts in the array to zero 
  for( i = 0; i < NUM_OF_DECADES; i++ ) {
    if( i != index ) {
      wordData->counts[i] = 0;
    }
    else{
    // Set the counts value at the index to the count parameter
    wordData->counts[i] = count;
    }
  }
  
  // Set the hashValue to the computed hash value from computeHash 
  wordData->hashValue = computeHash( wordData->word );

}
