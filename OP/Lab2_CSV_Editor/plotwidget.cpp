#include "plotwidget.h"
#include "consts.h"

#include <string>
#include <math.h>

using namespace std;

PlotWidget::PlotWidget(QWidget* parent)
    : QWidget(parent)
{
    setupUi();

    yMin = MARGIN + AXLE_MARGIN;
    yMax = PLOT_WINDOW_HEIGHT - MARGIN - AXLE_MARGIN;
    xMin = PLOT_LEFT_MARGIN + AXLE_MARGIN;
    xMax = PLOT_WINDOW_WIDTH - PLOT_RIGHT_MARGIN - AXLE_MARGIN;
}

void PlotWidget::setContext(const AppContext* context) {
    this->context = context;
}

void PlotWidget::setupUi() {
    setFixedSize(PLOT_WINDOW_WIDTH, PLOT_WINDOW_HEIGHT);
    setWindowTitle("Plot");
}

void PlotWidget::paintEvent(QPaintEvent *event) {
    paintAxles();
    paintPlot();
    paintMinMaxMedian();
    paintMarks();
}

void PlotWidget::paintAxles() {
    QPainter painter = QPainter(this);

    QPen pen;
    pen.setColor(QColor(Qt::GlobalColor::white));
    painter.setPen(pen);

    painter.drawLine(PLOT_LEFT_MARGIN, MARGIN, PLOT_LEFT_MARGIN, PLOT_WINDOW_HEIGHT - MARGIN);
    painter.drawLine(PLOT_LEFT_MARGIN, PLOT_WINDOW_HEIGHT - MARGIN,
                     PLOT_WINDOW_WIDTH - PLOT_RIGHT_MARGIN, PLOT_WINDOW_HEIGHT - MARGIN);
}

void PlotWidget::paintPlot() {
    QPainter painter = QPainter(this);

    QPen pen;
    pen.setColor(QColor(Qt::GlobalColor::white));
    painter.setPen(pen);

    painter.setBrush(QColor(Qt::GlobalColor::white));

    points = getPlotPoints();

    for (int i = 0; i < context->filteredRowsCount - 1; i++) {
        painter.drawEllipse(points[i], POINT_RADIUS, POINT_RADIUS);
        painter.drawEllipse(points[i + 1], POINT_RADIUS, POINT_RADIUS);
        painter.drawLine(points[i], points[i + 1]);
    }
}

void PlotWidget::paintMinMaxMedian() {
    QPainter painter = QPainter(this);

    // lines
    QPen pen;
    pen.setColor(QColor(Qt::GlobalColor::green));
    pen.setDashPattern({1, 4});
    painter.setPen(pen);

    painter.drawLine(PLOT_LEFT_MARGIN, yMin, PLOT_WINDOW_WIDTH - PLOT_RIGHT_MARGIN, yMin);

    pen.setColor(QColor(Qt::GlobalColor::red));
    painter.setPen(pen);
    painter.drawLine(PLOT_LEFT_MARGIN, yMax, PLOT_WINDOW_WIDTH - PLOT_RIGHT_MARGIN, yMax);

    pen.setColor(QColor(Qt::GlobalColor::blue));
    painter.setPen(pen);
    painter.drawLine(PLOT_LEFT_MARGIN, medianY, PLOT_WINDOW_WIDTH - PLOT_RIGHT_MARGIN, medianY);


    // text
    pen.setColor(QColor(Qt::GlobalColor::white));
    painter.setPen(pen);

    QString tempStr = "Max = ";
    tempStr += trimZeros(context->metrics->maxValue);
    painter.drawText(PLOT_WINDOW_WIDTH - PLOT_RIGHT_MARGIN - TEXT_SHIFT_X, yMin - TEXT_SHIFT_Y, tempStr);

    tempStr = "Min = ";
    tempStr += trimZeros(context->metrics->minValue);
    painter.drawText(PLOT_WINDOW_WIDTH - PLOT_RIGHT_MARGIN - TEXT_SHIFT_X, yMax - TEXT_SHIFT_Y, tempStr);

    tempStr = "Median = ";
    tempStr += trimZeros(context->metrics->medianValue);
    painter.drawText(PLOT_WINDOW_WIDTH - PLOT_RIGHT_MARGIN - TEXT_SHIFT_X, medianY - TEXT_SHIFT_Y, tempStr);

}

