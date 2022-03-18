#ifndef AST_H
#define AST_H

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>


typedef struct {
    const char* type;

    union {
        char* token;
        uint64_t tokenInt;
    } value;
} ast_node_t;


typedef struct {
    ast_node_t* nodes;
    size_t idx;
} ast_t;


void ast_init(ast_t* ast);
void ast_push_node(ast_t* ast, ast_node_t node);
ast_node_t ast_create_node(const char* typelabel, const char* token);
ast_node_t ast_create_nodeint(const char* typelabel, uint64_t token);
void ast_destroy(ast_t ast);

#endif
