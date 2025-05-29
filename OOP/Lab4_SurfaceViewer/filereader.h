#ifndef FILEREADER_H
#define FILEREADER_H

#include <string>
#include "figure.h"
#include "normalizationparameters.h"

// done

using namespace std;

class BaseFileReader {
public:
    virtual Figure readFigure(const string& path, const NormalizationParameters& normParams);
};

class FileReader : public BaseFileReader
{
public:
    FileReader();
    Figure readFigure(const string& path, const NormalizationParameters& normParams) override;

private:
    FILE* file;

    int lineCount();
    int rowCount();
    int charCount(const char* s, char c);
};

#endif // FILEREADER_H
