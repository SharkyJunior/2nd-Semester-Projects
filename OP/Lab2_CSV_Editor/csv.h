#ifndef CSV_H
#define CSV_H

#include "consts.h"
#include "appcontext.h"

Region* readCsv(FILE* filestream);
Region* filterCsv(FILE* filestream, char* filterName);
double calcMinValue(Region* data, int column);
double calcMaxValue(Region* data, int column);
double calcMedianValue(Region* data, int column);


#endif // CSV_H
