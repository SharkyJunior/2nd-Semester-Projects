#ifndef APPLICATION_H
#define APPLICATION_H

#include <vector>
#include <map>
#include <functional>

#include "Shapes/shape.hpp"
#include "Shapes/point.hpp"
#include "Shapes/circle.hpp"
#include "Shapes/rectangle.hpp"
#include "Shapes/triangle.hpp"

using namespace std;

class Application {
    vector<Shape*> shapes;
    map<int, void (Application::*)()> menuActions;
    map<int, Shape* (Application::*)()> shapeSelectors;
    bool isRunning;
    
    // menu actions
    void addShape();
    void printInfo();
    void printPerimeters();
    void printPerimeterSum();
    void sortByPerimeter();
    void deleteShape();
    void deleteShapesByPerimeter();

    // shape creators
    Shape* createCircle();
    Shape* createRectangle();
    Shape* createTriangle();

    // utilities
    void printMenu();
    unsigned readOption();
    Shape* readShape(); 

    public:
        Application();
        ~Application();
        void run();
        void stop();
};

#endif