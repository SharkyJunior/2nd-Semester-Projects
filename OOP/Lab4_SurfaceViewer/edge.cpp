#include "edge.h"

Edge::Edge() {}

Edge::Edge(const Vertex& begin, const Vertex& end)
    : _begin(begin), _end(end) {}

Vertex Edge::getBegin() const { return _begin; }

Vertex Edge::getEnd() const { return _end; }

void Edge::transform(const TransformMatrix& matrix) {
    _begin.transform(matrix);
    _end.transform(matrix);
}
