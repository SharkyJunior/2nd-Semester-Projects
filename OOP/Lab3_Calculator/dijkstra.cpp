#include "dijkstra.h"

#include <cctype>
#include <stack>

#include "commands.h"
#include "exceptions.h"


Dijkstra::Dijkstra() {
    operations["+"] = &CommandFactory::createPlus;
    operations["-"] = &CommandFactory::createMinus;
    operations["*"] = &CommandFactory::createMultiply;
    operations["/"] = &CommandFactory::createDivide;
}

std::vector<std::string> Dijkstra::tokenize(const std::string& expression) const {
    std::vector<std::string> tokens;
    std::string currentToken;
    bool prevOperatorOrBracket = true;

    for (size_t i = 0; i < expression.size(); ++i) {
        char c = expression[i];

        if ((c == '-') && (prevOperatorOrBracket || (i == 0) || (i > 0 && expression[i-1] == '('))) {
            if (!currentToken.empty()) {
                tokens.push_back(currentToken);
                currentToken.clear();
            }
            currentToken += c;
        }
        else if (isOperator(std::string(1, c)) || c == '(' || c == ')') {
            if (!currentToken.empty()) {
                tokens.push_back(currentToken);
                currentToken.clear();
            }
            tokens.push_back(std::string(1, c));
            prevOperatorOrBracket = (c != ')');
        }
        else {
            currentToken += c;
            prevOperatorOrBracket = false;
        }
    }

    if (!currentToken.empty()) {
        tokens.push_back(currentToken);
    }

    return tokens;
}

std::vector<std::string> Dijkstra::postfix(const std::string& expression) const {
    std::vector<std::string> tokens = tokenize(expression);
    std::stack<std::string> operatorStack;
    std::vector<std::string> output;

    for (const auto& token : tokens) {
        if (isNumber(token)) {
            output.push_back(token);
        }
        else if (isFunction(token) || isLeftBracket(token)) {
            operatorStack.push(token);
        }
        else if (isOperator(token)) {
            while (!operatorStack.empty()) {
                const std::string& top = operatorStack.top();

                if (isOperator(top)) {
                    Command* cmd1 = (factory.*operations.at(token))(0, 0);
                    Command* cmd2 = (factory.*operations.at(top))(0, 0);

                    if (cmd1->priority() <= cmd2->priority()) {
                        output.push_back(top);
                        operatorStack.pop();
                        delete cmd1;
                        delete cmd2;
                        continue;
                    }
                    delete cmd1;
                    delete cmd2;
                }
                else if (isFunction(top)) {
                    output.push_back(top);
                    operatorStack.pop();
                    continue;
                }
                break;
            }

            operatorStack.push(token);
        }
        else if (isRightBracket(token)) {
            while (!operatorStack.empty() && !isLeftBracket(operatorStack.top())) {
                output.push_back(operatorStack.top());
                operatorStack.pop();
            }

            if (operatorStack.empty()) {
                throw InvalidExpression("Mismatched parentheses");
            }

            operatorStack.pop();

            if (!operatorStack.empty() && isFunction(operatorStack.top())) {
                output.push_back(operatorStack.top());
                operatorStack.pop();
            }
        }
    }

    while (!operatorStack.empty()) {
        if (isLeftBracket(operatorStack.top())) {
            throw InvalidExpression("Mismatched parentheses");
        }
        output.push_back(operatorStack.top());
        operatorStack.pop();
    }

    return output;
}

double Dijkstra::calculate(std::vector<std::string> postfix) const {
    std::stack<double> calcStack;

    for (const auto& token : postfix) {
        if (isNumber(token)) {
            calcStack.push(std::stod(token));
        }
        else if (operations.count(token)) {
            auto operationCreator = operations.at(token);

            if (isFunction(token)) {
                if (calcStack.empty())
                    throw InvalidExpression("Not enough operands");
                double a = calcStack.top();
                calcStack.pop();

                Command* cmd = (factory.*operationCreator)(a, 0);
                double result = cmd->execute();
                delete cmd;
                calcStack.push(result);
            }
            else {
                if (calcStack.size() < 2)
                    throw InvalidExpression("Not enough operands");
                double b = calcStack.top();
                calcStack.pop();
                double a = calcStack.top();
                calcStack.pop();

                Command* cmd = (factory.*operationCreator)(a, b);
                double result = cmd->execute();
                delete cmd;
                calcStack.push(result);
            }
        }
    }

    if (calcStack.size() != 1) {
        throw InvalidExpression();
    }

    return calcStack.top();
}

double Dijkstra::evaluate(const std::string& expression) const {
    return calculate(postfix(expression));
}

bool Dijkstra::isNumber(const std::string& token) const {
    if (token.empty())
        return false;

    size_t start = 0;
    if (token[0] == '-') {
        if (token.size() == 1)
            return false;
        start = 1;
    }

    bool hasPeriod = false;
    for (size_t i = start; i < token.size(); ++i) {
        if (token[i] == '.') {
            if (hasPeriod)
                return false;
            hasPeriod = true;
        }
        else if (!isdigit(token[i])) {
            return false;
        }
    }

    return true;
}

bool Dijkstra::isOperator(const std::string& token) const {
    return operations.count(token) && !(factory.*operations.at(token))(0, 0)->isFunction();
}

bool Dijkstra::isFunction(const std::string& token) const {
    return operations.count(token) && (factory.*operations.at(token))(0, 0)->isFunction();
}

bool Dijkstra::isLeftBracket(const std::string& token) const {
    return token == "(";
}

bool Dijkstra::isRightBracket(const std::string& token) const {
    return token == ")";
}

