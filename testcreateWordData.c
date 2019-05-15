/*
 * Filename: testcreateWordData.c
 * Author: Matt Roth
 * UserId: cs30xgs
 * Date: May 15th, 2019
 * Sources of help: Textbook, cse 30 website, lecture notes, discussion notes.
 */

#include <stdio.h>
#include <string.h>
#include "pa3.h"
#include "test.h"

/*
 * Unit Test for createWordData.c
 * Populates the fields of the wordDatastruct to represent the word
 * in wordStr, initializes all values in counts, and computes the 
 * hash value. 
 *
 */
unsigned int computeHash_test( const char * str ) {
  
  /** helper function to compute hash**/
  unsigned int hash = HASH_START_VAL;
  for ( int i = 0; str[i] != '\0'; i++ ) {
    hash = hash * HASH_PRIME + str[i];
  }
  return hash; 
}

void testcreateWordData() {

  const char * wordStr = "the";
  const char * wordStr2 = "TEST1234";
  const char * wordStr3 = "randomword";
  const char * wordStrlong = 
  "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
  const char * longStr = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
  
   
  unsigned int decade = 1980;
  unsigned int decade2 = 1760;
  unsigned int decade3 = 1800;

  unsigned int count = 1234567;
  unsigned int count3 = 200;

  int index =  (decade - MIN_DECADE) / YEARS_IN_DECADE;
  int index2 = (decade2 - MIN_DECADE) / YEARS_IN_DECADE;
  int index3 = (decade3 - MIN_DECADE) / YEARS_IN_DECADE;
  int i;

  wordData_t word_data1;
  wordData_t word_data2;

  /** initialize the data in word_data2**/
  strncpy(word_data2.word, "the", MAX_WORD_SIZE);
  word_data2.hashValue = computeHash( wordStr );
  for(i = 0; i < NUM_OF_DECADES; i++) {
    word_data2.counts[i] = 0;  
  }
  word_data2.counts[index] = 1234567;


  createWordData( &word_data1, wordStr, decade, count );

  /** Test #1 with two structs **/
  // test the hashvalue 
  TEST( (word_data1.hashValue ) == word_data2.hashValue);
  // test all the counts[] elements in the wordData 
  for ( i = 0; i < NUM_OF_DECADES; i++ ){
    if( i != index){
      TEST(( word_data1.counts[i] ) == 0);
    }else{
      // test the counts[index]     
      TEST( ( word_data1.counts[index] ) == word_data2.counts[index]); 
    }    
  }  
  // test the word 
  TEST( strcmp( word_data1.word, wordStr) == 0);


  
  createWordData( &word_data1, wordStr2, decade2, 0xFFFFFFFA );

 /** Test #2 hard code test **/
  // test the hashvalue 
  TEST( (word_data1.hashValue ) == computeHash_test( wordStr2));
  // test all the counts[] elements in the wordData 
  for ( i = 0; i < NUM_OF_DECADES; i++ ){
    if( i != index2){
      TEST(( word_data1.counts[i] ) == 0);
    }else{
      // test the counts[index]     
      TEST( ( word_data1.counts[index2] ) == 5555555); 
    }    
  }  
  // test the word 
  TEST( strcmp( word_data1.word, wordStr2) == 0);


  createWordData( &word_data1, wordStr3, decade3, count3);

 /** Test #3 hard code test **/ 
  // test the hashvalue 
  TEST( (word_data1.hashValue ) == computeHash_test( wordStr3 ));
  // test all the counts[] elements in the wordData 
  for ( i = 0; i < NUM_OF_DECADES; i++ ){
    if( i != index3){
      TEST(( word_data1.counts[i] ) == 0);
    }else{
      // test the counts[index]     
      TEST( ( word_data1.counts[index3] ) == 200); 
    }    
  }  
  // test the word 
  TEST( strcmp( word_data1.word, wordStr3 ) == 0);


  createWordData( &word_data1, wordStrlong, decade, count);

   TEST( (word_data1.hashValue ) == computeHash_test( wordStrlong ));
  // test all the counts[] elements in the wordData 
  for ( i = 0; i < NUM_OF_DECADES; i++ ){
    if( i != index){
      TEST(( word_data1.counts[i] ) == 0);
    }else{
      // test the counts[index]     
      TEST( ( word_data1.counts[index] ) == 1234567 ); 
    }    
  }  

  // test the word 
  TEST( strcmp( word_data1.word, longStr ) == 0); 

 }


int main( void ) {

  fprintf( stderr, "Running tests for createWordData.c...\n" );
  testcreateWordData();
  fprintf( stderr, "Done running tests!\n" );

  return 0;
}
