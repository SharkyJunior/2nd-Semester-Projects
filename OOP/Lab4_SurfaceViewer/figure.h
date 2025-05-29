#ifndef FIGURE_H
#define FIGURE_H

#include <vector>

#include "vertex.h"
#include "edge.h"
#include "sceneobject.h"

// done

class Figure : public SceneObject
{ 
public:
    Figure();
    Figure(const std::vector<Vertex>& vertices,
           const std::vector<Edge>& edges);

    std::vector<Vertex> getVertices() const;
    void addVertex(Vertex vertex);
    std::vector<Edge> getEdges() const;
    void addEdge(Edge edge);
    void transform(const TransformMatrix& matrix) override;

private:
    std::vector<Vertex> _vertices;
    std::vector<Edge> _edges;


};

#endif // FIGURE_H
