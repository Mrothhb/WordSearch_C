
/*
 * Filename: 
 * Author: Matt Roth
 * UserId: cs30xgs
 * Date: May 15th, 2019 
 * Sources of help: Textbook, cse 30 website, lecture notes, discussion notes.
 */

#include <stdio.h>
#include "pa3.h"
#include "test.h"

/*
 * Unit Test for computeHash.c
 *
 int computeHash( tableSlot_t * slot, const char * word,
 *                   unsigned int decade, unsigned int count );
 *
 * This function will be used to create the hash value of a string. This 
 * function creates an unsigned integer hash value from strwith the following 
 * hashing algorithm. Your task is to translate this algorithm into assembly. 
 * Use the global variables defined in pa3Globals.cto access these constants in 
 * assembly. Refer to the discussion worksheet on accessing global variables in 
 * Assembly
  */

/*
 * helper function to test against the assembly code
 */
unsigned int computeHash_c( const char * str ) {

 unsigned int hash = HASH_START_VAL;
  for ( int i = 0; str[i] != '\0'; i++ ) {
    hash = hash * HASH_PRIME + str[i];
  }
  return hash; 

}

void testcomputeHash() {
  
  // zero the testers 
  unsigned int valid_s = 0;
  unsigned int valid_c = 0;
  
  const char * str = "H";
  const char * str2 = "1234";
  const char * str3 = "";
  const char * str4 = " 1 s e f^ %!";
  const char * str5 = 
  "efoigrgrhgjsklhgkjrlhgskdhgskrhgkrshgskhgkghsdkhgsdkjrhgdklifguj jsenfvnkla";
  const char * str6 = NULL;
  const char * str7 = '\0';
  const char * str8 = "                        ";

  
  valid_s = computeHash( "apple" );
  valid_c = computeHash_c( "apple" );
  TEST( valid_s == valid_c );   // hardcode the hash value 
  printf("%ld\n\n\n", valid_s);

  valid_s = computeHash( str2 );
  valid_c = computeHash_c( str2 );
  TEST( valid_s == valid_c );

  valid_s = computeHash( str3 );
  valid_c = computeHash_c( str3 );
  TEST( valid_s == valid_c );

  valid_s = computeHash( str4 );
  valid_c = computeHash_c( str4 );
  TEST( valid_s == valid_c );

  valid_s = computeHash( str5 );
  valid_c = computeHash_c( str5 );
  TEST( valid_s == valid_c );
  
  valid_s = 0;
  valid_s = computeHash( str6 );
  //valid_c = computeHash_c( str6 );
  TEST( valid_s == 0 );

  valid_s = computeHash( str7 );
  //valid_c = computeHash_c( str7 );
  TEST( valid_s == 0 );

  valid_s = computeHash( str8 );
  valid_c = computeHash_c( str8 );
  TEST( valid_s == valid_c );

  valid_s = computeHash( "HARDCODE_STRING" );
  valid_c = computeHash_c( "HARDCODE_STRING");
  TEST( valid_s == valid_c );

  valid_s = computeHash( "" );
  valid_c = computeHash_c( "");
  TEST( valid_s == valid_c );

  TEST( computeHash("hello") == computeHash_c("hello"));
 }

int main( void ) {

  fprintf( stderr, "Running tests for testcomputeHash...\n" );
  testcomputeHash();
  fprintf( stderr, "Done running tests!\n" );

  return 0;
}
