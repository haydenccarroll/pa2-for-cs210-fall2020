#ifndef SCANNER_H
#define SCANNER_H

#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "makeArg.h" // from another P.A assignment, I found one of my functions in here useful

struct Indexes
{
    int start;
    int end;
};

struct Indexes findNextToken(char* str, int NUM_OF_TOKENS, char** TOKENS);
int findNumOfTokens(char* str, int NUM_OF_TOKENS, char** TOKENS);
char** collectAllTokens(char* str, int NUM_OF_TOKENS, char** TOKENS);
void printSubstr(char* str, int startIndex, int endIndex);
struct Indexes findNextSubstr(char* substr, char* str);
struct Indexes findNextAlpha(char* str);
struct Indexes findNextNum(char* str);
struct Indexes findNextString(char* str);
struct Indexes findNextComment(char* str);
char** scanner(int argc, char** argv);


#endif