#ifndef SCANNER_H
#define SCANNER_H

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
void scanner(int argc, char** argv);


#endif