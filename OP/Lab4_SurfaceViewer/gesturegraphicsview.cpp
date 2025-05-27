#include "gesturegraphicsview.h"

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
        QPointF delta = mapToScene(event->pos()) - mapToScene(lastMousePos);
        double pitchRad = window->context.camera.angleX * M_PI / PI_RADIAN;

        window->context.camera.angleX += delta.x() * PAN_MULTIPLIER * std::cos(pitchRad);
        window->context.camera.angleX = std::clamp(window->context.camera.angleX, -90.0, 90.0);
        window->context.camera.angleY -= delta.y() * PAN_MULTIPLIER;
        window->context.camera.angleY = std::clamp(window->context.camera.angleY, -90.0, 90.0);
        lastMousePos = event->pos();

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
