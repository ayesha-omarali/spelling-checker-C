/*
 * Include the provided hashtable library
 */
#include "hashtable.h"

/*
 * Include the header file
 */
#include "philspel.h"

/*
 * Standard IO and file routines
 */
#include <stdio.h>

/*
 * General utility routines (including malloc())
 */
#include <stdlib.h>

/*
 * Character utility routines.
 */
#include <ctype.h>

/*
 * String utility routines
 */
#include <string.h>

/*
 * this hashtable stores the dictionary
 */
HashTable *dictionary;

/*
 * the MAIN routine.  You can safely print debugging information
 * to standard error (stderr) and it will be ignored in the grading
 * process, in the same way which this does.
 */
int main(int argc, char **argv){
  if(argc != 2){
    fprintf(stderr, "Specify a dictionary\n");


    /* tests for stringHash. */
    char *s, *r, *t, *v, *w;
    s = "hi";
    fprintf(stderr, "the hash for %s is %d\n", s, stringHash(s));
    r = "hello";
    fprintf(stderr, "the hash for %s is %d\n", r, stringHash(r));
    t = "a";
    fprintf(stderr, "the hash for %s is %d\n", t, stringHash(t));
    fprintf(stderr, "the hash for %s is %d\n", t, stringHash(t));
    v = "b";
    fprintf(stderr, "the hash for %s is %d\n", v, stringHash(v));

    /* test for stringEqual. */
    fprintf(stderr, "%s and %s : %d\n", s, r, stringEquals(s, r));
    w = "hello";
    fprintf(stderr, "%s and %s : %d\n", w, r, stringEquals(w, r));
    // printf(stderr, "%s and %s : %d\n", t, v, stringEquals(t, v));
    // printf(stderr, "%s and %s : %d\n", t, t, stringEquals(t, t));


    /* test for readDictionary. */
    dictionary = createHashTable(2255, &stringHash, &stringEquals);
    readDictionary("sampleDictionary");
    char *word = findData(dictionary, "sample");

    /* test for validWord. */
    fprintf(stderr, "%s is in the dictionary? should return 1 --> %d\n", word, validWord(word));
    // char *word2 = (char *) malloc(sizeof "dEvil");
    word = "SAMPLE";
    fprintf(stderr, "%s is in the dictionary? should return 1 --> %d\n", word, validWord(word));   
    char *word2 = "DEviL";
    fprintf(stderr, "%s is in the dictionary? should return 0 --> %d\n", word2, validWord(word2));
    char *word3 = "weIrD";
    fprintf(stderr, "%s is in the dictionary? should return 1 --> %d\n", word3, validWord(word3));
    word3 = "Weird";
    fprintf(stderr, "%s is in the dictionary? should return 0 --> %d\n", word3, validWord(word3));
    word3 = "sentence";
    fprintf(stderr, "%s is in the dictionary? should return 1 --> %d\n", word3, validWord(word3));
    word3 = "NorMal";
    fprintf(stderr, "%s is in the dictionary? should return 1 --> %d\n", word3, validWord(word3));
    word3 = "misspelled";
    fprintf(stderr, "%s is in the dictionary? should return 0 --> %d\n", word3, validWord(word3));
    word3 = "is";
    fprintf(stderr, "%s is in the dictionary? should return 1 --> %d\n", word3, validWord(word3));
    word3 = "BAD";
    fprintf(stderr, "%s is in the dictionary? should return 1 --> %d\n", word3, validWord(word3));
    word3 = "job";
    fprintf(stderr, "%s is in the dictionary? should return 0 --> %d\n", word3, validWord(word3));
    word3 = "sell";
    fprintf(stderr, "%s is in the dictionary? should return 0 --> %d\n", word3, validWord(word3));
    word3 = "nick";
    fprintf(stderr, "%s is in the dictionary? should return 1 --> %d\n", word3, validWord(word3));
    word3 = "NiCK";
    fprintf(stderr, "%s is in the dictionary? should return 1 --> %d\n", word3, validWord(word3));
    fprintf(stderr, "end of main \n");

    /* test for processInput. */


    return 0;
  }
  /*
   * Allocate a hash table to store the dictionary
   */
  fprintf(stderr, "Creating hashtable\n");
  dictionary = createHashTable(2255, &stringHash, &stringEquals);

  fprintf(stderr, "Loading dictionary %s\n", argv[1]);
  readDictionary(argv[1]);
  fprintf(stderr, "Dictionary loaded\n");

  fprintf(stderr, "Processing stdin\n");
  processInput();

  /* main in C should always return 0 as a way of telling
     whatever program invoked this that everything went OK
     */
  return 0;
}

