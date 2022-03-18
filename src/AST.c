#include <include/AST.h>

void ast_init(ast_t* ast) {
    ast->nodes = malloc(sizeof(ast_node_t));
    ast->idx = 0;
}


void ast_push_node(ast_t* ast, ast_node_t node) {
    ast->nodes[ast->idx++] = node;
    ast->nodes = realloc(ast->nodes, sizeof(ast_node_t) * (ast->idx + 1));
}


ast_node_t ast_create_node(char* typelabel, char* token) {
    ast_node_t node = {
        .type = typelabel, 
    };

   node.value.str = token;
   return node;
}


ast_node_t ast_create_nodeint(char* typelabel, uint64_t dec) {
    ast_node_t node = {
        .type = typelabel
    };

    node.value.dec = dec;
}


void ast_destroy(ast_t ast) {
    free(ast.nodes);
}
