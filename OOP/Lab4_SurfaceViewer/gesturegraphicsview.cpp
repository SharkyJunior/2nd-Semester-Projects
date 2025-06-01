#include "gesturegraphicsview.h"

#include <QQuaternion>

#include "consts.h"

GestureGraphicsView::GestureGraphicsView(QWidget* parent)
    : QGraphicsView(parent)
{
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setResizeAnchor(QGraphicsView::AnchorViewCenter);
}

void GestureGraphicsView::setWindow(MainWindow* window) {
    this->window = window;
}

void GestureGraphicsView::wheelEvent(QWheelEvent* event)
{
    if (event->angleDelta().y() > 0)
        window->gestureScale(SCROLL_MULTIPLIER);
    else
        window->gestureScale(-SCROLL_MULTIPLIER);
}

void GestureGraphicsView::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::RightButton) {
        dragging = true;
        lastMousePos = event->pos();
    }
    if (event->button() == Qt::LeftButton) {
        rotating = true;
        lastMousePos = event->pos();
        lastSpherePos = projectToSphere(event->pos().x(),
                                        event->pos().y(),
                                        width(), height());
    }
    QGraphicsView::mousePressEvent(event);
}

void GestureGraphicsView::mouseMoveEvent(QMouseEvent* event) {

    if (dragging) {
        QPointF delta = mapToScene(event->pos()) - mapToScene(lastMousePos);

        window->gestureMove(delta.x() * PAN_MULTIPLIER, -delta.y() * PAN_MULTIPLIER);

        lastMousePos = event->pos();
    }
    else if (rotating) {
        QVector3D curSpherePos = projectToSphere(
            event->pos().x(), event->pos().y(), width(), height());

        QVector3D axis = QVector3D::crossProduct(lastSpherePos, curSpherePos).normalized();
        double angle = std::acos(std::min(1.0f, QVector3D::dotProduct(lastSpherePos, curSpherePos)));

        double deltaDeg = angle * PI_RADIAN/M_PI;

        window->gestureRotate(-axis.x() * deltaDeg,
                              -axis.y() * deltaDeg,
                              -axis.z() * deltaDeg);

        lastSpherePos = curSpherePos;
    }
    QGraphicsView::mouseMoveEvent(event);

}

void GestureGraphicsView::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::RightButton) {
        dragging = false;
    }
    if (event->button() == Qt::LeftButton) {
        rotating = false;
    }
    QGraphicsView::mouseReleaseEvent(event);
}


QVector3D GestureGraphicsView::projectToSphere(int x, int y, int w, int h) {
    double nx =  (2.0 * x - w) / w;
    double ny = -(2.0 * y - h) / h;
    double length2 = nx*nx + ny*ny;
    double nz = length2 < 1.0 ? std::sqrt(1.0 - length2) : 0.0;
    return QVector3D(nx, ny, nz);
}
