#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "figure.h"
#include "transformmatrix.h"

// done

class Scene
{
public:
    Scene() = default;
    Scene(const std::vector<Figure>& figures);
    std::vector<Figure> getFigures() const;
    void transformFigures(const TransformMatrix& transformMatrix);
    void addFigure(const Figure& figure);

private:
    std::vector<Figure> _figures;
};

class SceneDrawerBase {
public:
    virtual void drawScene(const Scene& scene) = 0;
    virtual ~SceneDrawerBase() {}
};

#endif // SCENE_H
