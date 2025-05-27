#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include "consts.h"
#include "appcontext.h"

enum Operations {
    LoadSurface,
    UpdateSurface
};

struct AppParams {
    char filePath[MAX_PATH_LEN];
    double posX, posY, posZ, angleX, angleY, angleZ, scale;
    double minNorm, maxNorm, step;
    int isGesture = 0;
};

void doOperation(Operations operation, AppContext* context, AppParams* params);

#endif // ENTRYPOINT_H
