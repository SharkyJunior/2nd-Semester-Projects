#include "plotwidget.h"

#include "consts.h"

PlotWidget::PlotWidget(QWidget* parent)
    : QWidget(parent)
{
    setupUi();
    setWindowTitle("Plot");
}

void PlotWidget::setupUi() {
    resize(PLOT_WINDOW_WIDTH, PLOT_WINDOW_HEIGHT);
}

void PlotWidget::paintAxles() {
    QPainter painter = QPainter(this);

    QPen pen;
    pen.setColor(QColor(Qt::GlobalColor::white));
    painter.setPen(pen);

    painter.drawLine(QPoint(100, 100), QPoint(100, ))
}
