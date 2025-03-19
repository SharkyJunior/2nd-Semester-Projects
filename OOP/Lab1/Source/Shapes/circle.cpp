#include "circle.hpp"
#include <sstream>
#include <iomanip>

Circle::Circle(string name, const Point& center, double radius) 
    : Shape(name)
{
    if (radius <= 0)
        throw invalid_argument("Radius can't be negative");

    this->center = center;
    this->radius = radius;
}

string Circle::getInfo() {
    stringstream s;
    s << fixed << setprecision(2) << "Circle \"" << name << "\" with center at (" 
        << center.getX() << ", " << center.getY() << ") and radius " << radius;
    return s.str();
}

double Circle::getPerimeter() {
    return 2 * M_PI * radius;
}