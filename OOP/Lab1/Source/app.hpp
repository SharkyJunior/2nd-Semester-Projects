#ifndef APPLICATION_H
#define APPLICATION_H

#include <vector>
#include <map>
#include <functional>
#include "shapes.hpp"

using namespace std;

enum ShapeType {
    CIRCLE = 1,
    RECTANGLE = 2,
    TRIANGLE = 3
};

class Application {
    vector<Shape*> shapes;
    map<int, void (Application::*)()> menuActions;

    // menu actions
    void addShape();
    void printInfo();
    void printPerimeters();
    void printPerimeterSum();
    void sortByPerimeter();
    void deleteShape();
    void deleteShapesByPerimeter();

    // utilities
    void printMenu();
    unsigned readOption();
    Shape* readShape(); 

    public:
        static const unsigned menuActionCount = 7;
        Application();
        ~Application();
        int run();
};

#endif