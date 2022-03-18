#include <include/Debugger.h>


void raise(const char* error_msg, uint64_t line) {
    printf("\033[0;31m%s\n", error_msg);
    printf("Line: %d\n", line);
}
