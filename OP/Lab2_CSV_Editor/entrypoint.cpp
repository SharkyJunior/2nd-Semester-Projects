#include "entrypoint.h"

#include <string.h>
#include "csv.h"


void doInit(AppContext* context);
void setPath(AppContext* context, const char* filepath);
Metrics* calculateMetrics(const CSVData* data);

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
        context->data = readCsv(context->filePath, &context->errorCode);
        break;
    case FilterCSV:
        //context->data = filterCsv(context->data, context->columnFilterName, context->filterValue);
        break;
    case CalculateMetrics:
        //context->metrics = calculateMetrics(context->data);
        break;
    };
}

void doInit(AppContext* context) {

}

void setPath(AppContext* context, const char* filepath) {
    strncpy(context->filePath, filepath, strlen(filepath) + 1);
}
