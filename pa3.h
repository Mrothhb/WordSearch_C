/*
 * Filename: pa3.h
 * Author: Matt Roth
 * UserId: cs30xgs
 * Date: May 15th, 2019
 * Sources of help: Given.
 */
#ifndef PA3_H
#define PA3_H

#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <stddef.h>

// =============================================================================
// Defined Constants
// =============================================================================

/* Command-line argument parsing */
#define OPTSTRING "n:s:d:h"
#define NUM_SLOTS_FLAG 'n'
#define FILE_SIZE_FLAG 's'
#define DATA_DIR_FLAG 'd'
#define HELP_FLAG 'h'

#define SIZE_BASE 10
#define DEFAULT_FILE_SIZE 50
#define ALLOWED_FILE_SIZES {1, 5, 10, 50, 100, 500}
#define ALLOWED_FILE_SIZES_LEN 6

#define NUM_SLOTS_BASE 10
#define DEFAULT_NUM_SLOTS 11
#define MIN_NUM_SLOTS 3
#define MAX_NUM_SLOTS 421

#define DEFAULT_DATA_DIR "/home/linux/ieng6/cs30x/public/pa3Data/"

/* Statistics */
#define NUM_OF_DECADES 21
#define YEARS_IN_DECADE 10
#define MIN_DECADE 1800
#define MAX_DECADE 2000

/* Data file parsing */
#define DELIMS " \t"
#define NEWLINE_CHAR '\n'
#define FIRST_LETTER 'a'
#define LAST_LETTER 'z'
#define MAX_WORD_SIZE 48
#define DECADE_BASE 10
#define COUNT_BASE 10

/* Hashing */
#define HASH_START_VAL 13
#define HASH_PRIME 31

/* Plotting */
#define PLOT_ROWS 26
#define PLOT_COLS 44
#define PERCENTAGE_FACTOR 100
#define ROW_RESOLUTION 4
#define COL_SEPARATION 2
#define PLOT_SPACE_CHAR ' '
#define PLOT_LINE_CHAR 'x'

/* Interactive Loop */
#define COMMANDS {"plot", "data", "help", NULL}

#define PLOT 0
#define DATA 1
#define HELP 2

#define PRINT_PROMPT (shouldPrompt() ? printf(STR_COMMAND_PROMPT) : 0)

// =============================================================================
// Struct Definitions (DO NOT EDIT)
// =============================================================================

/*
 * Struct holding data on how often a certain word was used, across all decades
 * from 1800 to 2000.
 */
struct wordData {
  // The original word. May be truncated if the original word is longer
  // than MAX_WORD_SIZE - 1.
  char word[MAX_WORD_SIZE];

  // The counts for this word in every decade.
  unsigned int counts[NUM_OF_DECADES];

  // Computed hash on the truncated word.
  // This means wordData.hashValue == computeHash(wordData.word)
  unsigned int hashValue;
};
typedef struct wordData wordData_t;

/*
 * A slot in the hashtable which holds the sorted array of wordData_t that
 * collided into this slot.
 */
struct tableSlot {
  // The sorted array of wordData_t.
  wordData_t * wordDataPtr;

  // The length of the array.
  size_t numWords;
};
typedef struct tableSlot tableSlot_t;

/*
 * The hashtable metadata structure.
 */
struct wordTable {
  // The array of slots. This is the actual table which we hash entries into.
  tableSlot_t * slotPtr;

  // The length of the slot array.
  size_t numSlots;
};
typedef struct wordTable wordTable_t;

// =============================================================================
// Function Prototypes (DO NOT EDIT)
// =============================================================================

unsigned int computeHash( const char * str );
unsigned int myURem( unsigned int dividend, unsigned int divisor );
unsigned int findSlotIndex( const char * wordStr, size_t numSlots );
int compareWordData( const void * w1, const void * w2 );
void createWordData( wordData_t * wordData, const char * wordStr,
                     unsigned int decade, unsigned int count );
int addWordCount( tableSlot_t * slot, const char * word, unsigned int decade,
                  unsigned int count );
int buildWordTable( wordTable_t * table, unsigned int size );
void buildPlot( char plotArr[PLOT_ROWS][PLOT_COLS], const wordData_t * word,
                unsigned int minCount, unsigned int maxCount );
int findCommand( const char * cmdString, const char * commands[] );
void printPlot( char plotArr[PLOT_ROWS][PLOT_COLS], unsigned int minCount,
                unsigned int maxCount );
void printData( const wordData_t * word );
void interactiveLoop( const wordTable_t * table );
int shouldPrompt( void );
int intervalContains( int start, int end, int value );

// Convenience printing function.
void printTable( const wordTable_t * table );

#endif // PA3_H
