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
        .type = typelabel,
        .children = NULL,
        .childrenIdx = 0
    };

    node.value.dec = dec;
}

void node_init_children(struct AstNode** childrenPtr) {
    *childrenPtr = malloc(sizeof(struct AstNode));
}


void node_push_child(ast_node_t* dest, ast_node_t src) {
    dest->children[dest->childrenIdx++] = src;
    dest->children = realloc(dest->children, sizeof(struct AstNode) * (dest->childrenIdx + 1));
}


void ast_destroy(ast_t ast) {
    for (int i = 0; i < ast.idx + 1; ++i) {
        if (ast.nodes[i].children) {
            free(ast.nodes[i].children);
        }
    }

    free(ast.nodes);
}
