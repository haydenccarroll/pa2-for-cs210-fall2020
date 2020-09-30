#include "lexer.h"




void identifyLexemes(char** lexemes)
{

    for (int i=0; lexemes[i] != NULL; i++)
    {
        printToken(lexemes[i]);
    }
}

void printToken(char* lexeme)
{
    if (isKeyword(lexeme))
        printf("%s (keyword)\n", lexeme);
    else if (isIndentifier(lexeme))
        printf("%s (identifier)\n", lexeme);
    else if (isString(lexeme))
        printf("%s (string)\n", lexeme);
    else if (isOperator(lexeme))
        printf("%s (operator)\n", lexeme);
    else if (isComment(lexeme))
        printf("%s (comment)\n", lexeme);
    else if (isNumericLiteral(lexeme))
        printf("%s (numeric literal)\n", lexeme);
    else
        printf("%s (UNKOWN)\n", lexeme);
    
}

int isComment(char* str)
{
    return (findNextSubstr("/*" ,str).start == 0 && 
            findNextSubstr("*/" , str).end == strlen(str)-1);
}

int isString(char* str)
{
    return (str[0] == '"' && str[strlen(str)-1] == '"');
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
    makearg("accessor and array begin bool case character constant else elsif end exit function \
             if in integer interface is loop module mutator natural null of or others out positive \
             procedure range return struct subtype then type when while", &KEYWORDS);

    for (int i=0; KEYWORDS[i] != NULL; i++)
    {
        if (strcmp(KEYWORDS[i], str) == 0)
            return 1;
    }
    return 0;
}

int isIndentifier(char* str)
{
    if (!isalpha(str[0]))
        return 0;

    while (*++str != '\0')
    {
        if (!(isalnum(*str) || *str == '_'))
            return 0;
    }
    return 1;
}


int isNumericLiteral(char* str)
{
    if (!isdigit(str[0]))
        return 0;

    while (*++str != '\0')
    {
        if (!(isxdigit(*str) || *str == '-' || *str == '.' || *str == '#'))
            return 0;
    }
    return 1;
}
