#ifndef APPCONTEXT_H
#define APPCONTEXT_H

#include "consts.h"
#include <stdio.h>

struct Region {
    int year;
    char name[NAME_MAX_LEN];
    double npg, birthRate, deathRate, gdw, urbanization;
};

struct AppContext {
    FILE* file;
    int selectedColumn;
    double minValue, maxValue, medianValue;
    char* filePath;
    char filterName[NAME_MAX_LEN];
    Region* regions;
};

#endif // APPCONTEXT_H
