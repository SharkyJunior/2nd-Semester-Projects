#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "appcontext.h"

char* allocStr(size_t size);
void intToStr(char* str, int value);
char* trimZeros(char *str, ErrorCode* err);
char* padWithZeros(const char *input, ErrorCode* err);
int isOnlyDigits(const char *str);
int fitsInInt(long int num);
int isValidBinary(const char *str);
int isValidOctal(const char *str);
void checkInput(AppContext* context);
int isValidDec(const char *str);

#endif // UTILITIES_H
