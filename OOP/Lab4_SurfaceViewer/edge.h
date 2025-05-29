#ifndef EDGE_H
#define EDGE_H

#include "vertex.h"

// done

class Edge
{
    Vertex _begin, _end;
public:
    Edge();
    Edge(const Vertex& begin, const Vertex& end);

    Vertex getBegin() const;
    Vertex getEnd() const;
    void transform(const TransformMatrix& matrix);
};

#endif // EDGE_H
