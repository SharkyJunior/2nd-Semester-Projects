#ifndef VERTEX_H
#define VERTEX_H

#include "point3d.h"
#include "sceneobject.h"
#include "transformmatrix.h"

// done

class Vertex : public SceneObject
{
    Point3D _position;
public:
    Vertex();
    Vertex(Point3D position);
    Point3D getPosition() const;
    void transform(const TransformMatrix& matrix) override;

};

#endif // VERTEX_H
