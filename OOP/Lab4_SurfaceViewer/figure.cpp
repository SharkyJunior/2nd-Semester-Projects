#include "figure.h"

Figure::Figure() {}

Figure::Figure(const std::vector<Vertex>& vertices, const std::vector<Edge>& edges)
    : _vertices(vertices), _edges(edges) {}

std::vector<Vertex> Figure::getVertices() const { return _vertices; }

std::vector<Edge> Figure::getEdges() const { return _edges; }

void Figure::addVertex(Vertex vertex) { _vertices.push_back(vertex); }

void Figure::addEdge(Edge edge) { _edges.push_back(edge); }

void Figure::transform(const TransformMatrix& matrix) {
    for (Vertex v : _vertices)
        v.transform(matrix);
    for (Edge e : _edges)
        e.transform(matrix);
}
