#ifndef CSV_H
#define CSV_H

#include "appcontext.h"

CSVData* readCsv(const char* filename, ErrorCode* err);
CSVData* filterCsv(CSVData* data, char* columnName, char* filterValue);
double calcMinValue(CSVData* data, int column);
double calcMaxValue(CSVData* data, int column);
double calcMedianValue(CSVData* data, int column);


#endif // CSV_H
