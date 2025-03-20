#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "shape.hpp"
#include "point.hpp"

class Triangle: public Shape {
    Point p1, p2, p3;

    bool isCollinear(const Point& a, const Point& b, const Point& c);
    double getSideLength(const Point& a, const Point& b) const;

    void input(istream& is) override {
        is >> name >> p1 >> p2 >> p3;
    }
    
    public:
        Triangle() : Shape(name) {};
        Triangle(const string& name, const Point& p1, const Point& p2, const Point& p3);
        double getPerimeter() override;
        string getInfo() override;

        // friend istream& operator>>(istream& is, Triangle& a) {
        //     string name;
        //     Point p1, p2, p3;
        //     is >> name >> p1 >> p2 >> p3;

        //     a = Triangle(name, p1, p2, p3);
            
        //     return is;
        // }
};

#endif