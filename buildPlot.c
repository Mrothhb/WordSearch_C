/*
 * Filename: buildPlot.c
 * Author: Matt Roth
 * UserId: cs30xgs
 * Date: TODO
 * Sources of help: Textbook, cse 30 website, lecture notes, discussion notes.
 */

#include <stdio.h>
#include <string.h>
#include "pa3.h"

/*
 * Function Name: buildPlot()
 * Function Prototype:  void buildPlot( char plotArr[PLOT_ROWS][PLOT_COLS],
 *                      const wordData_t * word, unsigned int minCount, 
 *                          unsigned int maxCount );
 * Description: This function will populate plotArr, a 2d-array that contains
 *              the plotted data for the word data within word.  
 * Parameters:  plotArr -  the array of plot data for decade and percetnage.
 *              word    -  the wordData struct.
 *              minCount - the minium count in word.
 *              maxCount - the maximum count in the word.
 * Side Effects: The array will be initialized. 
 * Error Conditions: None.
 *                    
 * Return Value: None.     
 */

void buildPlot( char plotArr[PLOT_ROWS][PLOT_COLS], const wordData_t * word, 
    unsigned int minCount, unsigned int maxCount ) {

  // Truncate the minCount and maxCount, and variables to hold calculation data
  unsigned int truncMin = minCount / TRUNCATE;
  unsigned int truncMax = maxCount / TRUNCATE;
  unsigned int percent;
  unsigned int row_index;
  unsigned int truncCount;
  unsigned int countIDX;
  int i;
  int j;

  // Initialize the plotArray 
  for( i = 0; i < PLOT_ROWS; i++ ) {

    for( j = 0; j < PLOT_COLS; j++ ) {

      // Check if it's the last column in the array
      if( j == (PLOT_COLS - 1) ) {

        // Set the end to the null character
        plotArr[i][j] = '\0';
      }

      // Check if the column is an odd or even index
      else if((j % COL_SEPARATION) != 0 ) {

        // Calculate the row index of the percentage from word count
        countIDX = j / COL_SEPARATION;
        truncCount = word->counts[countIDX] / TRUNCATE;
        percent = (( truncCount - truncMin ) * TRUNCATE ) 
          / (truncMax - truncMin); 
        row_index = ( TRUNCATE - percent ) / ROW_RESOLUTION;

        // Determine if the index cooresponds to a count from the word
        if( i == row_index ) {
          plotArr[row_index][j] = PLOT_LINE_CHAR;
        }
        else {
          plotArr[i][j] = PLOT_SPACE_CHAR;
        } 
      }

      // Otherwise initialize with space chars 
      else {
        plotArr[i][j] = PLOT_SPACE_CHAR;
      }
    }
  }
}
