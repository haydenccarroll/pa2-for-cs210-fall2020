#include <stdlib.h>
#include <string.h>

#include "lexer.h"
#include "scanner.h"
#include "makeArg.h"


int isNumericLiteral(char* str);
int isIndentifier(char* str);

int isString(char* str);
int isComment(char* str);
int isKeyword(char* str);
int isOperator(char* str);



int isComment(char* str)
{
    return (findNextSubstr("/*" ,str).start == 0 && 
            findNextSubstr("*/" , str).end == strlen(str)-1);
}

int isString(char* str)
{
    return (findNextSubstr("\"" ,str).start == 0 && 
            findNextSubstr("\"" , str).end == strlen(str)-1);
}

int isOperator(char* str)
{
    char** OPERATORS;
    makearg(". < > ( ) + - * / | & ; , : [ ] = := .. << >> <> <= >= ** != =>", &OPERATORS);

    for (int i=0; OPERATORS[i] != NULL; i++)
    {
        if (strcmp(OPERATORS[i], str) == 0)
            return 1;
    }
    return 0;
}

int isKeyword(char* str)
{
    char** KEYWORDS;
    makearg("main key word keywords filler text", &KEYWORDS);

    for (int i=0; KEYWORDS[i] != NULL; i++)
    {
        if (strcmp(KEYWORDS[i], str) == 0)
            return 1;
    }
    return 0;
}

int isIndentifier(char* str)
{
    
}