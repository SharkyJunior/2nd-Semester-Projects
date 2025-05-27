#include "entrypoint.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <QtLogging>
#include <QDebug>

#include "appcontext.h"
#include "csv.h"
#include "surfacepainter.h"

void printCsvInfo(CSVData* data);
void updateSurface(AppContext* context);
void updateContext(AppContext* context, AppParams* params);

void doOperation(Operations operation, AppContext* context, AppParams* params) {
    context->err = OK;

    switch (operation) {
    case LoadSurface:
        strncpy(context->filePath, params->filePath, strlen(params->filePath) + 1);
        context->filePath[strlen(params->filePath)] = '\0';
        qDebug() << context->filePath;

        readCsv(context->filePath, &context->csv, &context->err);

        updateSurface(context);

        break;
    case UpdateSurface:
        if (!params->isGesture)
            updateContext(context, params);
        updateSurface(context);
        break;
    }
}

void printCsvInfo(CSVData* data) {
    qDebug() << "(" << data->rows << ", " << data->columns << ")";
    for (int i = 0; i < data->rows; i++) {
        QString temp = "";
        for (int j = 0; j < data->columns; j++)
            temp += QString::number(data->data[i][j]) + ' ';
        qDebug() << temp;
    }
}

void updateSurface(AppContext* context) {
    normalizeData(&context->csv, context->surfaceData.minNorm,
                  context->surfaceData.maxNorm, &context->err);

    computeProjectionPoints(&context->surfaceData, &context->csv,
                            &context->camera, &context->err);
}

void updateContext(AppContext* context, AppParams* params) {
    context->camera.posX = params->posX;
    context->camera.posY = params->posY;
    context->camera.posZ = params->posZ;

    context->camera.angleX = params->angleX;
    context->camera.angleY = params->angleY;
    context->camera.angleZ = params->angleZ;

    context->camera.scale = params->scale;

    context->surfaceData.minNorm = params->minNorm;
    context->surfaceData.maxNorm = params->maxNorm;
    context->surfaceData.step = params->step;
}
