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

struct RowNode {
    RowNode* next;
    char** data;
};

struct CSVData {
    char** columnNames;
    RowNode* head;
    int columnCount, rowCount, errEntryCount;
};

struct Metrics {
    double minValue, maxValue, medianValue;
};

struct AppContext {
    int selectedColumn;
    char filePath[MAX_PATH_LEN];
    char columnFilterName[NAME_MAX_LEN];
    char filterValue[NAME_MAX_LEN];
    ErrorCode errorCode;
    Metrics* metrics;
    FILE* file;
    CSVData* data;
};

#endif // APPCONTEXT_H
