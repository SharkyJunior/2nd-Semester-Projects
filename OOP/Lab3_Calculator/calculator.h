#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>

#include "dijkstra.h"

class Calculator
{
public:
    Calculator() = default;
    double evaluate(const std::string& expression) const;

    //memory methods
    std::string getMemory();
    void memoryPlus(const std::string& value);
    void memoryMinus(const std::string& value);
    void memoryClear();
private:
    Dijkstra dijkstra;
    double memory;
    bool memoryEmpty = true;
};

#endif // CALCULATOR_H
