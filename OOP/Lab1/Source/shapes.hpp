#ifndef SHAPES_H
#define SHAPES_H

#include <string>

using namespace std;

struct Point {
    double x, y;

    bool operator==(const Point& a) const {
        return (x == a.x && y == a.y);
    }
}; 

class Shape {
    protected:
        string name;

    public:
        Shape() {};
        virtual ~Shape() { };
        virtual double getPerimeter() = 0;
        virtual string getInfo() = 0;
        string getName() {
            return name;
        }
};


class Circle: public Shape {
    Point center;
    double radius;
    
    public:
        Circle(string name, const Point& center, double radius);
        double getPerimeter() override;
        string getInfo() override;
};

class Rectangle: public Shape {
    Point point1, point2;
    
    public:
        Rectangle(string name, const Point& point1, const Point& point2);
        double getPerimeter() override;
        string getInfo() override;
};

class Triangle: public Shape {
    Point points[3];

    bool isCollinear(const Point& a, const Point& b, const Point& c);
    
    public:
        Triangle(string name, const Point& point1, const Point& point2, const Point& point3);
        double getPerimeter() override;
        string getInfo() override;
};

// class Polygon : virtual Shape {
//     vector<Point> points;

//     public:
//         Polygon(const vector<Point> &points);
//         ~Polygon() = default;
//         double getPerimeter();
//         string getInfo();
// };

#endif