#include "vertex.h"

Vertex::Vertex() {}

Vertex::Vertex(Point3D position)
    : _position(position) {}

Point3D Vertex::getPosition() const { return _position; }

void Vertex::transform(const TransformMatrix& matrix) {
    _position = matrix.transformPoint(_position);
}
