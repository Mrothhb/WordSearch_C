/*
 * Filename: printTable.c
 * Author: Matt Roth
 * UserId: cs30xgs
 * Date: May 15th, 2019
 * Sources of help: Given.
 */

#include <stdio.h>

#include "pa3.h"

#define COUNTS_ROWS 10
#define COUNTS_COLS 2

#define STR_WORD_TABLE_HEADER \
  "+--------------------------------+\n" \
  "| slotPtr  *  | numSlots = %5u |\n" \
  "+----------|---------------------+\n" \
  "           v\n"

#define STR_TABLE_SLOT_HEADER \
  "       +-----------------------+\n" \
  " %5u | wordDataPtr =       *-----+\n" \
  "       | numWords = %-10u |   |\n" \
  "       +-----------------------+   |\n" \
  "         .                         |\n" \
  "         .         +---------------+\n" \
  "         .         |\n" \
  "         .         v\n"
#define STR_TABLE_SLOT_EMPTY \
  "       +-----------------------+\n" \
  " %5u | wordDataPtr = %7s |\n" \
  "       | numWords = %-10u |\n" \

#define STR_TABLE_SLOT_SEPARATOR \
  "       +-----------------------+\n" \

#define STR_SLOT_CONTINUATION "         .\n"

#define STR_WORD_DATA_SEP \
  "         .       +--------------------------------------------------+\n"
#define STR_WORD_DATA_THICK_SEP \
  "         .       +==================================================+\n"

#define STR_WORD_DATA_WORD "         . %5u | %-*s | word\n"

#define STR_WORD_DATA_COUNT_LEADING "         .       |       "
#define STR_WORD_DATA_COUNT_SEP "   |   "
#define STR_WORD_DATA_COUNT_ELEM "[%2u] %-10u"
#define STR_WORD_DATA_LAST_DECADE \
  "         .       |       [%2u] %-10u                            |\n"
#define STR_WORD_DATA_COUNT_TRAILING "      |"
#define STR_WORD_DATA_COUNT_LABEL " counts"

#define STR_WORD_DATA_HASH_VALUE \
  "         .       |                   %10u                     | hashValue\n"

/*
 * Function Name: printWordDataPtr()
 * Function Prototype: void printWordDataPtr(tableSlot_t * slot);
 * Description: Prints each element of the word data array for the given slot.
 * Parameters: slot - the slot which holds the word data.
 * Side Effects: Prints to stdout.
 * Error Conditions: None.
 * Return Value: None.
 */
static void printWordDataPtr(tableSlot_t * slot) {
  for (unsigned int i = 0; i < slot->numWords; i++) {
    wordData_t * data = &slot->wordDataPtr[i];

    // Print separator between words, thick if not the first
    if (i == 0) {
      printf(STR_WORD_DATA_SEP);
    } else {
      printf(STR_WORD_DATA_THICK_SEP);
    }

    // Print the word
    printf(STR_WORD_DATA_WORD, i, MAX_WORD_SIZE, data->word);

    printf(STR_WORD_DATA_SEP); // Separate word and counts

    // Print counts elements, wrapped into COUNTS_ROWS and COUNTS_COLS
    for (unsigned int row = 0; row < COUNTS_ROWS; row++) {
      // Leading space and border
      printf(STR_WORD_DATA_COUNT_LEADING);

      // Print each element on the same row, with its index
      for (unsigned int col = 0; col < COUNTS_COLS; col++) {
        // Only print separator after the first element
        if (col != 0) {
          printf(STR_WORD_DATA_COUNT_SEP);
        }

        unsigned int idx = row * COUNTS_COLS + col;
        printf(STR_WORD_DATA_COUNT_ELEM, idx, data->counts[idx]);
      }

      // Trailing space, border and label (only on the first row)
      printf(STR_WORD_DATA_COUNT_TRAILING);
      if (row == 0) {
        printf(STR_WORD_DATA_COUNT_LABEL);
      }
      printf("\n");
    }

    // Print last decade since the rows * cols doesn't fit all counts evenly.
    printf(STR_WORD_DATA_LAST_DECADE, NUM_OF_DECADES - 1,
           data->counts[NUM_OF_DECADES - 1]);

    printf(STR_WORD_DATA_SEP); // Separate counts and hashValue

    // Print the hashValue
    printf(STR_WORD_DATA_HASH_VALUE, data->hashValue);
  }
  printf(STR_WORD_DATA_SEP);
}

/*
 * Function Name: printTable()
 * Function Prototype: void printTable(wordTable_t * table);
 * Description: Pretty-prints the table to stdout.
 * Parameters: table - the table to print
 * Side Effects: Prints to stdout.
 * Error Conditions: None.
 * Return Value: None.
 */
void printTable(const wordTable_t * table) {
  // The header containing the numSlots
  printf(STR_WORD_TABLE_HEADER, table->numSlots);

  // Loop across each slot index, print the slot header and the
  // wordDataPtr for that slot
  for (unsigned int i = 0; i < table->numSlots; i++) {
    tableSlot_t * slot = &table->slotPtr[i];

    if (slot->numWords > 0) {
      printf(STR_TABLE_SLOT_HEADER, i, slot->numWords);
      printWordDataPtr(slot);

      // Print continuation only in between slots, not at the end of the slotPtr
      if (i != table->numSlots - 1) {
        printf(STR_SLOT_CONTINUATION);
      }
    } else {
      printf(STR_TABLE_SLOT_EMPTY,
             i, slot->wordDataPtr ? "DANGLE!" : "NULL", slot->numWords);
      if (i == table->numSlots - 1) {
        printf(STR_TABLE_SLOT_SEPARATOR);
      }
    }
  }
}
