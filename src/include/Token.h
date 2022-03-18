#ifndef TOKEN_H
#define TOKEN_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>


typedef enum {
    T_PUTS,
    T_STR,
    T_DEC,
} tokentype_t;


typedef struct {
    tokentype_t type;
    char* tok;
    bool heapAlloc;
} token_t;


typedef struct {
    token_t* tokens;
    size_t idx;
} tokenlist_t;


void tokenlist_destroy(tokenlist_t* tokenlist);
void tokenlist_push(tokenlist_t* tokenlist, token_t token);
void tokenlist_init(tokenlist_t* tokenlist);
token_t create_token(char* tok, tokentype_t type, bool heapAlloc); 

#endif
