#include "scanner.h"



char** scanner(int argc, char** argv)
{
    char* tokenStr = ":= .. << >> <> <= >= ** != -> . < > ( ) + - * / | & ; , : [ ] =";
    char** TOKENS = NULL;
    const int NUM_OF_TOKENS = makearg(tokenStr, &TOKENS);

    FILE *fp;
    char ch;
    int BUFFER_SIZE = 2048;
    char string[BUFFER_SIZE];
    fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        exit(0);
    }

    int i=0;
    while ((ch = fgetc(fp)) != EOF)
        string[i++] = ch;
    string[i] = '\0';
    fclose(fp);

    return collectAllTokens(string, NUM_OF_TOKENS, TOKENS);
}

int findNumOfTokens(char* str, int NUM_OF_TOKENS, char** TOKENS)
{    
    struct Indexes indexes = {-1, -1};
    int count = 0;

    while (findNextToken(str, NUM_OF_TOKENS, TOKENS).start != -1)
    {
        indexes = findNextToken(str, NUM_OF_TOKENS, TOKENS);
        str += indexes.end + 1;
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

struct Indexes findNextSubstr(char* substr, char* str)
{
    struct Indexes returnIndexes = {-1, -1};
    int substrLen = strlen(substr);
    int i, z;
    for (i=0; i < strlen(str); i++)
    {
        for (z=0; z < substrLen && str[i+z] != '\0'; z++)
        {
            if (str[i + z] != substr[z])
                break;
        }
        if (z == substrLen) // for loop completed, string matched
        {
            returnIndexes.start = i;
            returnIndexes.end = i + substrLen-1;
            return returnIndexes;
        }
    }
    return returnIndexes;
}

struct Indexes findNextToken(char* str, int NUM_OF_TOKENS, char** TOKENS)
{
    struct Indexes returnIndexes = {-1, -1};
    if (strlen(str) == 0) return returnIndexes;
    int i, z, minIndex;
    minIndex = strlen(str); // sets minIndex as high as the minIndex could possibly be

    if (findNextComment(str).start != -1 && findNextComment(str).start < minIndex)
    {
        minIndex = findNextComment(str).start;
        returnIndexes.start = findNextComment(str).start;
        returnIndexes.end = findNextComment(str).end;
    }

    if (findNextString(str).start != -1 && findNextString(str).start < minIndex)
    {
        minIndex = findNextString(str).start;
        returnIndexes.start = findNextString(str).start;
        returnIndexes.end = findNextString(str).end;
    }

    if (findNextAlpha(str).start != -1 && findNextAlpha(str).start < minIndex)
    {
        minIndex = findNextAlpha(str).start;
        returnIndexes.start = findNextAlpha(str).start;
        returnIndexes.end = findNextAlpha(str).end;
    }

    if (findNextNum(str).start != -1 && findNextNum(str).start < minIndex)
    {
        minIndex = findNextNum(str).start;
        returnIndexes.start = findNextNum(str).start;
        returnIndexes.end = findNextNum(str).end;
    }

    for (z = 0; z < NUM_OF_TOKENS; z++)
    {
        if (findNextSubstr(TOKENS[z], str).start != -1 && 
            findNextSubstr(TOKENS[z], str).start < minIndex)
        {
            minIndex = findNextSubstr(TOKENS[z], str).start;
            returnIndexes.start = findNextSubstr(TOKENS[z], str).start;
            returnIndexes.end = findNextSubstr(TOKENS[z], str).end;
        }
    
    }
    return returnIndexes;
}

// returns 2d char array
char** collectAllTokens(char* str, int NUM_OF_TOKENS, char** TOKENS)
{
    int tokenCount = findNumOfTokens(str, NUM_OF_TOKENS, TOKENS);

    // 2d char array
    char** strArray = malloc(sizeof(char*) * (tokenCount+1));
    strArray[tokenCount] = NULL;

    struct Indexes indexes = {-1, -1};

    int i = 0;
    while (findNextToken(str, NUM_OF_TOKENS, TOKENS).start != -1)
    {
        indexes = findNextToken(str, NUM_OF_TOKENS, TOKENS);

        int tokenLen = indexes.end - indexes.start + 1;
        strArray[i] = malloc(sizeof(char) * (tokenLen + 1)); // allocates memory for char array
        memcpy(strArray[i], str + indexes.start, sizeof(char) * tokenLen); // copies substr to strArray location
        strArray[i][tokenLen] = '\0';

        /**
         *  Uncomment this to print values as they are found
         **/

        // printSubstr(str, indexes.start, indexes.end);
        // printf("\n");

        str += indexes.end + 1;
        i++;
    }
    return strArray;
}

// returns [start, end] indexes
struct Indexes findNextAlpha(char* str)
{
    int i;
    int inWord = 0;
    int wordStart = -1, wordEnd = -1;
    struct Indexes returnIndexes = {-1, -1};
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
            returnIndexes.start = wordStart;
            returnIndexes.end = wordEnd;
            return returnIndexes;
        }
    }
    return returnIndexes;
}

// returns [start, end] indexes
struct Indexes findNextNum(char* str)
{
    struct Indexes returnIndexes = {-1, -1};
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
            returnIndexes.start = numStart;
            returnIndexes.end = numEnd;
            return returnIndexes;
        }
    }
    return returnIndexes;
}

// returns [start, end] indexes
struct Indexes findNextString(char* str)
{
    struct Indexes returnIndexes = {-1, -1};
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
            returnIndexes.start = strStart;
            returnIndexes.end = strEnd;
            return returnIndexes;
        }
    }
    return returnIndexes;
}

// returns [start, end] indexes
struct Indexes findNextComment(char* str)
{
    int i;
    struct Indexes returnIndexes = {-1, -1};
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
            returnIndexes.start = strStart;
            returnIndexes.end = strEnd;
            return returnIndexes;
        }
    }
    return returnIndexes;
}