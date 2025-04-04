#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include "consts.h"
#include "appcontext.h"

enum Operations {
    Initialization,
    SetPath,
    LoadCSV,
    FilterCSV,
    CalculateMetrics
};

struct AppParams {
    int selectedColumn, filteredRowsCount;
    char filePath[MAX_PATH_LEN];
    char filterName[NAME_MAX_LEN];
};

void doOperation(Operations operation, AppContext* context, AppParams* params);

#endif // ENTRYPOINT_H
