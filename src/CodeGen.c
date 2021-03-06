#include <include/CodeGen.h>


void compile(ast_t* ast) {
    /*
     *  To update: you must check the
     *  token typelabel and match it 
     *  with a type label in the parser.
     *  Then do something based on the
     *  child nodes!
     */

    elf_section_t currentSection = S_TEXT;
    uint64_t curLabel = 1;

    // Check if tmp file already exists. 
    if (access("/tmp/KessC.out.s", F_OK) == 0) {
        remove("/tmp/KessC.out.s");
    }

    FILE* fp = fopen("/tmp/KessC.out.s", "w");

    fprintf(fp, "; This assembly file was generated by\n"
                "; the KessC compiler which was created by\n"
                "; Ian Marco Moffett\n\n");

    fprintf(fp, "section .text\n");
    fprintf(fp, "global _start\n");
    fprintf(fp, "_start: jmp _1\n");

    for (uint64_t i = 0; i < ast->idx; ++i) {
        ast_node_t curNode = ast->nodes[i];

        if (strcmp(curNode.type, "STDOUT_WRITE") == 0) {
            if (currentSection != S_TEXT) {
                currentSection = S_TEXT;
                fprintf(fp, "\n\nsection .text\n");
            }
            

            fprintf(fp, "_%d: jmp _%d\n\n", curLabel, curLabel + 2);
            ++curLabel;

            fprintf(fp, "section .rodata\n");

            fprintf(fp, "_%d: db \"%s\", 0xA\n\n", curLabel++, curNode.value.str);

            currentSection = S_TEXT;
            fprintf(fp, "section .text\n");

            fprintf(fp, "_%d:\n", curLabel++);      
            fprintf(fp, "    mov eax, 4\n");                                    // SYS_WRITE.
            fprintf(fp, "    mov ebx, 1\n");                                    // STDOUT.
            fprintf(fp, "    mov ecx, _%d\n", curLabel - 2);                    // STR.
            fprintf(fp, "    mov edx, %d\n", strlen(curNode.value.str) + 1);    // LENGTH.
            fprintf(fp, "    int 0x80\n\n");                                      // LINUX SYSCALL.
        }
    }

    fprintf(fp, "_%d:\n", curLabel++);
    fprintf(fp, "   mov eax, 1\n");
    fprintf(fp, "   mov ebx, 0\n");
    fprintf(fp, "   int 0x80\n");

    fclose(fp);
    system("nasm -felf32 /tmp/KessC.out.s -o /tmp/KessC.out.o");
    remove("/tmp/KessC.out.s");
    system("ld -melf_i386 /tmp/KessC.out.o -o a.out");
    remove("/tmp/KessC.out.o");
}
