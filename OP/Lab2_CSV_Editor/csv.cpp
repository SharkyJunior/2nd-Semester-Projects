#include "csv.h"

#include "consts.h"
#include "rownode.h"
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
        data->head = NULL;
        char buff[MAX_CSVLINE_LENGTH];

        // read field names

        fgets(buff, MAX_CSVLINE_LENGTH, file);
        buff[strcspn(buff, "\r\n")] = '\0';

        data->columnCount = count(buff, ',') + 1;
        if (data->columnCount == 1 && strlen(buff) < 1) {
            *err = NO_COLUMNS;
        }
        else {
            data->columnNames = (char**) malloc(data->columnCount * sizeof(char*));

            int i = 0;
            char* token = strtok(buff, ",");
            while (token != NULL) {
                data->columnNames[i++] = strdup(token);
                token = strtok(NULL, ",");
            }

            parseData(data, file);
        }
    }

    fclose(file);

    return data;
}

void parseData(CSVData* data, FILE* file) {
    char buff[MAX_CSVLINE_LENGTH];
    int rows = 0, errCnt = 0;

    RowNode* head = (RowNode*) malloc(sizeof(RowNode));
    RowNode* cur = head;
    cur->data = NULL;
    cur->next = NULL;
    while (fgets(buff, sizeof(buff), file)) {
        buff[strcspn(buff, "\r\n")] = '\0';

        if (count(buff, ',') + 1 != data->columnCount)
            errCnt++;
        else {
            char** rowData = (char**) malloc(data->columnCount * sizeof(char*));
            char* token = strtok(buff, ",");
            for (int i = 0; i < data->columnCount; i++) {
                if (token == NULL || strlen(token) == 0) {
                    for (int j = 0; j < i; j++) {
                        free(rowData[j]);
                    }
                    free(rowData);
                    errCnt++;
                    break;
                }
                rowData[i] = strdup(token);
                token = strtok(NULL, ",");
            }
            if (rowData != NULL) {
                if (head->data == NULL)
                    head->data = rowData;
                else
                    addNode(head, rowData);
                rows++;
            }
        }
    }
    if (cur->data != NULL)
        rows++;

    data->head = head;
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
