#ifndef LEXER_H
#define LEXER_H

#include <string.h>
#include <include/Token.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Основная структура лексера.
typedef struct {
	size_t idx;
    size_t bufsize;
    char*  buffer;
    char curChar;
    tokenlist_t tokenlist;
} lexer_t;


void lexer_init(lexer_t* lexer, char* buffer);
void tokenize(lexer_t* lexer);


#endif
