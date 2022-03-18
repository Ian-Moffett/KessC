#include <include/Token.h>


void tokenlist_destroy(tokenlist_t* tokenlist) {
    // Iterate through all tokens.
    for (int i = 0; i < tokenlist->idx + 1; ++i) {
        // Check if token str is allocated on heap.
        if (tokenlist->tokens[i].heapAlloc) {
            // If so, free that token.
            free(tokenlist->tokens[i].tok); 
        }
    }

    free(tokenlist->tokens);    // Now free the token list.
    tokenlist->tokens = NULL;   // Also set it to NULL.
}


void tokenlist_push(tokenlist_t* tokenlist, token_t token) {
    tokenlist->tokens[tokenlist->idx++] = token;
    tokenlist->tokens = realloc(tokenlist->tokens, sizeof(token_t) * (tokenlist->idx + 1));
}


token_t create_token(char* tok, tokentype_t type, bool heapAlloc) {
    token_t token = {
        .tok = tok,
        .type = type,
        .heapAlloc = heapAlloc
    };

    return token;
}



void tokenlist_init(tokenlist_t* tokenlist) {
    tokenlist->tokens = malloc(sizeof(token_t));
    tokenlist->idx = 0;
}
