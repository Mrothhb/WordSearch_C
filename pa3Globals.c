/*
 * Filename: pa3Globals.c
 * Author: TODO
 * UserId: TODO
 * Date: TODO
 * Sources of help: Given.
 */

#include "pa3.h"
#include "pa3Strings.h"

// Used in computeHash().
unsigned int G_HASH_START_VAL = HASH_START_VAL;
unsigned int G_HASH_PRIME = HASH_PRIME;

// Offsets of wordData struct members.
size_t G_WORD_OFFSET = offsetof( wordData_t, word );
size_t G_COUNTS_OFFSET = offsetof( wordData_t, counts );
size_t G_HASHVALUE_OFFSET = offsetof( wordData_t, hashValue );
