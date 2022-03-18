// Written by Ian-Moffett.

#include <include/Lexer.h>
#include <string.h>

void lexer_init(lexer_t* lexer, char* buffer) {
    lexer->bufsize = strlen(buffer);
    lexer->idx = 0;
    lexer->buffer = buffer;
    lexer->curChar = '\0';
}


void tokenize(tokenlist_t* tokenlist, lexer_t* lexer) {
    char* lexbuf = calloc(lexer->bufsize + 1, sizeof(char));

    while (lexer->idx < lexer->bufsize) {
        lexer->curChar = lexer->buffer[lexer->idx];
        ++lexer->idx;
    }

    free(lexbuf);
}
