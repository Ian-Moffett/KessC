#include <include/Token.h>


void tokenlist_destroy(tokenlist_t* tokenlist) {
    for (int i = 0; i < tokenlist->idx + 1; ++i) {
        if (tokenlist->tokens[i].heapAlloc) {
            free(tokenlist->tokens[i].tok);
        }
    }

    free(tokenlist->tokens);
    tokenlist->tokens = NULL;
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
