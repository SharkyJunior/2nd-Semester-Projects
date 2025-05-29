#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "figure.h"
#include "transformmatrix.h"

class Scene
{
public:
    Scene(const std::vector<Figure>& figures);
    std::vector<Figure>& getFigures();
    void transformFigures(const TransformMatrix& transformMatrix);

private:
    std::vector<Figure> _figures;
};

class SceneDrawerBase {
public:
    virtual void drawScene(const Scene& scene);
};

class QtSceneDrawer : public SceneDrawerBase {
public:
    void drawScene(const Scene& scene) override;
};

#endif // SCENE_H
