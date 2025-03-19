#include <iostream>
#include <algorithm>
#include <exception>
#include <iomanip>
#include <stdlib.h> 
#include "app.hpp"

using namespace std;


Application::Application() {
    menuActions[1] = &Application::addShape;
    menuActions[2] = &Application::printInfo;
    menuActions[3] = &Application::printPerimeters;
    menuActions[4] = &Application::printPerimeterSum;
    menuActions[5] = &Application::sortByPerimeter;
    menuActions[6] = &Application::deleteShape;
    menuActions[7] = &Application::deleteShapesByPerimeter;

    isRunning = false;
}


void Application::run() {
    isRunning = true;
    cout << fixed << setprecision(2);
    int option = 1;
    string input;

    while (isRunning) {
        printMenu();
        try {
            option = readOption();
            if (option == 0) {
                stop();
                continue;
            }
            auto it = menuActions.find(option);
            if (it != menuActions.end())
                (this->*(it->second))();
            else
                throw invalid_argument("\nError: No such option.\n");
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

void Application::addShape() 
{
    Shape* shape = readShape();
    shapes.push_back(shape);
}

void Application::printInfo() 
{
    if (shapes.size() > 0) {
        cout << "\nShape information:\n" << shapes.size();
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
    int option;
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
    Shape* shape;
    string input, name;
    ShapeSelectorOptions opt;

    cout << "\nChoose shape type:\n1 - Circle\n2 - Rectangle\n3 - Triangle\n";
    opt = (ShapeSelectorOptions) readOption(); // add checks

    cout << "Input shape name:\n> ";
    cin >> name;
    if (opt == CIRCLE) {
        double x, y, r;
        cout << "Input center X:\n> ";
        cin >> input;
        x = stod(input);
        cout << "Input center Y:\n> ";
        cin >> input;
        y = stod(input);
        cout << "Input radius:\n> ";
        cin >> input;
        r = stod(input);
        Point c = Point(x, y);
        shape = new Circle(name, c, r);
    }
    else if (opt == RECTANGLE) {
        double x1, x2, y1, y2;
        cout << "Input first point X:\n> ";
        cin >> input;
        x1 = stod(input);
        cout << "Input first point Y:\n> ";
        cin >> input;
        y1 = stod(input);
        cout << "Input second point X:\n> ";
        cin >> input;
        x2 = stod(input);
        cout << "Input second point Y:\n> ";
        cin >> input;
        y2 = stod(input);
        Point c1 = Point(x1, y1), c2 = Point(x2, y2);
        shape = new Rectangle(name, c1, c2);
    }
    else
    {
        double x1, x2, x3, y1, y2, y3;
        cout << "Input first point X:\n> ";
        cin >> input;
        x1 = stod(input);
        cout << "Input first point Y:\n> ";
        cin >> input;
        y1 = stod(input);
        cout << "Input second point X:\n> ";
        cin >> input;
        x2 = stod(input);
        cout << "Input second point Y:\n> ";
        cin >> input;
        y2 = stod(input);
        cout << "Input third point X:\n> ";
        cin >> input;
        x3 = stod(input);
        cout << "Input third point Y:\n> ";
        cin >> input;
        y3 = stod(input);
        Point c1 = Point(x1, y1), c2 = Point(x2, y2), c3 = Point(x3, y3);
        shape = new Triangle(name, c1, c2, c3);
    }
    return shape;
}

void Application::printMenu() {
    cout << "\n<-- Menu -->\n1. Add shape to list\n2. Show list of shapes\n"
        << "3. Show perimeters of shapes\n4. Calculate sum of perimeters\n"
        << "5. Sort shapes by perimeter\n6. Delete shape by index\n"
        << "7. Delete shape above perimeter threshold\n0. Exit program\n";
}

