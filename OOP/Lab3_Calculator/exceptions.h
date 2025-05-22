#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <string>

class InfException : public std::exception
{
public:
    explicit InfException(const std::string& message){
        this->msg = message;
    }
    const char* what() const noexcept override {
        return msg.c_str();
    }

private:
    std::string msg;
};

class InvalidExpression : public std::exception
{
public:
    explicit InvalidExpression(const std::string& message = "Invalid expression"){
        this->msg = message;
    }
    const char* what() const noexcept override {
        return msg.c_str();
    }

private:
    std::string msg;
};

class MemoryEmpty : public std::exception
{
public:
    explicit MemoryEmpty(const std::string& message = "Memory is empty"){
        this->msg = message;
    }
    const char* what() const noexcept override {
        return msg.c_str();
    }

private:
    std::string msg;
};


#endif // EXCEPTIONS_H
