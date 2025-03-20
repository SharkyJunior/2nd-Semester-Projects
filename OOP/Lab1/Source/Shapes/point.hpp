#ifndef POINT_H
#define POINT_H

#include <iostream>

using namespace std;

class Point {
    double x, y;

    public:
    Point(double x = 0, double y = 0) : x(x), y(y) {};
    bool operator==(const Point& a) const {
        return (x == a.x && y == a.y);
    }

    friend istream& operator>>(istream& is, Point& a) {
        string temp;
        is >> temp;
        a.x = stod(temp);
        is >> temp;
        a.y = stod(temp);

        return is;
    }

    friend ostream& operator<<(ostream& os, const Point& a) {
        os << "(" << a.x << ", " << a.y << ")";
        return os;
    }

    void setX(double x) {
        this->x = x;
    };
    void setY(double y) { this->y = y; };
    double getX() const {return x;};
    double getY() const {return y;};

}; 

#endif