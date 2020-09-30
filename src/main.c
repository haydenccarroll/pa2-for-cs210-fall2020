#include "scanner.h"
#include "lexer.h"
int main(int argc, char** argv)
{
    char** lexemes = scanner(argc, argv);
    identifyLexemes(lexemes);
}
