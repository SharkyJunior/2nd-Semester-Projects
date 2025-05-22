#ifndef COMMANDS_H
#define COMMANDS_H

class Command
{
public:
    virtual ~Command() = default;
    virtual double execute() const = 0;
    virtual int priority() const = 0;
    virtual bool isFunction() const { return false; }
};

class PlusCommand : public Command {
    double a, b;
public:
    PlusCommand(double a, double b);
    double execute() const override;
    int priority() const override;
};

class MinusCommand : public Command {
    double a, b;
public:
    MinusCommand(double a, double b);
    double execute() const override;
    int priority() const override;
};

class MultiplyCommand : public Command {
    double a, b;
public:
    MultiplyCommand(double a, double b);
    double execute() const override;
    int priority() const override;
};

class DivideCommand : public Command {
    double a, b;
public:
    DivideCommand(double a, double b);
    double execute() const override;
    int priority() const override;
};


#endif // COMMANDS_H
