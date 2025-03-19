#ifndef SHAPES_H
#define SHAPES_H

#include <string>

using namespace std;

class Shape {
    protected:
        string name;

    public:
        Shape(const string& name); 
        virtual double getPerimeter() = 0;
        virtual string getInfo() = 0;
        virtual string getName();

        bool operator<(Shape& a);
};

#endif