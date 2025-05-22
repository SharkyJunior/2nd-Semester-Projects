#include "calculator.h"

#include "exceptions.h"

double Calculator::evaluate(const std::string& expression) const {
    return dijkstra.evaluate(expression);
}

std::string Calculator::getMemory() {
    if (memoryEmpty) {
        throw MemoryEmpty();
        return "";
    }
    if ((int) memory == memory)
        return std::to_string((int) memory);
    else {
        std::string str = std::to_string(memory);
        while (str[str.size() - 1] == '0')
            str.pop_back();
        return str;
    }
}

void Calculator::memoryPlus(const std::string& value) {
    try {
        double val = std::stod(value);
        memory += val;
        memoryEmpty = false;
    }
    catch (std::exception e) {
        throw InvalidExpression("Not a number to save");
    }
}

void Calculator::memoryMinus(const std::string& value) {
    try {
        double val = std::stod(value);
        memory -= val;
        memoryEmpty = false;
    }
    catch (std::exception e) {
        throw InvalidExpression("Not a number to save");
    }
}

void Calculator::memoryClear() {
    memory = 0;
    memoryEmpty = true;
}
