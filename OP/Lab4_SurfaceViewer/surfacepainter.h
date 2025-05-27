#ifndef SURFACEPAINTER_H
#define SURFACEPAINTER_H

#include <QPointF>
#include <QVector>
#include <QGraphicsView>

#include "appcontext.h"

void computeProjectionPoints(SurfaceData* surface,
    CSVData* csvData, Camera* camera, ErrorCode* err);

QGraphicsScene* paintSurface(SurfaceData* surfaceData, Camera* camera);

#endif // SURFACEPAINTER_H
