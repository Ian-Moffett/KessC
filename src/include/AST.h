#ifndef AST_H
#define AST_H

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>


typedef struct AstNode {
    const char* type;
    struct AstNode* children;
    unsigned int childrenIdx;

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
void node_init_children(struct AstNode** childrenPtr);
void node_push_child(ast_node_t* dest, ast_node_t src);
void ast_destroy(ast_t ast);

#endif
