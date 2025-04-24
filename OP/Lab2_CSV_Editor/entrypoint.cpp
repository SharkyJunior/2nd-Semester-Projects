#include "entrypoint.h"

#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "consts.h"
#include "csv.h"
#include "appcontext.h"


void doInit(AppContext* context);
void doReadCsv(AppContext* context);
void setPath(AppContext* context, const char* filepath);
void calculateMetrics(AppContext* context);
int cmp(const void* a, const void* b);

void doOperation(Operations operation, AppContext* context, AppParams* params) {
    context->errorCode = OK;

    switch (operation) {
    case Initialization:
        doInit(context);
        break;
    case SetPath:
        setPath(context, params->filePath);
        break;
    case LoadCSV:
        doReadCsv(context);
        break;
    case FilterCSV:
        strncpy(context->filterName, params->filterName, strlen(params->filterName) + 1);
        context->filteredRowsCount = params->filteredRowsCount;
        break;
    case CalculateMetrics:
        if (params->selectedColumn > 0 && params->selectedColumn <= context->data->columnCount) {
            context->selectedColumn = params->selectedColumn;
            calculateMetrics(context);
        }
        else
            context->errorCode = BAD_COLUMN;
        break;
    };
}

void doInit(AppContext* context) {
    context->metrics = (Metrics*) calloc(1, sizeof(Metrics));
    context->errorCode = OK;
    context->selectedColumn = 1;
    context->filteredRowsCount = 0;
}

void doReadCsv(AppContext* context) {
    if (strlen(context->filePath) == 0)
        context->errorCode = BAD_FILENAME;
    else
        context->data = readCsv(context->filePath, &context->errorCode);
}

void setPath(AppContext* context, const char* filepath) {
    strncpy(context->filePath, filepath, strlen(filepath) + 1);
}

void calculateMetrics(AppContext* context) {
    double min, max, median;
    long minYear, maxYear;
    int i = 0, tempLen = context->data->rowCount;
    RowNode* cur = context->data->head;

    if (strcmp(context->filterName, "") != 0)
        tempLen = context->filteredRowsCount;

    double* tempArr = (double*) calloc(tempLen, sizeof(double));

    min = strtod(cur->data[context->selectedColumn - 1], NULL);
    max = min;

    minYear = strtol(cur->data[YEAR_COL], NULL, 10);
    maxYear = minYear;

    while (cur != NULL) {
        if (!strcmp(context->filterName, "") || !strcmp(cur->data[REGION_COL], context->filterName)) {
            if (i == 0) {
                min = strtod(cur->data[context->selectedColumn - 1], NULL);
                max = min;
                minYear = strtol(cur->data[YEAR_COL], NULL, 10);
                maxYear = minYear;
            }
            char* endptr = NULL, *endptr2 = NULL;
            double val = strtod(cur->data[context->selectedColumn - 1], &endptr);
            long year = strtol(cur->data[YEAR_COL], &endptr2, 10);
            if (errno != 0 && (endptr == cur->data[i] || endptr2 == cur->data[YEAR_COL])) {
                context->errorCode = BAD_METRICS_VALUE;
                break;
            }
            else if (val < min)
                min = val;
            else if (val > max)
                max = val;

            if (year < minYear)
                minYear = year;
            else if (year > maxYear)
                maxYear = year;

            tempArr[i++] = val;
        }
        cur = cur->next;
    }

    if (context->errorCode == OK) {
        qsort(tempArr, i, sizeof(double), cmp);
        median = tempArr[i / 2];

        context->metrics->minValue = min;
        context->metrics->maxValue = max;
        context->metrics->medianValue = median;
        context->metrics->minYear = minYear;
        context->metrics->maxYear = maxYear;
    }

    free(tempArr);
}

int cmp(const void* a, const void* b) {
    int arg1 = *(const double*)a;
    int arg2 = *(const double*)b;

    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}
