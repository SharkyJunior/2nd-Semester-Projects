#include "entrypoint.h"
#include "converter.h"
#include "utilities.h"
#include "constants.h"
#include <stdlib.h>
#include <string.h>

void doConvert(AppContext* context);
void copyInputToContext(AppContext* context, AppParams* params);
void copyOutputToContext(AppContext* context, AppParams* params);
void doInitialization(AppContext* context);
void updateBases(AppContext* context, SelectedBase newFrom, SelectedBase newTo);
void doSwap(AppContext* context);
void convertSwitch(AppContext* context, char* input);

void doOperation(Operation operation, AppContext* context, AppParams* params) {
    context->errorCode = OK;

    switch(operation) {
    case Initialization:
        doInitialization(context);
        break;
    case Convert:
        copyInputToContext(context, params);
        doConvert(context);
        break;
    case CheckInput:
        break;
    case UpdateBases:
        updateBases(context, params->newFromBase, params->newToBase);
        break;
    case Swap:
        copyInputToContext(context, params);
        copyOutputToContext(context, params);
        doSwap(context);
        break;
    }
}

void doInitialization(AppContext* context) {
    context->fromBase = DEC;
    context->toBase = BIN;
    context->input[0] = '\0';
}

void copyInputToContext(AppContext* context, AppParams* params) {
    strncpy(context->input, params->input, strlen(params->input) + 1);
    context->input[strlen(params->input)] = '\0';
}

void copyOutputToContext(AppContext* context, AppParams* params) {
    strncpy(context->output, params->output, strlen(params->output) + 1);
}

void doConvert(AppContext* context) {
    char input[STR_LEN + 1];
    strncpy(input, context->input, strlen(context->input) + 1);

    SelectedBase to = context->toBase;

    checkInput(context);
    if (context->errorCode == OK)
    {
        if (to == context->fromBase || strlen(context->input) == 0) {
            char* temp = trimZeros(input, &context->errorCode);
            strncpy(input, temp, strlen(temp) + 1);
            strncpy(context->output, input, strlen(input) + 1);
        }
        else {
            if (context->fromBase == BIN)
                strncpy(input, padWithZeros(input, &context->errorCode), STR_LEN + 1);
            if (context->errorCode == OK) {
                convertSwitch(context, input);
            }
        }
    }
}

void convertSwitch(AppContext* context, char *input) {
    long int intInput;
    char* temp;
    SelectedBase to = context->toBase;

    switch (context->fromBase) {
    case DEC:
        intInput = strtol(input, NULL, DEC_BASE);
        if (!fitsInInt(intInput))
            context->errorCode = INTEGER_OVERFLOW;
        else {
            temp = intToBinaryString(intInput, &context->errorCode);
            if (context->errorCode == OK && to == OCT)
                temp = binaryStringToOctString(temp, &context->errorCode);
            if (context->errorCode == OK) {
                strncpy(context->output, temp, strlen(temp) + 1);
            }
            free(temp);
        }
        break;
    case BIN:
        if (to == DEC)
            intToStr(context->output, binaryStringToInt(input, &context->errorCode));
        else {
            temp = binaryStringToOctString(input, &context->errorCode);
            if (context->errorCode == OK) {
                strncpy(context->output, temp, strlen(temp) + 1);
            }
            free(temp);
        }
        break;
    case OCT:
        temp = octStringToBinaryString(input, &context->errorCode);
        if (context->errorCode == OK) {
            if (to == DEC)
                intToStr(context->output, binaryStringToInt(temp, &context->errorCode));
            else {
                strncpy(context->output, temp, strlen(temp) + 1);
            }
        }
        free(temp);
        break;
    }
}


void updateBases(AppContext* context, SelectedBase newFrom, SelectedBase newTo) {
    context->fromBase = newFrom;
    context->toBase = newTo;
}

void doSwap(AppContext* context) {
    SelectedBase temp = context->fromBase;
    context->fromBase = context->toBase;
    context->toBase = temp;

    char strTemp[STR_LEN + 1];
    strncpy(strTemp, context->input, STR_LEN + 1);
    strncpy(context->input, context->output, STR_LEN + 1);
    strncpy(context->output, strTemp, STR_LEN + 1);
}
