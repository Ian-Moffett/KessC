// Written by Ian-Moffett.

#include <include/Lexer.h>

void lexer_init(lexer_t* lexer, char* buffer) {
    lexer->bufsize = strlen(buffer);
    lexer->idx = 0;
    lexer->buffer = buffer;
    lexer->curChar = '\0';
    lexer->lineNum = 1;
    lexer->flags = 0x0;
}


// This function will flush any buffer you pass to it by nulling it out.
static void flushbuffer(char* buffer) {
    memset(buffer, '\0', strlen(buffer));
}


void tokenize(lexer_t* lexer) {
    char* lexbuf = calloc(2, sizeof(char));     // Buffer for holding chars until we are ready to compare.
    unsigned long lbufidx = 0;

    // curlineEnd will be true when a semicolon is reached.
    // This can be used to determain if a semicolon was used.
    bool curlineEnd = false;

    while (lexer->idx < lexer->bufsize) {
        lexer->curChar = lexer->buffer[lexer->idx];     // Set the current char.

        // Check if newline.
        if (lexer->curChar == '\n') {
            if (!(curlineEnd)) {            // Make sure there was a semicolon, if not raise an error.
                raise("Missing semicolon.", lexer->lineNum);
                lexer->flags | LFLAG_ERROR;
                break;
            }

            curlineEnd = false;
            flushbuffer(lexbuf);        // Flush the buffer to prevent newline inside.
            ++lexer->lineNum;           // Newline = increment line num.
        }

        switch (lexer->curChar) {
            case ';':
                curlineEnd = true;
            case ' ':
                // Check if we aren't ignoring whitespace.
                if (!(lexer->flags & LFLAG_IGNORE_WHITESPACE)) {
                    // Begin checking the buffer.
                    if (strcmp(lexbuf, "puts")) {
                        // TODO: Add to tokenlist.
                    }
                }

                flushbuffer(lexbuf);
                break;

        }

        ++lbufidx;                                      // Increment index after done using current char.
        lexbuf = realloc(lexbuf, sizeof(char) * lbufidx + 1);       // Realloc the buffer somewhere else in memory.
        ++lexer->idx;                                               // Increment buffer index.
    }

    free(lexbuf);
}
