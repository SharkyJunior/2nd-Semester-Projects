#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <string>
#include <vector>
#include <map>

#include "commandfactory.h"

class Dijkstra {
public:
    Dijkstra();
    double evaluate(const std::string& expression) const;

private:
    std::vector<std::string> tokenize(const std::string& expression) const;
    bool isNumber(const std::string& token) const;
    bool isOperator(const std::string& token) const;
    bool isFunction(const std::string& token) const;
    bool isLeftBracket(const std::string& token) const;
    bool isRightBracket(const std::string& token) const;
    std::vector<std::string> postfix(const std::string& expression) const;
    double calculate(std::vector<std::string> postfix) const;

    std::map<std::string, CommandFactory::CommandCreator> operations;
    CommandFactory factory;
};

#endif // DIJKSTRA_H
