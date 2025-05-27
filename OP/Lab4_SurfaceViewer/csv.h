#ifndef CSV_H
#define CSV_H

#include "appcontext.h"

void readCsv(const char* filename, CSVData* csvData, ErrorCode* err);
void normalizeData(CSVData* csv, double min, double max, ErrorCode* err);


#endif // CSV_H
