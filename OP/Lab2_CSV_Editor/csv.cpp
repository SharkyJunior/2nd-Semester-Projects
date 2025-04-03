#include "csv.h"

#include "consts.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count(const char* str, char c);
void parseData(CSVData* data, FILE* file);

CSVData* readCsv(const char* filename, ErrorCode* err) {
    FILE* file = fopen(filename, "r");
    CSVData* data = NULL;

    if (file == NULL)
        *err = FILE_NOT_OPENED;
    else {
        data  = (CSVData*) malloc(sizeof(CSVData));
        char buff[MAX_CSVLINE_LENGTH];

        // read field names

        fgets(buff, MAX_CSVLINE_LENGTH, file);
        buff[strcspn(buff, "\n")] = '\0';

        data->columnCount = count(buff, ',') + 1;
        if (data->columnCount == 1 && strlen(buff) < 1) {
            *err = NO_COLUMNS;
        }
        else {
            data->columnNames = (char**) malloc(data->columnCount * sizeof(char*));

            int i = 0;
            char* token = strtok(buff, ",");
            while (token != NULL) {
                token[strlen(token)] = '\0';
                data->columnNames[i++] = token;
                token = strtok(NULL, ",");
            }

            // read data
            //data->data = (char***) malloc(DEFAULT_ROW_NUM * sizeof(char**));

            parseData(data, file);
        }
    }

    fclose(file);

    return data;
}

void parseData(CSVData* data, FILE* file) {
    char buff[MAX_CSVLINE_LENGTH];
    int rows = 0, errCnt = 0, dataAllocLen = DEFAULT_ROW_NUM;
    while (fgets(buff, sizeof(buff), file)) {
        buff[strcspn(buff, "\n")] = '\0';

        if (count(buff, ',') + 1 != data->columnCount)
            errCnt++;
        else {
            if (rows >= dataAllocLen) {
                data->data = (char***) realloc(data->data, dataAllocLen * 2 * sizeof(char**));
                dataAllocLen *= 2;
            }
            data->data[rows] = (char**) malloc(data->columnCount * sizeof(char*));
            for (int i = 0; i < data->columnCount; i++) {
                char* token = strtok(buff, ",");
                int tokLen = strlen(token);
                if (tokLen == 0) {
                    free(data->data[rows]);
                    errCnt++;
                    break;
                }
                data->data[rows][i] = (char*) malloc((tokLen + 1) * sizeof(char));
                strncpy(data->data[rows][i], token, tokLen + 1);
                data->data[rows][i][tokLen] = '\0';
            }
            if (data->data[rows] != NULL)
                rows++;
        }
    }

    data->rowCount = rows;
    data->errEntryCount = errCnt;
}


int count(const char* s, char c) {
    int i;
    for (i = 0; s[i]; s++)
        if (s[i] == c)
            i++;
    return i;
}
