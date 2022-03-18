#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <stdint.h>
#include <stdio.h>

void raise(const char* error_type, uint64_t line);


#endif
