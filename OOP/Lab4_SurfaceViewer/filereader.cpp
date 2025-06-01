#include "filereader.h"

#include <QDebug>

#include "consts.h"
#include "exceptions.h"

FileReader::FileReader() {}

Figure FileReader::readFigure(const string& path, const NormalizationParameters& normParams) {
    file = fopen(path.c_str(), "r");

    if (!file)
        throw FileNotOpenedException("Couldn't open file.");


    // reading file

    char buff[MAX_CSVLINE_LENGTH];
    size_t rows = lineCount();
    size_t columns = rowCount();

    rewind(file);

    if (columns == 0 || rows == 0)
        throw BadFileException("No rows or columns.");

    vector< vector<double> > data = vector< vector<double> >();

    bool valuesSet = false;
    double dataMin, dataMax;
    while (fgets(buff, MAX_CSVLINE_LENGTH, file)) {
        buff[strcspn(buff, "\r\n")] = '\0';
        vector<double>* row = new vector<double>();
        char* endptr = NULL;

        char* token = strtok(buff, ",");
        while (token != NULL) {
            double value = strtod(token, &endptr);
            if (token == endptr) {
                throw BadFileException("Invalid value / not a number.");
                break;
            }

            if (!valuesSet) {
                dataMin = value;
                dataMax = value;
                valuesSet = true;
            }

            if (value > dataMax)
                dataMax = value;
            if (value < dataMin)
                dataMin = value;

            row->push_back(value);

            token = strtok(NULL, ",");
        }

        data.push_back(*row);
    }

    for (vector<double>& v : data)
        for (double d : v)
            qDebug() << d;

    // normalizing values, creating vertices and edges between them -> figure

    double normMin = normParams.min();
    double normMax = normParams.max();
    double dxStep = normParams.dxStep();
    double dyStep = normParams.dyStep();

    double centerX = normParams.windowW() / 2;
    double centerY = normParams.windowH() / 2;

    double centerIndexX = columns / 2;
    double centerIndexY = rows / 2;

    Figure figure = Figure();

    Vertex prevVertex, curVertex;

    rows = data.size();
    unsigned cols = data[0].size();

    std::vector<Vertex> vertices;
    vertices.reserve(rows * cols);

    for (unsigned i = 0; i < rows; ++i) {
        for (unsigned j = 0; j < cols; ++j) {
            double x = centerX + (i + 0.5 - centerIndexX) * dxStep;
            double y = centerY - (j + 0.5 - centerIndexY) * dyStep;
            double z = normMin + (data[i][j] - dataMin) * (normMax - normMin) / (dataMax - dataMin);

            Vertex v(Point3D(x, y, z));
            figure.addVertex(v);
            vertices.push_back(v);

            if (j > 0) {
                figure.addEdge(Edge(vertices[i * cols + (j - 1)], v));
            }

            if (i > 0) {
                figure.addEdge(Edge(vertices[(i - 1) * cols + j], v));
            }
        }
    }

    fclose(file);

    return figure;
}

int FileReader::lineCount() {
    int count = 0;

    for (char c = getc(file); c != EOF; c = getc(file))
        if (c == '\n')
            count += 1;

    return count;
}


int FileReader::rowCount() {
    char buff[MAX_CSVLINE_LENGTH];

    fgets(buff, MAX_CSVLINE_LENGTH, file);
    buff[strcspn(buff, "\r\n")] = '\0';
    int count = charCount(buff, ',') + 1;

    return count;
}

int FileReader::charCount(const char* s, char c) {
    int i;
    for (i = 0; s[i]; s++)
        if (s[i] == c)
            i++;
    return i;
}
