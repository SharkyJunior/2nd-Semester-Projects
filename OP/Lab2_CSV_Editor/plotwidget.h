#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include <QPainter>
#include <QWidget>
#include "rownode.h"
#include "appcontext.h"

struct PlotPoint {
    int year;
    double value;
};

class PlotWidget : public QWidget
{
    Q_OBJECT

private:


    void setupUi();

public:
    explicit PlotWidget(QWidget* parent = nullptr);
};

#endif // PLOTWIDGET_H