/*
 * You need to define this function. void *s can be safely casted
 * to a char * (null terminated string) which is done for you here for
 * convenience.
 q's: why pass in void *s why not pass in char *s? the idea is its generic so you can pass in any kind of data. 
 take the bytes of any object and treat them as characters. void *s means a pointer to anything
 Citation: using java's hashcode function: s[0]*31^(1) + s[1]*31^(2) + ... + s[n-1]*31^(n)
 */
unsigned int stringHash(void *s){
  char *string = (char *) s;
  // fprintf(stderr,"Need to define stringHash\n");
  int i = 1, sum = 0;
  do {
    sum += *string * (31^i); /* how to distinguish between what is multiplicaiton and what is a dereferencer? */
  } while (*string++);
  return sum;
}

/*
 * You need to define this function.  It should return a nonzero
 * value if the two strings are identical (case sensitive comparison)
 * and 0 otherwise.
 */
int stringEquals(void *s1, void *s2){
  char *string1 = (char *) s1;
  char *string2 = (char *) s2;
  if (stringHash(string1) == stringHash(string2)) {
    return 1;
  } else return 0;
  // fprintf(stderr,"Need to define stringEquals\n");
  // exit(0);
}

/*
 * this function should read in every word in the dictionary and
 * store it in the dictionary.  You should first open the file specified,
 * then read the words one at a time and insert them into the dictionary.
 * Once the file is read in completely, exit.  You will need to allocate
 * (using malloc()) space for each word.  As described in the specs, you
 * can initially assume that no word is longer than 60 characters.  However,
 * for the final 20% of your grade, you cannot assumed that words have a bounded
 * length You can NOT assume that the specified file exists.  If the file does
 * NOT exist, you should print some message to standard error and call exit(0)
 * to cleanly exit the program. Since the format is one word at a time, with
 * returns in between, you can
 * safely use fscanf() to read in the strings.
 */
void readDictionary(char *filename){
  // fprintf(stderr,"Need to define readDictionary\n");
  // exit(0);
  //if file does not exist then exit
  //read in each word and store the words in a hashtable
  //should we have main read stdin (input) and pass the filename to this function or 
  // should we read stdin in this function? probably should use it in main.
  //how to store stuff in memory: Malloc returns a ptr, you can dereference that ptr to store/load stuff from that block of memory.
  // notes: words that get read into from readDictionary and pointed to by the hash table should not be freed

  //using fscanf parse input
  //for every word, malloc a block of memory and put data into the block.
  FILE *file;
  file = fopen(filename, "r");
  if( (fopen(filename, "r")) == NULL)
  {
    printf("No such file\n");
    exit(1);
  }
  //do a while loop to loop through all the words in the input file.
  char *str = NULL;
  while (!feof(file)) {
    //if reach the end of file, then return
    str = malloc(sizeof(char) * 60);
    fscanf(file, "%s", str);
    //now add pointer to the hashtable
    //use insertData
    insertData(dictionary, (void *) str, (void *) str);
  }
  fclose(file);
}


