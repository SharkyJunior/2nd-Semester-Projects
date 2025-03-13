#include <exception>
#include <sstream>
#include <iomanip>
#include "shapes.hpp"
#include "app.hpp"

using namespace std;

//constructors
Circle::Circle(string name, const Point& center, double radius) {
    if (radius <= 0)
        throw invalid_argument("Radius can't be negative");

    this->name = name;
    this->center = center;
    this->radius = radius;
}

Rectangle::Rectangle(string name, const Point& point1, const Point& point2) {
    if (point1 == point2)
        throw invalid_argument("Error: Corners can't be identical");
    if (point1.x == point2.x || point1.y == point2.y)
        throw invalid_argument("Error: Area is zero");

    this->name = name;
    this->point1 = point1;   
    this->point2 = point2;
}

Triangle::Triangle(string name, const Point& point1, const Point& point2, const Point& point3) {
    if (isCollinear(point1, point2, point3))
        throw invalid_argument("Error: Triangle vertices can't be collinear");
    if (point1 == point2 && point2 == point3)
        throw invalid_argument("Error: Verteces can't be identical");

    this->name = name;
    this->points[0] = point1;
    this->points[1] = point2;
    this->points[2] = point3;
}



string Circle::getInfo() {
    stringstream s;
    s << fixed << setprecision(2) << "Circle \"" << name << "\" with center at (" 
        << center.x << ", " << center.y << ") and radius " << radius;
    return s.str();
}

double Circle::getPerimeter() {
    return 2 * M_PI * radius;
}

string Rectangle::getInfo() {
    stringstream s;
    s << fixed << setprecision(2);
    s << "Rectangle \"" << name << "\" with left upper corner at (" << point1.x
        << ", " << point1.y << ") and right lower corner at (" 
        << point2.x << ", " << point2.y << ")";
    return s.str();
}

double Rectangle::getPerimeter() {
    return (abs(point1.x - point2.x) + abs(point1.y - point2.y)) * 2;
}

string Triangle::getInfo() {
    stringstream s;
    s << fixed << setprecision(2);
    s << "Triangle \"" << name << "\" with vertexes";
    for (int i = 0; i < 2; i++)
        s << " (" << points[i].x << ", " << points[i].y << "),";
    s << " (" << points[2].x << ", " << points[2].y << ")";
    return s.str();
}

double Triangle::getPerimeter() {
    double perimeter = 0;
    int deltaX, deltaY;

    for (int i = 0; i < 3; i++) {
        deltaX = points[(i+1)%3].x - points[i].x;
        deltaY = points[(i+1)%3].y - points[i].y;
        perimeter += sqrt(deltaX * deltaX + deltaY * deltaY);
    }

    return perimeter;
}

bool Triangle::isCollinear(const Point& a, const Point& b, const Point& c) 
{
    return (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y)) == 0;
}