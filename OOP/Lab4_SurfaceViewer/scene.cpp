#include "scene.h"

Scene::Scene(const std::vector<Figure>& figures)
    : _figures(figures) {}

std::vector<Figure> Scene::getFigures() const { return _figures; }

void Scene::addFigure(const Figure& figure) { _figures.push_back(figure); }

void Scene::transformFigures(const TransformMatrix& matrix) {
    for (Figure& f : _figures)
        f.transform(matrix);
}
