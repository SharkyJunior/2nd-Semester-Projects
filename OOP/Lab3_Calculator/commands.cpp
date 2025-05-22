#include "commands.h"
#include "exceptions.h"

PlusCommand::PlusCommand(double a, double b)
    : a(a), b(b) {}
double PlusCommand::execute() const {
    return a + b;
}
int PlusCommand::priority() const {
    return 2;
}

MinusCommand::MinusCommand(double a, double b)
    : a(a), b(b) {}
double MinusCommand::execute() const {
    return a - b;
}
int MinusCommand::priority() const {
    return 2;
}

MultiplyCommand::MultiplyCommand(double a, double b)
    : a(a), b(b) {}
double MultiplyCommand::execute() const {
    return a * b;
}
int MultiplyCommand::priority() const {
    return 3;
}

DivideCommand::DivideCommand(double a, double b)
    : a(a), b(b) {}
double DivideCommand::execute() const {
    if (b == 0) throw InfException("Division by zero");
    return a / b;
}
int DivideCommand::priority() const {
    return 3;
}
