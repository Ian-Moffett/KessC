#ifndef AST_H
#define AST_H

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>


typedef struct {
    const char* type;

    union {
        char* str;
        uint64_t dec;
    } value;
} ast_node_t;


typedef struct {
    ast_node_t* nodes;
    size_t idx;
} ast_t;


void ast_init(ast_t* ast);
void ast_push_node(ast_t* ast, ast_node_t node);
ast_node_t ast_create_node(char* typelabel, char* str);
ast_node_t ast_create_nodeint(char* typelabel, uint64_t dec);
void ast_destroy(ast_t ast);

#endif
