#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stddef.h>
#include <include/Lexer.h>
#include <include/Parser.h>
#include <include/AST.h>
#include <include/CodeGen.h>


// TODO: Allow multiple files to be compiled.
char* target_file = NULL;


int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: kessc <file>\n");
        return 1;
    }

    for (int i = 1; i < argc; ++i) {
        // Check if argument is not a flag (-flag).
        if (argv[i][0] != '-') {
            // Assume it is a file if so.
            if (access(argv[i], F_OK) != 0) {
                printf("KessC: Cannot access file.\n");
                return 1;
            }

            // If the file was found, set the target file and break.
            target_file = argv[i];
            break;
        }
    }

    // Grab the file size.
    FILE* fp = fopen(target_file, "r");
    fseek(fp, 0, SEEK_END);
    size_t fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    // Allocate memory on heap since heap is bigger then stack.
    char* buffer = calloc(fsize + 1, sizeof(char));
    fread(buffer, sizeof(char), fsize, fp);

    /*
     *  First we will need to create an instance
     *  of the lexer struct. Then we need to set
     *  it up with lexer_init.
     */

    // Struct instances.
    lexer_t lexer;
    parser_t parser;

    lexer_init(&lexer, buffer);
    tokenlist_init(&lexer.tokenlist);

    tokenize(&lexer);

    parser_init(&parser, lexer.tokenlist);
    parse(&parser);

    compile(&parser.ast);

    // Destroy tokenlist.
    tokenlist_destroy(&lexer.tokenlist);
    ast_destroy(parser.ast);

    // Free buffer.
    free(buffer);

    // Close file.
    fclose(fp);
}
