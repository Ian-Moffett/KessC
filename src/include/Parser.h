#ifndef PARSER_H
#define PARSER_H

#include <include/Debugger.h>
#include <include/Token.h>
#include <include/AST.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct {
    bool error;
    unsigned long long line;
    unsigned long long idx;
    tokenlist_t tokenlist;
    token_t currentToken;
    ast_t ast;
} parser_t;


void parser_init(parser_t* parser, tokenlist_t tokenlist);
void parse(parser_t* parser);


#endif
