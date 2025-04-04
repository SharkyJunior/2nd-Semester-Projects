#ifndef APPCONTEXT_H
#define APPCONTEXT_H

#include "consts.h"
#include "rownode.h"
#include <stdio.h>

enum ErrorCode {
    OK,
    BAD_FILENAME,
    FILE_NOT_OPENED,
    INVALID_INPUT,
    CALC_ERROR,
    EMPTY_FILE,
    NO_COLUMNS,
    BAD_COLUMN
};

enum FieldType {
    String,
    Int,
    Double
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
    int selectedColumn, filteredRowsCount;
    char filterName[NAME_MAX_LEN] = "";
    char filePath[MAX_PATH_LEN] = "";
    ErrorCode errorCode;
    Metrics* metrics;
    CSVData* data;
};

#endif // APPCONTEXT_H
