#include "utilities.h"
#include "appcontext.h"
#include "constants.h"

#include <string.h>

char* allocStr(size_t size) {
    char* str = (char*) calloc(size, sizeof(char));
    str[size-1] = '\0';
    return str;
}

void intToStr(char* str, int value) {
    int len = (int) ((ceil(log10(abs(value))) + 1) * sizeof(char));
    if (value < 0)
        len++;
    snprintf(str, len + 1, "%d", value);
}

char* trimZeros(char *str, ErrorCode* err) {
    if (str == NULL) {
        *err = NULL_STR;
    }
    else
        while (*str == '0' && *(str + 1) != '\0') {
            str++;
        }

    return str;
}

char* padWithZeros(const char *input, ErrorCode* err) {
    char *result;
    size_t len = strlen(input);
    if (len >= STR_LEN) {
        result = (char *) malloc(len + 1);
        if (result == NULL)
            *err = MEM_ALLOC_ERR;
        else
            strncpy(result, input, len + 1);
    }
    else {
        size_t numZeros = STR_LEN - len;
        result = (char *) malloc(STR_LEN + 1);
        if (result == NULL)
            *err = MEM_ALLOC_ERR;
        else {
            memset(result, '0', numZeros);
            strncpy(result + numZeros, input, len + 1);
            result[STR_LEN] = '\0';
        }
    }

    return result;
}

void checkInput(AppContext* context) {
    char* input = context->input;
    if (context->fromBase != DEC && !isOnlyDigits(input) ||
        (context->fromBase == BIN && !isValidBinary(input)) ||
        (context->fromBase == OCT && !isValidOctal(input)) ||
        (context->fromBase == DEC && !isValidDec(input)))

        context-> errorCode = INVALID_INPUT;
}

int isValidDec(const char *str) {
    int flag = 1;
    if (str == NULL) {
        flag = 0;
    }
    else
        while (*str != '\0') {
            if (!(*str >= '0' && *str <= '9') && *str != '-') {
                flag = 0;
                break;
            }
            str++;
        }

    return flag;
}

int isOnlyDigits(const char *str) {
    int flag = 1;
    if (str == NULL) {
        flag = 0;
    }
    else
        while (*str != '\0') {
            if (!(*str >= '0' && *str <= '9')) {
                flag = 0;
                break;
            }
            str++;
        }

    return flag;
}

int isValidBinary(const char *str) {
    int flag = 1;
    if (str == NULL || strlen(str) > 32) {
        flag = 0;
    }
    else
        while (*str != '\0') {
            if (!(*str >= '0' && *str <= '1')) {
                flag = 0;
                break;
            }
            str++;
        }

    return flag;
}

int isValidOctal(const char *str) {
    int flag = 1;
    if (str == NULL || strlen(str) > 11) {
        flag = 0;
    }
    else
        while (*str != '\0') {
            if (!(*str >= '0' && *str <= '7')) {
                flag = 0;
                break;
            }
            str++;
        }

    return flag;
}

int fitsInInt(long int num) {
    return num >= INT_MIN && num <= INT_MAX;
}
