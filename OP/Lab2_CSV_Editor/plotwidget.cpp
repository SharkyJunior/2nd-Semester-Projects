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

    QPixmap* pix = new QPixmap();

    QLayout layout = new QLayout();
}
