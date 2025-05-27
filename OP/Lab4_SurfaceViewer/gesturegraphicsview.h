#ifndef GESTUREGRAPHICSVIEW_H
#define GESTUREGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QWheelEvent>

#include <mainwindow.h>

class GestureGraphicsView : public QGraphicsView {
    Q_OBJECT

public:
    explicit GestureGraphicsView(QWidget* parent = nullptr);
    void setWindow(MainWindow* window);

protected:
    void wheelEvent(QWheelEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    bool dragging = false, rotating = false;
    QPoint lastMousePos;
    MainWindow* window;
};

#endif // GESTUREGRAPHICSVIEW_H
