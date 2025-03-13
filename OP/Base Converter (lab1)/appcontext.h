#ifndef APPCONTEXT_H
#define APPCONTEXT_H

#define MAX_LEN 32

enum SelectedBase {
    DEC,
    BIN,
    OCT
};

enum ErrorCode {
    OK,
    INVALID_INPUT,
    INTEGER_OVERFLOW,
    MEM_ALLOC_ERR,
    NOT_32_BITS,
    NULL_STR
};

struct AppContext {
    ErrorCode errorCode = OK;
    SelectedBase fromBase, toBase;
    char input[MAX_LEN + 1];
    char output[MAX_LEN + 1];
};

#endif // APPCONTEXT_H
