#include "rectangle.hpp"
#include <exception>
#include <sstream>
#include <iomanip>

Rectangle::Rectangle(string& name, const Point& point1, const Point& point2) 
    : Shape(name)
{
    if (point1 == point2)
        throw invalid_argument("Error: Corners can't be identical");
    if (point1.getX() == point2.getX() || point1.getY() == point2.getY())
        throw invalid_argument("Error: Area is zero");

    this->point1 = point1;  
    this->point2 = point2;
}

string Rectangle::getInfo() {
    stringstream s;
    s << fixed << setprecision(2);
    s << "Rectangle \"" << name << "\" with left upper corner at (" << point1.getX()
        << ", " << point1.getY() << ") and right lower corner at (" 
        << point2.getX() << ", " << point2.getY() << ")";
    return s.str();
}

double Rectangle::getPerimeter() {
    return (abs(point1.getX() - point2.getX()) + abs(point1.getY() - point2.getY())) * 2;
}