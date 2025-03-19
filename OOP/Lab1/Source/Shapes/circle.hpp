#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.hpp"
#include "point.hpp"

using namespace std;

class Circle: public Shape {
    Point center;
    double radius;
    
    public:
        Circle(const string& name, const Point& center, double radius);
        double getPerimeter() override;
        string getInfo() override;
        using Shape::getName;
        
};

#endif