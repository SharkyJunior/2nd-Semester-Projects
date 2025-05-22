#include "commandfactory.h"

#include "commands.h"

Command* CommandFactory::createPlus(double a, double b) const {
    return new PlusCommand(a, b);
}

Command* CommandFactory::createMinus(double a, double b) const {
    return new MinusCommand(a, b);
}

Command* CommandFactory::createMultiply(double a, double b) const {
    return new MultiplyCommand(a, b);
}

Command* CommandFactory::createDivide(double a, double b) const {
    return new DivideCommand(a, b);
}
