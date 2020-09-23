#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "makeArg.h" // from another P.A assignment, I found one of my functions in here useful
const int NUM_OF_TOKENS = 13;

// problem: something at the end of str is accessed, and it can potentially match that if it happens to be a valid lexeme

char* tokenStr = "( ) , := - + / * = ; : [ ]";
char** TOKENS = NULL;


int* findNextToken(char* str);
int findNumOfTokens(char* str);
char** collectAllTokens(char* str);
void printSubstr(char* str, int startIndex, int endIndex);
int* findNextSubstr(char* substr, char* str);
int* findNextAlpha(char* str);
int* findNextNum(char* str);
int* findNextString(char* str);
int* findNextComment(char* str);

int main(int argc, char** argv)
{
    FILE *fp;
    char ch;
    int BUFFER_SIZE = 1024;

    char string[BUFFER_SIZE];
    fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        exit(0);
    }

    int i=0;
    while ((ch = fgetc(fp)) != EOF)
    {
        string[i] = ch;
        i++;
    }

    makearg(tokenStr, &TOKENS);
    char** lexemeArray = collectAllTokens(string);

}

int findNumOfTokens(char* str)
{    
    int* indexes = findNextToken(str);
    int count = 0;
    while (indexes = findNextToken(str))
    {
        // printf("%d %d\n", indexes[0], indexes[1]);
        str += indexes[1] + 1;
        count++;
    }
    return count;
}

void printSubstr(char* str, int startIndex, int endIndex)
{
    int i;
    for (i = startIndex; i <= endIndex; i++)
    {
        printf("%c", str[i]);
    }
}

int* findNextSubstr(char* substr, char* str)
{
    int substrLen = strlen(substr);
    int i, z;
    for (i=0; str[i] != '\0'; i++)
    {
        for (z=0; z < substrLen; z++)
        {
            if (str[i + z] != substr[z])
                break;
        }
        if (z == substrLen) // for loop completed, string matched
        {
            int* returnInt = malloc(sizeof(int)*2);
            returnInt[0] = i;
            returnInt[1] = i + substrLen-1;
            return returnInt;
        }
    }
    return NULL;
}

int* findNextToken(char* str)
{
    printf("start\n");
    if (strlen(str) == 0) return NULL;
    int i, z, minIndex;
    minIndex = strlen(str);
    int* indexes = calloc(sizeof(int), 2);

    if (findNextComment(str) != NULL && findNextComment(str)[0] < minIndex)
    {
        minIndex = findNextComment(str)[0];
        indexes[0] = findNextComment(str)[0];
        indexes[1] = findNextComment(str)[1];
    }

    if (findNextString(str) != NULL && findNextString(str)[0] < minIndex)
    {
        minIndex = findNextString(str)[0];
        indexes[0] = findNextString(str)[0];
        indexes[1] = findNextString(str)[1];
    }

    if (findNextAlpha(str) != NULL && findNextAlpha(str)[0] < minIndex)
    {
        minIndex = findNextAlpha(str)[0];
        indexes[0] = findNextAlpha(str)[0];
        indexes[1] = findNextAlpha(str)[1];
    }

    if (findNextNum(str) != NULL && findNextNum(str)[0] < minIndex)
    {
        minIndex = findNextNum(str)[0];
        indexes[0] = findNextNum(str)[0];
        indexes[1] = findNextNum(str)[1];
    }

    for (z = 0; z < NUM_OF_TOKENS; z++)
    {
        if (findNextSubstr(TOKENS[z], str) == NULL) // isnt found
            continue;

        if (findNextSubstr(TOKENS[z], str)[0] < minIndex)
        {
            minIndex = findNextSubstr(TOKENS[z], str)[0];
            indexes[0] = findNextSubstr(TOKENS[z], str)[0];
            indexes[1] = findNextSubstr(TOKENS[z], str)[1];
        }
    }

    
    printf("end\n");

    // printf("%d (%d, %d) %d %s\n", minIndex, indexes[0], indexes[1], strlen(str), str);
    if (minIndex == strlen(str))
        return NULL;
    else 
        return indexes;
}

// returns 2d char array
char** collectAllTokens(char* str)
{
    int tokenCount = findNumOfTokens(str);
    printf("%d tokenCount", tokenCount);

    // 2d char array
    char** strArray = malloc(sizeof(char*) * (tokenCount+1));
    strArray[tokenCount] = NULL;

    int* indexes = findNextToken(str);

    int i = 0;
    while (indexes = findNextToken(str))
    {

        int tokenLen = indexes[1] - indexes[0] + 1;
        strArray[i] = malloc(sizeof(char) * (tokenLen + 1)); // allocates memory for char array
        memcpy(strArray[i], str + indexes[0], sizeof(char) * tokenLen); // copies substr to strArray location
        strArray[tokenLen] = '\0';
        printSubstr(str, indexes[0], indexes[1]);
        printf("\n");

        str += indexes[1] + 1;
        i++;
    }
    return strArray;
}

// returns [start, end] indexes
int* findNextAlpha(char* str)
{
    int i;
    int inWord = 0;
    int wordStart = -1, wordEnd = -1;
    for (i = 0; i < strlen(str); i++)
    {
        if (inWord == 0 && (isalpha(str[i]) || str[i] == '_'))
        {
            inWord = 1;
            wordStart = i;
        }
        if (inWord == 1 && !(isalnum(str[i]) || str[i] == '_'))
        {
            wordEnd = i-1;
            int* ptr = malloc(sizeof(int) * 2);
            ptr[0] = wordStart;
            ptr[1] = wordEnd;
            return ptr;
        }
    }
    return NULL;
}

// returns [start, end] indexes
int* findNextNum(char* str)
{
    int i;
    int inNum = 0;
    int numStart = -1, numEnd = -1;
    for (i = 0; i < strlen(str); i++)
    {
        if (inNum == 0 && isdigit(str[i]))
        {
            inNum = 1;
            numStart = i;
        }
        if (inNum == 1 && !isdigit(str[i]))
        {
            numEnd = i-1;
            int* ptr = malloc(sizeof(int) * 2);
            ptr[0] = numStart;
            ptr[1] = numEnd;
            return ptr;
        }
    }
    return NULL;
}

// returns [start, end] indexes
int* findNextString(char* str)
{
    int i;
    int inStr = 0;
    int strStart = -1, strEnd = -1;
    for (i = 0; i < strlen(str); i++)
    {
        if (inStr == 0 && str[i] == '"')
        {
            inStr = 1;
            strStart = i;
            continue;
        }
        if (inStr == 1 && str[i] == '"')
        {
            strEnd = i;
            inStr = 0;
            int* ptr = malloc(sizeof(int) * 2);
            ptr[0] = strStart;
            ptr[1] = strEnd;
            return ptr;
        }
    }
    return NULL;
}

// returns [start, end] indexes
int* findNextComment(char* str)
{
    int i;
    int inStr = 0;
    int strStart = -1, strEnd = -1;
    for (i = 0; i < strlen(str)-1; i++)
    {
        if (inStr == 0 && str[i] == '/' && str[i+1] == '*')
        {
            inStr = 1;
            strStart = i;
            continue;
        }
        if (inStr == 1 && str[i] == '*' && str[i+1] == '/' && i != strStart+1) // if end of comment, and end of comment is not /*/
        {
            strEnd = i+1;
            inStr = 0;
            int* ptr = malloc(sizeof(int) * 2);
            ptr[0] = strStart;
            ptr[1] = strEnd;
            return ptr;
        }
    }
    return NULL;
}