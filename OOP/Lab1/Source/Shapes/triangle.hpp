#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "shape.hpp"
#include "point.hpp"

class Triangle: public Shape {
    Point p1, p2, p3;

    bool isCollinear(const Point& a, const Point& b, const Point& c);
    double getSideLength(const Point& a, const Point& b) const;
    
    public:
        Triangle(const string& name, const Point& p1, const Point& p2, const Point& p3);
        double getPerimeter() override;
        string getInfo() override;
        using Shape::getName;
};

#endif