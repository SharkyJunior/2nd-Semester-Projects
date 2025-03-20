#include <iostream>
#include <algorithm>
#include <exception>
#include <iomanip>
#include <stdlib.h> 
#include "app.hpp"

using namespace std;


Application::Application() {
    menuActions[0] = &Application::stop;
    menuActions[1] = &Application::addShape;
    menuActions[2] = &Application::printInfo;
    menuActions[3] = &Application::printPerimeters;
    menuActions[4] = &Application::printPerimeterSum;
    menuActions[5] = &Application::sortByPerimeter;
    menuActions[6] = &Application::deleteShape;
    menuActions[7] = &Application::deleteShapesByPerimeter;

    shapeSelectors[1] = &Application::createCircle;
    shapeSelectors[2] = &Application::createRectangle;
    shapeSelectors[3] = &Application::createTriangle;

    isRunning = false;
}


void Application::run() {
    cout << fixed << setprecision(2);
    int option;
    string input;

    isRunning = true;
    while (isRunning) {
        printMenu();
        try {
            option = readOption();
            if (menuActions[option] == nullptr)
                throw "Error: No such option.";
            (this->*menuActions[option])();
        }
        catch (const exception& e) {
            cout << endl << e.what() << endl;
        }
    }
}

void Application::stop() {
    isRunning = false;
    cout << "\nGoodbye!\n";
}

Application::~Application() {
    shapes.clear();
}

void Application::addShape() {
    Shape* shape = readShape();
    shapes.push_back(shape);
}

void Application::printInfo() {
    if (shapes.size() > 0) {
        cout << "\nShape information:\n";
        for (int i = 0; i < shapes.size(); i++)
            cout << to_string(i+1) + ". " + shapes[i]->getInfo() + "\n";
    }
    else
        cout << "\n* No shapes yet. *\n";
}

void Application::printPerimeters() {
    if (shapes.size() > 0) {
        cout << "\nShape perimeters:\n";
        for (int i = 0; i < shapes.size(); i++)
            cout << to_string(i+1) + ". \"" + shapes[i]->getName() + "\": " 
                << shapes[i]->getPerimeter() << "\n";
    }
    else
        cout << "\n* No shapes yet. *\n";
}

void Application::printPerimeterSum() {
    double sum = 0;
    
    for (int i = 0; i < shapes.size(); i++)
        sum += shapes[i]->getPerimeter();
    
    cout << "\nTotal perimeter: " << sum << "\n";
}

void Application::sortByPerimeter() {
    sort(shapes.begin(), shapes.end());
}


void Application::deleteShape() {
    string input;
    cout << "\nInput shape number:\n> ";
    cin >> input;
    unsigned n = stoi(input);

    if (n < 0 || n > shapes.size())
        throw out_of_range("\nError: Index out of range\n");
    
    shapes.erase(shapes.begin() + n - 1);
}

void Application::deleteShapesByPerimeter() {
    string input;
    cout << "\nInput maximum perimeter value:\n> ";
    cin >> input;
    double maxPerimeter = stod(input);

    for (int i = 0; i < shapes.size(); i++)
        if (shapes[i]->getPerimeter() > maxPerimeter)
            shapes.erase(shapes.begin() + i--);
}

unsigned Application::readOption() {
    string input;
    unsigned option;
    bool valid = false;
    while (!valid) {
        try {
            cout << "\nChoose option: ";
            cin >> input;
            option = stoi(input);
            valid = true;
        }
        catch (const invalid_argument& e) {cout << "\nError: Invalid input.\n";}
    }

    return option;
}

Shape* Application::readShape() {
    Shape* shape = nullptr;

    cout << "\nChoose shape type:\n1 - Circle\n2 - Rectangle\n3 - Triangle\n";
    int opt = readOption(); 

    shape = (this->*shapeSelectors[opt])();

    return shape;
}


void Application::printMenu() {
    cout << "\n<-- Menu -->\n1. Add shape to list\n2. Show list of shapes\n"
        << "3. Show perimeters of shapes\n4. Calculate sum of perimeters\n"
        << "5. Sort shapes by perimeter\n6. Delete shape by index\n"
        << "7. Delete shape above perimeter threshold\n0. Exit program\n";
}

Shape* Application::createCircle() {
    cout << "Input name, center and radius:\n";
    Shape* shape = new Circle();
    cin >> *shape;
    return shape;
}

Shape* Application::createRectangle() {
    cout << "Input name and two corners:\n";
    Shape* shape = new Rectangle();
    cin >> *shape;
    return shape;
}

Shape* Application::createTriangle() {
    cout << "Input name and 3 verteces:\n";
    Shape* shape = new Triangle();
    cin >> *shape;
    return shape;
}