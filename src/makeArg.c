// Name: makeArg.c
// Author: Hayden Carroll
// Date-last-modified: 9/13/20
// Description: Implementation file for makeArg. Used to create a word-separated 2d char* array
//              from a char array. Example can be foud in main.c

#include <stdlib.h>
#include <string.h>

#include "makeArg.h"

/**
 * @brief Takes an input char array s, and stores a word separated 2d char* array
 * into the destination char*** args.
 *
 * The last row of the 2d char** array is NULL, and all strings in the columns are null terminated.
 * For example,  
 *   char str[] = "Hello World!";
 *   char **arr;
 *   makearg(str, &arr)
 *   changes arr into a 2d char array like this: ['Hello\0', 'World\0', NULL]
 * 
 * @param s A char array containing an argument list such as "ls -l file"
 * @param args A pointer to an array of char*. Used to store the word separated array.
 * @return -1 if some problem occurs, otherwise the number of words found
*/
int makearg(char s[], char ***args)
{
    struct wordIndexes wordStruct = locateWords(s);
    (*args) = (char**) malloc(sizeof(char*) * (wordStruct.numWords + 1)); // allocates memory for each word + 1 for NULL
    (*args)[wordStruct.numWords] = NULL; // last element is NULL

    int i=0;
    for (i=0; i < wordStruct.numWords; i++)
    {
        int start = wordStruct.wordStartIndexes[i]; // start index of word
        int end = wordStruct.wordEndIndexes[i]; // end index of word
        int wordSize = end - start + 1;

        (*args)[i] = (char*) malloc(sizeof(char) * (wordSize+1)); // allocates memory for each char + 1 for '\0'
        memcpy((*args)[i], &(s[start]), sizeof(char)*(wordSize)); // copies string from s to args
        (*args)[i][wordSize] = '\0';
    }

    // free dynamic memory
    free(wordStruct.wordStartIndexes);
    free(wordStruct.wordEndIndexes);

    return (wordStruct.numWords != 0) ? wordStruct.numWords : -1; // return number of words if words != else -1

}

// /**
//  * @brief locates words found in s and returns a wordIndexes struct with relevant information 
//  * @param s A char array containing an argument list such as "ls -l file"
//  * @return wordIndexes A struct containing parallel arrays of start/end indexes for each word, 
//  *         as well as number of words
// */
struct wordIndexes locateWords(char s[])
{
    // parallel arrays that correlate with word start and word end
    int *wordStartIndexes = (int *) malloc(strlen(s) * sizeof(int));
    int *wordEndIndexes =  (int *) malloc(strlen(s) * sizeof(int));

    int numWords = 0;
    int inWord = 0;
    int index = 0;

    while (1)
    {

        // if whitespace or \0
        if (s[index] == ' ' || s[index] == '\t' || s[index] == '\0' || s[index] == '\n')
        {
            if (inWord == 1) // if inside a word
            {
                wordEndIndexes[numWords-1] = index-1;
                inWord = 0;
            }
        }
        else // character isnt whitespace or \0
        {
            if (inWord == 0) // if not in word
            {
                inWord = 1;
                wordStartIndexes[numWords] = index;
                numWords++;
            }
        }

        if (s[index] == '\0')
            break;

        index++;
    }

    // return struct
    struct wordIndexes returnStruct;
    returnStruct.numWords = numWords;
    returnStruct.wordStartIndexes = wordStartIndexes;
    returnStruct.wordEndIndexes = wordEndIndexes;
    return returnStruct;
}