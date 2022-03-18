// Written by Ian-Moffett.

#include <include/Lexer.h>

void lexer_init(lexer_t* lexer, char* buffer) {
    lexer->bufsize = strlen(buffer);
    lexer->idx = 0;
    lexer->buffer = buffer;
    lexer->curChar = '\0';
}


void tokenize(lexer_t* lexer) {
    char* lexbuf = calloc(2, sizeof(char));
    unsigned long lbufidx = 0;

    while (lexer->idx < lexer->bufsize) {
        lexer->curChar = lexer->buffer[lexer->idx];     // Set the current char.
        ++lbufidx;                                      // Increment index after done using current char.

        lexbuf = realloc(lexbuf, sizeof(char) * lbufidx + 1);       // Realloc the buffer somewhere else in memory.
        ++lexer->idx;                                               // Increment buffer index.
    }

    free(lexbuf);
}
