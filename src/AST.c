#include <include/AST.h>


void ast_destroy(ast_t ast) {
    free(ast.nodes);
}
