#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include <stdlib.h>
#include "appcontext.h"
#include "constants.h"

enum Operation {
    Initialization,
    Convert,
    CheckInput,
    UpdateBases,
    Swap
};

struct AppParams {
    SelectedBase newFromBase, newToBase;
    char input[STR_LEN + 1];
    char output[STR_LEN + 1];
};

void doOperation(Operation operation, AppContext* context, AppParams* params);

#endif // ENTRYPOINT_H
