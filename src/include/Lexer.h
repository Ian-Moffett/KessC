#ifndef LEXER_H
#define LEXER_H

#include <string.h>
#include <include/Token.h>
#include <stdlib.h>

typedef struct {
	size_t idx;
    size_t bufsize;
    char*  buffer;
    char curChar;
} lexer_t;


void lexer_init(lexer_t* lexer, char* buffer);
void tokenize(tokenlist_t* tokenlist, lexer_t* lexer);


#endif
