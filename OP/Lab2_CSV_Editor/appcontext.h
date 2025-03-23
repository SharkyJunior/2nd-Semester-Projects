#ifndef APPCONTEXT_H
#define APPCONTEXT_H

#include "consts.h"
#include <stdio.h>

enum ErrorCode {
    OK,
    FILE_NOT_OPENED,
    INVALID_INPUT,
    CALC_ERROR,
    EMPTY_FILE,
    NO_COLUMNS
};

enum FieldType {
    String,
    Int,
    Double
};

// struct Region {
//     int year;
//     char name[NAME_MAX_LEN];
//     double npg, birthRate, deathRate, gdw, urbanization;
// };

struct CSVData {
    char** columnNames;
    char*** data;
    int columnCount, rowCount, errEntryCount;
};

struct Metrics {
    double minValue, maxValue, medianValue;
};

struct AppContext {
    int selectedColumn;
    char* filePath;
    char filterName[NAME_MAX_LEN];
    Metrics* metrics;
    FILE* file;
    CSVData* data;
};

#endif // APPCONTEXT_H
