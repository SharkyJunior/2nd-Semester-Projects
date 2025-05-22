#ifndef COMMANDFACTORY_H
#define COMMANDFACTORY_H

#include "commands.h"

class CommandFactory
{
public:
    typedef Command* (CommandFactory::*CommandCreator)(double, double) const;

    Command* createPlus(double a, double b) const;
    Command* createMinus(double a, double b) const;
    Command* createMultiply(double a, double b) const;
    Command* createDivide(double a, double b) const;
};

#endif // COMMANDFACTORY_H
