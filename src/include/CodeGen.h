#ifndef CODEGEN_H
#define CODEGEN_H

#include <include/AST.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


/*
 *  This file will read the AST
 *  and generate code based on
 *  what it finds.
 */

typedef enum {
    S_TEXT,
    S_BSS,
    S_RODATA,
    S_DATA
} elf_section_t;


void compile(ast_t* ast);

#endif
