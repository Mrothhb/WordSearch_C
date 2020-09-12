/*
 * Filename: printPlot.c
 * Author: Matt Roth
 * UserId: cs30xgs
 * Date: May 22nd, 2019
 * Sources of help: Textbook, cse 30 website, lecture notes, discussion notes.
 */
#include <stdio.h>
#include "pa3.h"
#include "pa3Strings.h"

/*
 * Function Name: printPlot()
 * Function Prototype:  void buildPlot( char plotArr[PLOT_ROWS][PLOT_COLS],
 *                      const wordData_t * word, unsigned int minCount, 
 *                          unsigned int maxCount );
 * Description: This function prints the graph that has been previously 
 *              initialized by buildPlot()to stdout.
 * Parameters:  plotArr -  the array of plot data for decade and percentage.
 *              minCount - the minium count in word.
 *              maxCount - the maximum count in the word.
 * Side Effects: The graph will be printed to stdout. 
 * Error Conditions: None.
 *                    
 * Return Value: None.     
 */
void printPlot( char plotArr[PLOT_ROWS][PLOT_COLS], unsigned int minCount,
    unsigned int maxCount ){

  int i;
  int percent;    // Calculate the percentage for each row 

  // Print the plot by iterating each row 
  for( i = 0; i < PLOT_ROWS; i++ ) {

    percent = PERCENTAGE_FACTOR-(i*ROW_RESOLUTION); 

    // Check if it's the first row to print 
    if( i == 0 ) {

      fprintf(stdout, STR_PLOT_ROW_BOUND, maxCount, percent, plotArr[i] );
    }

    // Check if it's the last row to print
    else if( i == ( PLOT_ROWS-1 ) ) {

      fprintf(stdout, STR_PLOT_ROW_BOUND, minCount, percent, plotArr[i] );  
    }

    // Print the row next to the percentage for the coorespding row
    else {

      fprintf(stdout, STR_PLOT_ROW, percent, plotArr[i] );
    }
  }

  // Print the decaed for the columns 
  fprintf(stdout, STR_PLOT_X_AXIS );
}

