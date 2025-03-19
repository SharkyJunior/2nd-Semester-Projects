#include "shape.hpp"

bool Shape::operator<(Shape& a) {
    return getPerimeter() < a.getPerimeter();
}

string Shape::getName() {
    return name;
}

Shape::Shape(const string& name) 
{ 
    this->name = name; 
}