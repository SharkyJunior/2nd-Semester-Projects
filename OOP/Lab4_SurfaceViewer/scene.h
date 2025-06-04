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


class SceneState {
    double curPosX, curPosY, curPosZ,
        curRotX, curRotY, curRotZ,
        curScaleX, curScaleY, curScaleZ;

public:
    // Position Getters and Setters
    double getCurPosX() const { return curPosX; }
    void setCurPosX(double value) { curPosX = value; }

    double getCurPosY() const { return curPosY; }
    void setCurPosY(double value) { curPosY = value; }

    double getCurPosZ() const { return curPosZ; }
    void setCurPosZ(double value) { curPosZ = value; }

    // Rotation Getters and Setters
    double getCurRotX() const { return curRotX; }
    void setCurRotX(double value) { curRotX = value; }

    double getCurRotY() const { return curRotY; }
    void setCurRotY(double value) { curRotY = value; }

    double getCurRotZ() const { return curRotZ; }
    void setCurRotZ(double value) { curRotZ = value; }

    // Scale Getters and Setters
    double getCurScaleX() const { return curScaleX; }
    void setCurScaleX(double value) { curScaleX = value; }

    double getCurScaleY() const { return curScaleY; }
    void setCurScaleY(double value) { curScaleY = value; }

    double getCurScaleZ() const { return curScaleZ; }
    void setCurScaleZ(double value) { curScaleZ = value; }
};

#endif // SCENE_H
