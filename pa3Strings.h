/*
 * Filename: pa3Strings.h
 * Author: TODO
 * UserId: TODO
 * Date: TODO
 * Sources of help: Given.
 */
#ifndef PA3_STRINGS_H
#define PA3_STRINGS_H

/* Command-line argument parsing */
#define STR_USAGE \
  "\nUsage: %s [-n numSlots] [-s size] [-h]\n" \
  "Interactive program for studying word use frequency across decades.\n" \
  "Uses files from '%s'.\n" \
  "  -n numSlots\tThe number of slots in the hash table. \n" \
  "             \tMust be in range [%u, %u]. Defaults to %u.\n" \
  "  -s size\tThe size of files to be used. Files are identified by\n" \
  "         \t{letter}_{size} (e.g. a_5 has size 5). Must be one of\n" \
  "         \t{1, 5, 10, 50, 100, 500}. Defaults to %u.\n" \
  "  -h    \tPrints this help message.\n" \
  "\n"

#define STR_SIZE_ARGNAME "size"
#define STR_NUM_SLOTS_ARGNAME "numSlots"

#define STR_ERR_EXTRA_ARG "\n\tExtra argument '%s' encountered.\n\n"
#define STR_ERR_CONVERTING "\n\tError converting %s '%s' to base %d: %s\n\n"
#define STR_ERR_NOT_INT "\n\t%s '%s' is not a valid integer in base %d\n\n"
#define STR_ERR_NUM_SLOTS_INTERVAL \
  "\n\tnumSlots (%u) is not within [%u, %u]\n\n"
#define STR_ERR_SIZE_INVALID \
  "\n\tsize (%u) is not within {1, 5, 10, 50, 100, 500}\n\n"

/* Reading data files */
#define STR_PATH_JOIN "%s/%c_%u"
#define STR_ERR_OPENING_FILE "Could not open file %s: %s\n"
#define STR_ERR_PARSING_LINE "Could not parse line %u of %s: %s\n"

/* Statistics */
#define STR_STATS_HEADER \
  "\n\tDecade\t     Count\n" \
    "\t------\t----------\n"
#define STR_STATS_FMT_COUNT "\t %4u \t%10u\n"

#define STR_HIGH_COUNT "\n"\
  "'%s' was used most frequently %sin %u with %u occurrences\n\n"
#define STR_NO_HIGH_COUNT ""\
  "'%s' was not one of the top common words from 1800 to 2000\n"
#define STR_MOST_RECENT "recently "
#define STR_ERR_MEM_EXCEEDED "\n\tMemory limit exceeded.\n"

/* Plot */
#define STR_PLOT_ROW "              %3u%% |%s\n"
#define STR_PLOT_ROW_BOUND " (%10u) %3u%% |%s\n"
#define STR_PLOT_X_AXIS \
  "                   --------------------------------------------\n" \
  "                     1   1   1   1   1   1   1   1   1   1   2\n" \
  "                     8   8   8   8   8   9   9   9   9   9   0\n" \
  "                     0   2   4   6   8   0   2   4   6   8   0\n" \
  "                     0   0   0   0   0   0   0   0   0   0   0\n"

/* Interactive */
#define STR_HELP\
  "\nCommands:\n" \
  "\tplot    word -- Display a plot showing a word's popularity over time. \n" \
  "\tdata    word -- List word occurrences by decade for a word. \n" \
  "\thelp         -- Display this message. \n\n" 
#define STR_COMMAND_PROMPT ">>> "
#define STR_END_PROMPT "\n"
#define STR_ERR_BAD_COMMAND "\n\tBad command.\n\n"
#define STR_ERR_COMMAND_MISSING_ARG "\n\tMissing argument(s) for command.\n\n"
#define STR_ERR_COMMAND_EXTRA_ARG \
  "\n\tUnexpected extra argument(s) encountered in command.\n\n"
#define STR_NO_DATA "\n\tNo data found for this word.\n\n"

#endif // PA3_STRINGS_H
