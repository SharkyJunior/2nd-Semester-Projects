#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.hpp"
#include "point.hpp"

class Circle: public Shape {
    Point center;
    double radius;
    
    public:
        Circle(string name, const Point& center, double radius) : Shape(name) {};
        double getPerimeter() override;
        string getInfo() override;
};

#endif