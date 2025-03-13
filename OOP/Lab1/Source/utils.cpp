#include "utils.hpp"

int cmpPerimeters(Shape* a, Shape* b) {
    return (a->getPerimeter() < b->getPerimeter());
}