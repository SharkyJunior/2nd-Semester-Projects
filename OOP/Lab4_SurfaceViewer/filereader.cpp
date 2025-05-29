#include "filereader.h"

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

    if (columns == 0 || rows == 0)
        throw BadFileException("No rows or columns.");

    vector< vector<double> > data = vector< vector<double> >();

    double dataMin, dataMax;
    while (fgets(buff, MAX_CSVLINE_LENGTH, file)) {
        buff[strcspn(buff, "\r\n")] = '\0';
        vector<double> row = vector<double>();
        char* endptr = NULL;

        char* token = strtok(buff, ",");

        double value = strtod(token, &endptr);
        if (token == endptr) {
            throw BadFileException("Invalid value / not a number.");
            break;
        }
        dataMin = value;
        dataMax = value;

        while (token != NULL) {
            double value = strtod(token, &endptr);
            if (token == endptr) {
                throw BadFileException("Invalid value / not a number.");
                break;
            }

            if (value > dataMax)
                dataMax = value;
            if (value < dataMin)
                dataMin = value;

            row.push_back(value);

            token = strtok(NULL, ",");
        }

        data.push_back(row);
    }


    // normalizing values, creating vertices and edges between them -> figure

    double normMin = normParams.min();
    double normMax = normParams.max();
    double dxStep = normParams.dxStep();
    double dyStep = normParams.dyStep();

    double centerIndexX = columns / 2;
    double centerIndexY = rows / 2;

    Figure figure = Figure();

    Vertex prevVertex, curVertex;

    double x = (0.5 - centerIndexX) * dxStep;
    double y = (0.5 - centerIndexY) * dyStep;
    double z = normMin + (data[0][0] - dataMin) * (normMax - normMin) / (dataMax - dataMin);

    curVertex = Vertex(Point3D(x, y, z));

    for (unsigned j = 1; j < data[0].size(); j++) {
        x = (0.5 - centerIndexX) * dxStep;
        y = (j + 0.5 - centerIndexY) * dyStep;
        z = normMin + (data[0][j] - dataMin) * (normMax - normMin) / (dataMax - dataMin);

        prevVertex = curVertex;
        curVertex = Vertex(Point3D(x, y, z));

        figure.addVertex(curVertex);
        figure.addEdge(Edge(prevVertex, curVertex));
    }

    for (unsigned i = 1; i < data.size(); i++) {
        x = (i + 0.5 - centerIndexX) * dxStep;
        y = (0.5 - centerIndexY) * dyStep;
        z = normMin + (data[i][0] - dataMin) * (normMax - normMin) / (dataMax - dataMin);

        curVertex = Vertex(Point3D(x, y, z));
        figure.addEdge(Edge(figure.getVertices()[(i-1)*columns], curVertex));

        for (unsigned j = 1; j < data[0].size(); j++) {
            x = (i + 0.5 - centerIndexX) * dxStep;
            y = (j + 0.5 - centerIndexY) * dyStep;
            z = normMin + (data[i][j] - dataMin) * (normMax - normMin) / (dataMax - dataMin);

            prevVertex = curVertex;
            curVertex = Vertex(Point3D(x, y, z));

            figure.addVertex(curVertex);
            figure.addEdge(Edge(prevVertex, curVertex));
            figure.addEdge(Edge(figure.getVertices()[(i-1)*columns + j], curVertex));
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
