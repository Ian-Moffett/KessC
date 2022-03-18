#ifndef CODEGEN_H
#define CODEGEN_H

#include <include/AST.h>
#include <stdint.h>
#include <stdio.h>


/*
 *  This file will read the AST
 *  and generate code based on
 *  what it finds.
 */


void compile(ast_t* ast);

#endif
