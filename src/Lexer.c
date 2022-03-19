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
static void flushbuffer(char** buffer) {
    memset(*buffer, '\0', strlen(*buffer));
    *buffer = realloc(*buffer, sizeof(char) + 1);
}


static char* fetch_str(lexer_t* lexer) {
    char* strbuf = (char*)calloc(2, sizeof(char));
    unsigned long long strbufidx = 0;

    ++lexer->idx;
    strbuf[0] = '\0';
    for (int i = lexer->idx; i < strlen(lexer->buffer); ++i) {
        lexer->curChar = lexer->buffer[i];
        
        if (lexer->curChar == '"') {
            return strbuf;
        }

        strbuf[strbufidx] = lexer->curChar;
        ++strbufidx;
        strbuf = realloc(strbuf, sizeof(char) * (strbufidx + 1));
    }
}


static void review_buffer(lexer_t* lexer, const char* const BUFFER) {
    if (strcmp(BUFFER, "puts") == 0) {        
        tokenlist_push(&lexer->tokenlist, create_token("puts", T_PUTS, false));
    } else {

        for (int i = 0; i < strlen(BUFFER); ++i) {
            if (BUFFER[i] != ' ' && BUFFER[i] != '\t') {
                raise("Unexpected token!", lexer->lineNum);
                lexer->flags |= LFLAG_ERROR;
            }
        }
    }
}


void tokenize(lexer_t* lexer) {
    char* lexbuf = calloc(2, sizeof(char));     // Buffer for holding chars until we are ready to compare.
    unsigned long lbufidx = 0;
    unsigned char go = 1;

    // curlineEnd will be true when a semicolon is reached.
    // This can be used to determain if a semicolon was used.
    bool curlineEnd = false;

    while (lexer->idx < lexer->bufsize && !(lexer->flags & LFLAG_ERROR)) {
        lexer->curChar = lexer->buffer[lexer->idx];     // Set the current char.

        if (lexer->curChar == ' ') {
            review_buffer(lexer, lexbuf);
            flushbuffer(&lexbuf);
            ++lexer->idx;
            continue;
        }

        switch (lexer->curChar) {
            case '(':
                review_buffer(lexer, lexbuf);
                tokenlist_push(&lexer->tokenlist, create_token("(", T_LPAREN, false));
                flushbuffer(&lexbuf);
                break;
            case ')':
                tokenlist_push(&lexer->tokenlist, create_token("(", T_LPAREN, false));
                flushbuffer(&lexbuf);
                break;
            case '"':
                if (!(lexer->flags & LFLAG_IGNORE_QUOTE)) {
                    char* str = fetch_str(lexer);
                    tokenlist_push(&lexer->tokenlist, create_token(str, T_STR, true));
                    flushbuffer(&lexbuf);
                    lexer->flags |= LFLAG_IGNORE_QUOTE;
                }
                break;
            case ';':
                lexer->flags |= LFLAG_SEMI;
                
                if (lexer->flags & LFLAG_IGNORE_QUOTE) {
                    lexer->flags ^= LFLAG_IGNORE_QUOTE;
                }

                flushbuffer(&lexbuf);
                break;
            case '\n':
                if (!(lexer->flags & LFLAG_SEMI)) {
                    raise("Missing semicolon.", lexer->lineNum);
                    lexer->flags |= LFLAG_ERROR;
                    break;
                } else {
                    lexer->flags ^= LFLAG_SEMI;
                }
        }

        lexbuf[lbufidx++] = lexer->curChar;
        lexbuf = realloc(lexbuf, sizeof(char) * (lbufidx + 2));
        ++lexer->idx;
    }

    free(lexbuf);
}
