#ifndef CONVERTER_H
#define CONVERTER_H

#include <QString>
#include "appcontext.h"

char* intToBinaryString(int num, ErrorCode* err);
long int binaryStringToInt(const char *binaryStr, ErrorCode* err);
char* binaryStringToOctString(const char* binaryStr, ErrorCode* err);
char* octStringToBinaryString(char* octString, ErrorCode* err);
int binaryDigitToOct(const char* str);
char* offsetBinaryStrToOct(const char* binaryStr);
char* octDigitToBinary(int digit);

#endif // CONVERTER_H
