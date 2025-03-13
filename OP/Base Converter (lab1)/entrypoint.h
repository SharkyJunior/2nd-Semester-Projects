#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include <stdlib.h>
#include "appcontext.h"

enum Operation {
    Initialization,
    Convert,
    CheckInput,
    UpdateBases,
    Swap
};

struct AppParams {
    SelectedBase newFromBase, newToBase;
    char input[33];
    char output[33];
};

void doOperation(Operation operation, AppContext* context, AppParams* params);
void doConvert(AppContext* context);
void doInitialization(AppContext* context);
void updateBases(AppContext* context, SelectedBase newFrom, SelectedBase newTo);
void doSwap(AppContext* context);
void convertSwitch(AppContext* context, char* input);

#endif // ENTRYPOINT_H
