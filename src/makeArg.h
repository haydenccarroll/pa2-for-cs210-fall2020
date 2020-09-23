// Name: makeArg.h
// Author: Hayden Carroll
// Date-last-modified: 9/13/20
// Description: Header file for makeArg.c. Contains function prototypes and a struct definition needed for 
// tokenizing an argument list.

#ifndef MAKEARG_H
#define MAKEARG_H

/** 
 * @struct wordIndexes
 * @brief a struct of useful information for an char* argument list such as "ls -l file"
*/
struct wordIndexes
{
    int numWords;  ///<numWords An int representing the number of words found in the corresponding char*
    int *wordStartIndexes; ///< A dynamically allocated int array with the indexes of each word start.
    int *wordEndIndexes; ///< A dynamically allocated int array with the indexes of each word end.
};

int makearg(char s[], char ***args);
struct wordIndexes locateWords(char s[]);
// void allocateMemory(struct wordIndexes wordStruct, char ***args);


#endif