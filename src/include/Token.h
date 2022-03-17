#ifndef TOKEN_H
#define TOKEN_H

#include <stdint.h>


typedef enum {
    T_PRINT,
    T_STR,
    T_DEC,
} tokentype_t;


typedef struct {
    tokentype_t type;

    union value {
        char token;
        int64_t dec;
    };
} token_t;



#endif
