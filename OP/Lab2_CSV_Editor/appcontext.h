#ifndef APPCONTEXT_H
#define APPCONTEXT_H

#include "consts.h"
#include <stdio.h>

enum ErrorCode {
    OK,
    FILE_NOT_OPENED,
    INVALID_INPUT,
    CALC_ERROR,
    EMPTY_FILE
};

enum FieldType {
    String,
    Int,
    Double
};

struct Region {
    int year;
    char name[NAME_MAX_LEN];
    double npg, birthRate, deathRate, gdw, urbanization;
};

struct CSVData {
    char** columnNames;
    FieldType* columnTypes;
    char*** data;
};

struct AppContext {
    FILE* file;
    int selectedColumn;
    double minValue, maxValue, medianValue;
    char* filePath;
    char filterName[NAME_MAX_LEN];
    Region* regions;
};

#endif // APPCONTEXT_H
