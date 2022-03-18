#ifndef TOKEN_H
#define TOKEN_H

#include <stdint.h>
#include <stdbool.h>


typedef enum {
    T_PRINT,
    T_STR,
    T_DEC,
} tokentype_t;


typedef struct {
    tokentype_t type;
    char* tok;
    bool heapAlloc;
} token_t;


// Tokenlist which is basically a linked list.
typedef struct TokenList {
    struct TokenList* next;
    token_t token;
} tokenlist_t;


void tokenlist_destroy(tokenlist_t* masterNode);
void tokenlist_add_node(token_t token);
token_t tokenlist_mknode(tokentype_t type, char* token, bool heapAlloc);


#endif
