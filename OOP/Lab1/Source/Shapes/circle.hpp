#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.hpp"
#include "point.hpp"

using namespace std;

class Circle: public Shape {
    Point center;
    double radius;

    void input(istream& is) override {
        is >> name >> center >> radius;
    }
    
    public:
        Circle() : Shape(name) {};
        Circle(const string& name, const Point& center, double radius);
        double getPerimeter() override;
        string getInfo() override;
        using Shape::getName;
        
        // friend istream& operator>>(istream& is, Circle& a) {
        //     string temp;
        //     is >> a.name >> a.center >> temp;
        //     a.radius = stod(temp);

        //     return is;
        // }
};

#endif