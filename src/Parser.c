#include <include/Parser.h>

#define PARSER_DUMP_TOKENS

#ifdef PARSER_DUMP_TOKENS
#define TOKEN_COUNT 6
const char* tokens[] = {
    "T_PUTS",
    "T_STR",
    "T_DEC",
    "T_LPAREN",
    "T_RPAREN",
    "<unknown>"
};
#endif


void parser_init(parser_t* parser, tokenlist_t tokenlist) {
    parser->error = false;
    parser->line = 1;
    parser->idx = 0;
    parser->tokenlist = tokenlist;
}


static token_t peek(parser_t* parser, uint16_t offset) {
    return parser->tokenlist.tokens[parser->idx + offset];
}


void parse(parser_t* parser) { 
    ast_t ast = {
        .nodes = malloc(sizeof(ast_node_t)),
        .idx = 0
    };

    parser->ast = ast;

    while (parser->idx < parser->tokenlist.idx) {
        parser->currentToken = parser->tokenlist.tokens[parser->idx];
        #ifdef PARSER_DUMP_TOKENS
        parser->currentToken.type < TOKEN_COUNT ? printf("%s\n", tokens[parser->currentToken.type]) : printf("");
        #endif

        switch (parser->currentToken.type) {
            case T_PUTS:
                ast_push_node(&parser->ast, ast_create_node("STDOUT_WRITE", peek(parser, 2).tok));
        }

        ++parser->idx;
    }
}
