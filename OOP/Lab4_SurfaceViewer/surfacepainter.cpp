#include "surfacepainter.h"

#include <QMatrix4x4>
#include <QVector4D>
#include <QGraphicsView>

QPointF project3Dto2D(double x, double y, double z, Camera* camera);
QPointF project3Dto2DnoMove(double x, double y, double z, Camera* camera);

void computeProjectionPoints(SurfaceData* surface,
    CSVData* csv, Camera* camera, ErrorCode* err)
{
    QVector< QVector<QPointF> > points;

    if (!csv->normData)
        *err = INVALID_DATA;
    else {
        points = QVector< QVector<QPointF> >();

        double centerIndexX = (double) (csv->columns) / 2;
        double centerIndexY = (double) (csv->rows) / 2;

        for (int i = 0; i < csv->rows; i++) {
            points.append(QVector<QPointF>());
            for (int j = 0; j < csv->columns; j++) {
                double x = (i + 0.5 - centerIndexX) * surface->step;
                double y = (j + 0.5 - centerIndexY) * surface->step;
                double z = csv->normData[i][j];

                points[i].append(project3Dto2D(x, y, z, camera));
            }
        }

        surface->points = points;
    }
}

QGraphicsScene* paintSurface(SurfaceData* surface, Camera* camera) {
    QGraphicsScene* scene = new QGraphicsScene();

    QPen pen = QPen(Qt::white, 2);

    int rows = surface->points.size();
    int cols = surface->points[0].size();

    for (int i = 0; i < rows - 1; i++) {
        for(int j = 0; j < cols - 1; j++) {
            scene->addLine(surface->points[i][j].x(),
                           surface->points[i][j].y(),
                           surface->points[i][j+1].x(),
                           surface->points[i][j+1].y(), pen);
            scene->addLine(surface->points[i][j].x(),
                           surface->points[i][j].y(),
                           surface->points[i+1][j].x(),
                           surface->points[i+1][j].y(), pen);
        }
        scene->addLine(surface->points[i][cols-1].x(),
                       surface->points[i][cols-1].y(),
                       surface->points[i+1][cols-1].x(),
                       surface->points[i+1][cols-1].y(), pen);
    }
    for (int i = 0; i < rows - 1; i++) {
        scene->addLine(surface->points[rows-1][i].x(),
                       surface->points[rows-1][i].y(),
                       surface->points[rows-1][i+1].x(),
                       surface->points[rows-1][i+1].y(), pen);
    }

    scene->addLine(QLineF(project3Dto2DnoMove(0, 0, 0, camera),
                          project3Dto2DnoMove(10, 0, 0, camera)),
                   QPen(Qt::red, 2));

    scene->addLine(QLineF(project3Dto2DnoMove(0, 0, 0, camera),
                          project3Dto2DnoMove(0, 10, 0, camera)),
                   QPen(Qt::green, 2));

    scene->addLine(QLineF(project3Dto2DnoMove(0, 0, 0, camera),
                          project3Dto2DnoMove(0, 0, 10, camera)),
                   QPen(Qt::blue, 2));

    return scene;
}

QPointF project3Dto2D(double x, double y, double z, Camera* camera) {

    double xRad = camera->angleX * M_PI / PI_RADIAN;
    double yRad = camera->angleY * M_PI / PI_RADIAN;
    double zRad = camera->angleZ * M_PI / PI_RADIAN;

    QMatrix4x4 rotX = QMatrix4x4(
        1, 0, 0, 0,
        0, cos(xRad), -sin(xRad), 0,
        0, sin(xRad), cos(xRad), 0,
        0, 0, 0, 1
        );

    QMatrix4x4 rotY = QMatrix4x4(
        cos(yRad), 0, sin(yRad), 0,
        0, 1, 0, 0,
        -sin(yRad), 0, cos(yRad), 0,
        0, 0, 0, 1
        );

    QMatrix4x4 rotZ = QMatrix4x4(
        cos(zRad), -sin(zRad), 0, 0,
        sin(zRad), cos(zRad), 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
        );

    QVector4D vector = QVector4D(x + camera->posX,
                                 y + camera->posY,
                                 z + camera->posZ,
                                 1.0);

    vector = vector * rotX;
    vector = vector * rotY;
    vector = vector * rotZ;

    int px = camera->windowW / 2 + vector.x() * camera->scale * SCALE_MULTIPLIER;
    int py = camera->windowH / 2 - vector.y() * camera->scale * SCALE_MULTIPLIER;

    return QPoint(px, py);

}

QPointF project3Dto2DnoMove(double x, double y, double z, Camera* camera) {

    double xRad = camera->angleX * M_PI / PI_RADIAN;
    double yRad = camera->angleY * M_PI / PI_RADIAN;
    double zRad = camera->angleZ * M_PI / PI_RADIAN;

    QMatrix4x4 rotX = QMatrix4x4(
        1, 0, 0, 0,
        0, cos(xRad), -sin(xRad), 0,
        0, sin(xRad), cos(xRad), 0,
        0, 0, 0, 1
        );

    QMatrix4x4 rotY = QMatrix4x4(
        cos(yRad), 0, sin(yRad), 0,
        0, 1, 0, 0,
        -sin(yRad), 0, cos(yRad), 0,
        0, 0, 0, 1
        );

    QMatrix4x4 rotZ = QMatrix4x4(
        cos(zRad), -sin(zRad), 0, 0,
        sin(zRad), cos(zRad), 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
        );

    QVector4D vector = QVector4D(x, y, z, 1.0);

    vector = vector * rotX;
    vector = vector * rotY;
    vector = vector * rotZ;

    int px = camera->windowW / 2 + vector.x() * camera->scale * SCALE_MULTIPLIER;
    int py = camera->windowH / 2 - vector.y() * camera->scale * SCALE_MULTIPLIER;

    return QPoint(px, py);

}
