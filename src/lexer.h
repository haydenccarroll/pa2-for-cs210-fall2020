#ifndef LEXER_H
#define LEXER_H

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "scanner.h"
#include "makeArg.h"

int isNumericLiteral(char* str);
int isIndentifier(char* str);
int isString(char* str);
int isComment(char* str);
int isKeyword(char* str);
int isOperator(char* str);


void printToken(char* lexeme);
void identifyLexemes(char** lexemes);

#endif