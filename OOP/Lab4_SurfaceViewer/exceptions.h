#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <string>

class BaseException : public std::exception
{
public:
    const char* what() const noexcept override {
        return msg.c_str();
    }

private:
    std::string msg;
};

class FileNotOpenedException : public BaseException
{
public:
    explicit FileNotOpenedException(const std::string& message){
        this->msg = message;
    }
};

class EmptyFileException : public std::exception
{
public:
    explicit EmptyFileException(const std::string& message){
        this->msg = message;
    }
    const char* what() const noexcept override {
        return msg.c_str();
    }

private:
    std::string msg;
};

#endif // EXCEPTIONS_H