/*
 * This should process standard input and copy it to standard output
 * as specified in specs.  EG, if a standard dictionary was used
 * and the string "this is a taest of  this-proGram" was given to
 * standard input, the output to standard output (stdout) should be
 * "this is a teast [sic] of  this-proGram".  All words should be checked
 * against the dictionary as they are input, again with all but the first
 * letter converted to lowercase, and finally with all letters converted
 * to lowercase.  Only if all 3 cases are not in the dictionary should it
 * be reported as not being found, by appending " [sic]" after the
 * error.
 *
 * Since we care about preserving whitespace, and pass on all non alphabet
 * characters untouched, and with all non alphabet characters acting as
 * word breaks, scanf() is probably insufficent (since it only considers
 * whitespace as breaking strings), so you will probably have
 * to get characters from standard input one at a time.
 *
 * As stated in the specs, you can initially assume that no word is longer than
 * 60 characters, but you may have strings of non-alphabetic characters (eg,
 * numbers, punctuation) which are longer than 60 characters. For the final 20%
 * of your grade, you can no longer assume words have a bounded length.
 */
void processInput(){
  // fprintf(stderr,"Need to define processInput\n");
  // exit(0);

  //two while loops
  //getchar returns the actual character, not a pointer.
  
  //how to find sampleInput?
  //define file.
  char *p = NULL;
  char *c = NULL;
  char t = getchar();
  while (t != EOF) {
    //pointer to front of word.
    p = malloc(sizeof(char) * 60);
    //pointer that traverses through the characters in a word.
    c = p;
    // *c = getchar();

    //why can't we just use:
    // p = malloc(sizeof c)
    // do we need to use remalloc?

    

    while (!isalpha((int) t)) {
      if (t == EOF) {
        exit(0);
      }
      fprintf(stdout, "%c", t);
      fprintf(stderr, "%c", t);      
      t = getchar();
    }
    while (isalpha((int) t)) {
      *c = t;
      t = getchar();
      c++;
      if (t == EOF) {
        break;
      }
    }
    //print the word
    fprintf(stdout, "%s", p);
    fprintf(stderr, "%s", p);    
    //check if word is valid
    if (!validWord(p)) {
        fprintf(stderr, " [sic]"); //debugging
        fprintf(stdout, " [sic]");
    }
    fprintf(stderr, "outer loop \n");
  }

  exit(0);
  



  

  


  
  // while (c != EOF)

  //must read input character by character
  //read input until reach end of a word
  //check it's three permutations against the dictionary
  //output word and [sic], if appropriate, to std output

  //check if the character is EOF (end of file), if so exit.



}

int validWord(char *word) {
  char *pointer = malloc(sizeof word);
  pointer = word;
  //check the original word against the dictionary
  fprintf(stderr, "pointer: %s \n", pointer);
  int found = 0;
  if (findData(dictionary, word) != NULL) {
    fprintf(stderr, "found ya \n");
    found = 1;
  } else {
    int i = 0;
    char lower[strlen(word)+1];
    fprintf(stderr, "lower: %s \n", lower);
    /* leave the first character in the word unchanged. */
    lower[i] = *pointer;
    pointer++;
    i++;
    fprintf(stderr, "first char: %s \n", lower);

    /* make the rest of the word lower case. */
    for ( ; *pointer; pointer++) {
      lower[i] = (char) tolower(*pointer);
      i++;
    }
    fprintf(stderr, "rest of the word, lower: %s \n", lower);

    lower[strlen(word)] = '\0';
    fprintf(stderr, "with null term. lower: %s \n", lower);
    int b = (findData(dictionary, lower) != NULL);
    fprintf(stderr, "%s is in dict: %i \n", lower, b);

    // printf("%s is in the dictionary: %d \n", lower, findData(dictionary, lower) != NULL);
    if (findData(dictionary, lower) != NULL) {
      found = 1;
    } else {
      /* convert the first character to lower case as well so the entire word is lower case. */
      lower[0] = (char) tolower(lower[0]);
      // printf("%s is in the dictionary: %d \n", lower, findData(dictionary, lower) != NULL);
      fprintf(stderr, "all lower: %s \n", lower);
      // fprintf(stderr, "later \n");
      if (findData(dictionary, lower) != NULL) {
        found = 1;
      }
    }
  }
  fprintf(stderr, "done \n");
  return found;
}