void PlotWidget::paintMarks() {
    QPainter painter = QPainter(this);
    QPen pen;
    pen.setColor(QColor(Qt::GlobalColor::white));
    painter.setPen(pen);

    // x lines
    int x = xMin;
    int y = yMax + AXLE_MARGIN;
    int val = context->metrics->minYear;
    painter.drawLine(x, y, x, y + MARK_LEN);
    painter.drawText(x - MARK_TEXT_SHIFT_X, y + MARK_LEN + MARK_TEXT_SHIFT_Y, QString::number(val));
    for (int i = MARK_DENSITY_X; i < context->filteredRowsCount - 1; i += MARK_DENSITY_X) {
        x = points[i].x();
        y = yMax + AXLE_MARGIN;

        val = xVal[i];

        painter.drawLine(x, y, x, y + MARK_LEN);
        painter.drawText(x - MARK_TEXT_SHIFT_X, y + MARK_LEN + MARK_TEXT_SHIFT_Y, QString::number(val));
    }

    // y lines
    x = xMin - AXLE_MARGIN;
    double val2;
    double stepY = (yMax - yMin) / (MARK_COUNT_Y - 1);
    double stepVal = (context->metrics->maxValue - context->metrics->minValue) / (MARK_COUNT_Y - 1);
    for (int i = 0; i < MARK_COUNT_Y; i++) {
        y = yMax - i * stepY;
        val2 = context->metrics->minValue + i * stepVal;
        painter.drawLine(x, y, x - MARK_LEN, y);
        painter.drawText(x - MARK_TEXT_SHIFT_X - AXLE_MARGIN * 2, y, trimZeros(val2));
    }
}

int PlotWidget::cmp(const void* a, const void* b) {
    int arg1 = *(const double*)a;
    int arg2 = *(const double*)b;

    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}


QPoint* PlotWidget::getPlotPoints() {
    QPoint* arr = (QPoint*) calloc(context->filteredRowsCount, sizeof(QPoint));
    int* xArr = (int*) calloc(context->filteredRowsCount, sizeof(int));
    int* yArr = (int*) calloc(context->filteredRowsCount, sizeof(int));
    int* xVal = (int*) calloc(context->filteredRowsCount, sizeof(int));
    double* yVal = (double*) calloc(context->filteredRowsCount, sizeof(double));

    int i = 0;
    RowNode* cur = context->data->head;
    while (cur != NULL) {
        if (!strncmp(cur->data[REGION_COL], context->filterName, strlen(context->filterName))) {
            double val = strtod(cur->data[context->selectedColumn - 1], NULL);
            long year = strtol(cur->data[YEAR_COL], NULL, 10);

            xVal[i] = year;
            yVal[i] = val;

            int x, y;
            x = xMin + (int) (relativeVal(year, context->metrics->minYear, context->metrics->maxYear)
                              * (xMax - xMin));
            y = yMax - (int) (relativeVal(val, context->metrics->minValue, context->metrics->maxValue)
                              * (yMax - yMin));

            xArr[i] = x;
            yArr[i] = y;
            arr[i++] = QPoint(x, y);
        }
        cur = cur->next;
    }

    qsort(xArr, i, sizeof(int), cmp);
    qsort(yArr, i, sizeof(int), cmp);
    qsort(xVal, i, sizeof(int), cmp);
    qsort(yVal, i, sizeof(double), cmp);
    medianY = yMax - (int) (relativeVal(yVal[i / 2], context->metrics->minValue, context->metrics->maxValue)
                            * (yMax - yMin));


    this->xArr = xArr;
    this->yArr = yArr;
    this->xVal = xVal;
    this->yVal = yVal;


    return arr;
}

double PlotWidget::relativeVal(double val, double min, double max) {
    return (val - min) / (max - min);
}

QString PlotWidget::trimZeros(double d) {
    string numText = to_string(d);
    return QString::fromStdString(numText.substr(0, numText.find(".")+2));
}
