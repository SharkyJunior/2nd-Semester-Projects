#include "triangle.hpp"
#include <sstream>
#include <iomanip>

Triangle::Triangle(string name, const Point& p1, const Point& p2, const Point& p3) 
    : Shape(name)
{
    if (isCollinear(p1, p2, p3))
        throw invalid_argument("Error: Triangle vertices can't be collinear");
    if (p1 == p2 && p2 == p3)
        throw invalid_argument("Error: Verteces can't be identical");


    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
}

string Triangle::getInfo() {
    Point points[3] = {p1, p2, p3};
    stringstream s;
    s << fixed << setprecision(2);
    s << "Triangle \"" << name << "\" with vertexes";
    for (int i = 0; i < 2; i++)
        s << " (" << points[i].getX() << ", " << points[i].getY() << "),";
    s << " (" << points[2].getX() << ", " << points[2].getY() << ")";
    return s.str();
}

double Triangle::getPerimeter() {
    Point points[3] = {p1, p2, p3};
    double perimeter = 0;
    int deltaX, deltaY;

    for (int i = 0; i < 3; i++)
        perimeter += getSideLength(points[i], points[(i+1)%3]);

    return perimeter;
}

bool Triangle::isCollinear(const Point& a, const Point& b, const Point& c) 
{
    return (a.getX() * (b.getY() - c.getY()) + 
        b.getX() * (c.getY() - a.getY()) + 
        c.getX() * (a.getY() - b.getY())) == 0;
}

double Triangle::getSideLength(const Point& a, const Point& b) const {
    return sqrt((a.getX() - b.getX()) * (a.getX() - b.getX()) + 
        (a.getY() - b.getY()) * (a.getY() - b.getY()));
}