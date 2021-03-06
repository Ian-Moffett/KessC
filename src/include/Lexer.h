#ifndef LEXER_H
#define LEXER_H

#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <include/Token.h>
#include <include/Debugger.h>

#define LFLAG_IGNORE_WHITESPACE 1
#define LFLAG_ERROR (1 << 1)
#define LFLAG_IGNORE_QUOTE (1 << 2)
#define LFLAG_SEMI (1 << 3)


// Основная структура лексера.
typedef struct {
	size_t idx;
    size_t bufsize;
    uint64_t lineNum;
    char* buffer;
    char curChar;
    tokenlist_t tokenlist;
    uint8_t flags;
} lexer_t;


void lexer_init(lexer_t* lexer, char* buffer);
void tokenize(lexer_t* lexer);


#endif
