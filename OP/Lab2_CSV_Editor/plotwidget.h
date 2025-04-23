#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include <QPainter>
#include <QWidget>
#include "rownode.h"
#include "appcontext.h"

class PlotWidget : public QWidget
{
    Q_OBJECT

private:
    const AppContext* context;
    unsigned column, medianY;

    int* xArr, *yArr, *xVal;
    double* yVal;
    size_t yMin, yMax, xMin, xMax;
    QPoint* points;

    void setupUi();

    // plot components
    void paintAxles();
    void paintPlot();
    void paintMinMaxMedian();
    void paintMarks();

    // utilities
    static int cmp(const void* a, const void* b);
    QPoint* getPlotPoints();
    double relativeVal(double val, double min, double max);
    QString trimZeros(double d);

protected:
    void paintEvent(QPaintEvent *event) override;

public:
    explicit PlotWidget(QWidget* parent = nullptr);
    void setContext(const AppContext* context);
};

#endif // PLOTWIDGET_H
