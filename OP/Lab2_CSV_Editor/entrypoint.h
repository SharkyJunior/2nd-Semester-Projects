#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include "consts.h"
#include "appcontext.h"

enum Operations {
    Initialization,
    SetPath,
    LoadCSV,
    CalculateMetrics
};

struct AppParams {
    int selectedColumn;
    char* filePath;
    char filterName[NAME_MAX_LEN];
};

void doOperation(Operations operation, AppContext* context, AppParams* params);

#endif // ENTRYPOINT_H
