#ifndef APPCONTEXT_H
#define APPCONTEXT_H

#include <QPointF>
#include <QVector>

#include "consts.h"

enum ErrorCode {
    OK,
    FILE_NOT_OPENED,
    EMPTY_FILE,
    INVALID_DATA,
    INVALID_NORM_VALS,
};

struct CSVData {
    double** data;
    double** normData;
    int rows = 0, columns = 0;
};

struct Camera {
    double posX = 0, posY = 0, posZ = 0, angleX = 30, angleY = 30, angleZ = 30;
    double scale = 1;
    int windowH, windowW;
};

struct SurfaceData {
    QVector< QVector<QPointF> > points;
    double minNorm = -20, maxNorm = 20, step = 5;
};

struct AppContext {
    char filePath[MAX_PATH_LEN] = "";
    ErrorCode err;
    CSVData csv;
    Camera camera;
    SurfaceData surfaceData;
};

#endif // APPCONTEXT_H
