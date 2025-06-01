#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <string>

class FileNotOpenedException : public std::exception
{
public:
    explicit FileNotOpenedException(const std::string& message){
        this->msg = message;
    }
    const char* what() const noexcept override {
        return msg.c_str();
    }

private:
    std::string msg;
};

class BadFileException : public std::exception
{
public:
    explicit BadFileException(const std::string& message){
        this->msg = message;
    }
    const char* what() const noexcept override {
        return msg.c_str();
    }

private:
    std::string msg;
};

#endif // EXCEPTIONS_H
