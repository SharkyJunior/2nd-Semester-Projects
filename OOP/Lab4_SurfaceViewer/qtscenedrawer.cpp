#include "mainwindow.h"

#include <QGraphicsScene>
#include "normalizationparameters.h"
#include "mainwindow.h"

QtSceneDrawer::QtSceneDrawer() {}

void QtSceneDrawer::setView(QGraphicsView* view) { _view = view; }

void QtSceneDrawer::drawAxles(bool value) {_drawAxles = value; }

void QtSceneDrawer::setNormParams(NormalizationParameters normParams) { _normParams = normParams; }

void QtSceneDrawer::setSceneState(SceneState* state) { _state = state; }

void QtSceneDrawer::drawScene(const Scene& scene) {
    QGraphicsScene* qscene = new QGraphicsScene();

    QPen pen = QPen(Qt::white, 2);

    vector<Figure> figs = scene.getFigures();

    for (Figure& f : figs) {
        for (Edge& e : f.getEdges())
            qscene->addLine(e.getBegin().getPosition().x(),
                           e.getBegin().getPosition().y(),
                           e.getEnd().getPosition().x(),
                           e.getEnd().getPosition().y(), pen);
    }

    _view->setScene(qscene);

}
