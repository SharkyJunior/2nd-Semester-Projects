#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.hpp"
#include "point.hpp"

class Rectangle: public Shape {
    Point point1, point2;
    
    public:
        Rectangle(string& name, const Point& point1, const Point& point2) : Shape(name) {};
        double getPerimeter() override;
        string getInfo() override;
};

#endif