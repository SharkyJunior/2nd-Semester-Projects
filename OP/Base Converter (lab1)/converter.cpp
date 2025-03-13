#include "appcontext.h"
#include "converter.h"
#include "utilities.h"
#include "constants.h"


const int numBits = sizeof(int) * BYTE;

char* intToBinaryString(int num, ErrorCode* err) {
    char* binaryStr = allocStr(numBits + 1);

    if (binaryStr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        *err = MEM_ALLOC_ERR;
    }
    else {
        for (int i = 0; i < numBits; i++) {
            int bit = (num >> (numBits - 1 - i)) & 1;
            binaryStr[i] = bit ? '1' : '0';
        }

        binaryStr[numBits] = '\0';
    }
    return binaryStr;
}

long int binaryStringToInt(const char *binaryStr, ErrorCode* err) {
    if (strlen(binaryStr) != STR_LEN) {
        fprintf(stderr, "Error: Input string must be exactly 32 bits.\n");
        *err = NOT_32_BITS;
    }

    unsigned int result = 0;

    for (int i = 0; i < STR_LEN; i++) {
        result = (result << 1) | (binaryStr[i] == '1' ? 1 : 0);
    }

    return (long int)result;
}


char* binaryStringToOctString(const char* binaryStr, ErrorCode* err) {
    char* offsetBinStr = offsetBinaryStrToOct(binaryStr);
    int offsetStrLen = strlen(offsetBinStr);
    int numBits = sizeof(int) * BYTE;
    char* octalStr = allocStr(numBits + 1);

    if (offsetBinStr == NULL || octalStr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        *err = MEM_ALLOC_ERR;
        free(octalStr);
    }
    else {
        for (int i = 0; i < offsetStrLen / OCT_DIGIT_LEN; i++)
            octalStr[i] = binaryDigitToOct(offsetBinStr + i * OCT_DIGIT_LEN) + '0';
    }

    free(offsetBinStr);

    return octalStr;
}

char* octStringToBinaryString(char* octString, ErrorCode* err) {
    int len = strlen(octString);
    char* offsetStr = NULL;
    char* octDigit;
    offsetStr = (char *) malloc((STR_LEN + 1) * sizeof(char));

    if (len > OCT_MAX_LEN && (octString[0] - '0') > OCT_DIGIT_LEN)
        *err = INTEGER_OVERFLOW;
    else {
        char* binaryStr = allocStr(STR_LEN + 1);

        octDigit = octDigitToBinary((int) octString[0] - '0');
        binaryStr[0] = octDigit[1];
        binaryStr[1] = octDigit[2];
        for (int i = 1; i < len; i++) {
            octDigit = octDigitToBinary((int) octString[i] - '0');
            for (int j = 0; j < OCT_DIGIT_LEN; j++)
                binaryStr[i * OCT_DIGIT_LEN + j - 1] = octDigit[j];
        }
        free(octDigit);

        int offset = STR_LEN - strlen(binaryStr);
        for (int i = 0; i < offset; i++)
            offsetStr[i] = '0';
        if (offset >= 0)
            strncat(offsetStr, binaryStr, strlen(offsetStr) + strlen(binaryStr) + 1);
        offsetStr[STR_LEN] = '\0';

        free(binaryStr);
    }

    return offsetStr;
}

int binaryDigitToOct(const char* str) {
    return ((int) str[0] - '0') * 4 + ((int) str[1] - '0') * 2 + ((int) str[2] - '0');
}

char* octDigitToBinary(int digit) {
    char* binDigit = allocStr(OCT_DIGIT_LEN + 1);
    if (binDigit != NULL)
        for (int i = 0; i < OCT_DIGIT_LEN; i++) {
            binDigit[OCT_DIGIT_LEN - i - 1] = digit % 2 + '0';
            digit /= 2;
        }

    return binDigit;
}

char* offsetBinaryStrToOct(const char* binaryStr) {
    int sumLen = 0;
    int len = strlen(binaryStr);
    int offset = OCT - (len % OCT_DIGIT_LEN) + 1;
    char* offsetStr = allocStr(offset + 1);
    if (offsetStr != NULL) {
        for (int i = 0; i < offset; i++)
            offsetStr[i] = '0';

        offsetStr = (char *) realloc(offsetStr, len + offset + 1);

        sumLen = strlen(offsetStr) + strlen(binaryStr) + 1;

        return strncat(offsetStr, binaryStr, sumLen);
    }
    else return NULL;
}
