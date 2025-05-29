#include "gesturegraphicsview.h"

#include <QQuaternion>

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
    window->isGesture = true;

    if (event->angleDelta().y() > 0)
        window->context.camera.scale += SCROLL_MULTIPLIER;
    else
        window->context.camera.scale -= SCROLL_MULTIPLIER;

    window->onEditorChanged();
    window->updateUi();

    window->isGesture = false;
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
        window->context.camera.posX += delta.x() * PAN_MULTIPLIER;
        window->context.camera.posY -= delta.y() * PAN_MULTIPLIER;
        lastMousePos = event->pos();

        window->isGesture = true;

        window->onEditorChanged();
        window->updateUi();

        window->isGesture = false;
    }
    else if (rotating) {
        QVector3D curSpherePos = projectToSphere(
            event->pos().x(), event->pos().y(), width(), height());

        QVector3D axis = QVector3D::crossProduct(lastSpherePos, curSpherePos).normalized();
        double angle = std::acos(std::min(1.0f, QVector3D::dotProduct(lastSpherePos, curSpherePos)));

        double deltaDeg = angle * PI_RADIAN/M_PI;

        // apply the rotation around each axis
        window->context.camera.angleX -= axis.x() * deltaDeg;
        window->context.camera.angleY -= axis.y() * deltaDeg;
        window->context.camera.angleZ -= axis.z() * deltaDeg;

        // keep angles in a sane range (optional)
        window->context.camera.angleX = std::fmod(window->context.camera.angleX + 360.0, 360.0);
        window->context.camera.angleY = std::fmod(window->context.camera.angleY + 360.0, 360.0);
        window->context.camera.angleZ = std::fmod(window->context.camera.angleZ + 360.0, 360.0);

        lastSpherePos = curSpherePos;

        window->isGesture = true;

        window->onEditorChanged();
        window->updateUi();

        window->isGesture = false;
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
