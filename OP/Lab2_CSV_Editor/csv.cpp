#include "csv.h"

#include "consts.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count(const char* str, char c);

CSVData* readCsv(const char* filename, ErrorCode* err) {
    FILE* file = fopen(filename, "r");
    CSVData* data = (CSVData*) malloc(sizeof(CSVData));

    if (file == NULL)
        *err = FILE_NOT_OPENED;
    else {
        char buffer[MAX_CSVLINE_LENGTH];

        // read field names

        fgets(buffer, MAX_CSVLINE_LENGTH, file);
        buffer[strcspn(buffer, "\n")] = '\0';

        int fieldCount = count(buffer, ',') + 1;

        data->columnNames = (char**) malloc(fieldCount * sizeof(char*));

        int i = 0;
        char* token = strtok(buffer, ",");
        while (token != NULL) {
            token[strlen(token)] = '\0';
            data->columnNames[i++] = token;
            token = strtok(NULL, ",");
        }

        // set field types

        fgets(buffer, MAX_CSVLINE_LENGTH, file);
        buffer[strcspn(buffer, "\n")] = '\0';

        data->columnTypes = (FieldType*) malloc(fieldCount * sizeof(FieldType));

        for (int i = 0; i < fieldCount; i++) {
            token = strtok(buffer, ",");
            if (token == NULL) {
                *err = INVALID_INPUT;
                break;
            }

            char* end;
            long n = strtol(token, &end, 10);
            if (!(token == end && n == 0))
                data->columnTypes[i] = Int;

        }



        char line[MAX_CSVLINE_LENGTH];
        // Read the file line by line.
        while (fgets(line, sizeof(line), file)) {
            // Remove potential newline characters.
            line[strcspn(line, "\r\n")] = '\0';

            // Tokenize the line using comma as the delimiter.
            char *token = strtok(line, ",");
            while (token != NULL) {
                // Process each token (field) as needed.
                printf("%s ", token);
                token = strtok(NULL, ",");
            }
            printf("\n");  // Newline after each CSV row.
        }
    }

    fclose(file);


    return data;
}


int count(const char* s, char c) {
    int i;
    for (i = 0; s[i]; s++)
        if (s[i] == c)
            i++;
    return i;
}
