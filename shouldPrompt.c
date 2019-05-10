/*
 * Filename: shouldPrompt.c
 *
 * XXX DO NOT EDIT THIS FILE.
 */

#include <unistd.h>

/*
 * Function Name: shouldPrompt()
 * Function Prototype: int shouldPrompt( void );
 * Description: Checks if we are accepting input from terminal or some
 *              file-redirection, etc and therefore if we should prompt.
 * Parameters: None.
 * Side Effects: Sets errno if stdin doesn't refer to a terminal.
 * Error Conditions: None.
 * Return Value: Returns 1 if should prompt, 0 if not.
 */
int shouldPrompt( void ) {
  return isatty( STDIN_FILENO );
}
