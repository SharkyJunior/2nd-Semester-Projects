#include "csv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <QDebug>

#include "consts.h"

int charCount(const char* s, char c);
int lineCount(const char* filename);
int rowCount(const char* filename);

// works
void readCsv(const char* filename, CSVData* csvData, ErrorCode* err) {
    FILE* file = fopen(filename, "r");

    if (!file) {
        *err = FILE_NOT_OPENED;
        qDebug() << "file not opened";
    }
    else {
        char buff[MAX_CSVLINE_LENGTH];
        size_t rows = lineCount(filename);
        size_t columns = rowCount(filename);

        if (columns == 0 || rows == 0)
            *err = INVALID_DATA;
        else {
            double** data = (double**) malloc(sizeof(double*) * rows);
            double** normData = (double**) malloc(sizeof(double*) * rows);
            int curRow = 0;
            while (fgets(buff, MAX_CSVLINE_LENGTH, file)) {
                buff[strcspn(buff, "\r\n")] = '\0';
                double* row = (double*) malloc(sizeof(double) * columns);
                double* normRow = (double*) malloc(sizeof(double) * columns);
                char* endptr = NULL;

                int i = 0;
                char* token = strtok(buff, ",");
                while (token != NULL) {
                    row[i++] = strtod(token, &endptr);
                    if (token == endptr) {
                        *err = INVALID_DATA;
                        break;
                    }
                    token = strtok(NULL, ",");
                }
                if (*err != OK) {
                    free(row);
                    free(normRow);
                    break;
                }
                data[curRow] = row;
                normData[curRow++] = normRow;
            }
            if (*err != OK) {
                for (size_t i = 0; i < rows; i++) {
                    free(data[i]);
                    free(normData[i]);
                }
                free(data);
                free(normData);
            }
            else {
                csvData->data = data;
                csvData->normData = normData;
                csvData->rows = rows;
                csvData->columns = columns;
            }
        }
    }
}

void normalizeData(CSVData* csv, double min, double max, ErrorCode* err) {
    if (!csv)
        *err = INVALID_DATA;
    else if (min >= max)
        *err = INVALID_NORM_VALS;
    else {
        double minVal = csv->data[0][0];
        double maxVal = csv->data[0][0];
        for (int i = 0; i < csv->rows; i++) {
            for (int j = 0; j < csv->columns; j++) {
                double val = csv->data[i][j];
                if (val < minVal)
                    minVal = val;
                if (val > maxVal)
                    maxVal = val;
            }
        }

        for (int i = 0; i < csv->rows; i++)
            for (int j = 0; j < csv->columns; j++)
                csv->normData[i][j] = min + (csv->data[i][j] - minVal) * (max - min) / (maxVal - minVal);
    }
}

int charCount(const char* s, char c) {
    int i;
    for (i = 0; s[i]; s++)
        if (s[i] == c)
            i++;
    return i;
}

int lineCount(const char* filename) {
    FILE* file = fopen(filename, "r");
    int count = 0;

    for (char c = getc(file); c != EOF; c = getc(file))
        if (c == '\n')
            count += 1;

    fclose(file);

    return count;
}

int rowCount(const char* filename) {
    FILE* file = fopen(filename, "r");
    char buff[MAX_CSVLINE_LENGTH];

    fgets(buff, MAX_CSVLINE_LENGTH, file);
    buff[strcspn(buff, "\r\n")] = '\0';
    int count = charCount(buff, ',') + 1;

    fclose(file);

    return count;
}
