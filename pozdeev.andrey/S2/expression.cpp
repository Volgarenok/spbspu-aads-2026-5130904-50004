#include "expression.hpp"

#include <cstdlib>

namespace pozdeev {

Token::Token()
    : type_(TokenType::Number)
    , value_()
    , numberValue_(0)
{
}

int getPriority(const std::string &op)
{
    if (op == "*" || op == "/" || op == "%") {
        return 3;
    }
    if (op == "+" || op == "-") {
        return 2;
    }
    if (op == "<<") {
        return 1;
    }
    return 0;
}

bool isOperator(const std::string &token)
{
    return token == "+" || token == "-" || token == "*" || token == "/"
        || token == "%" || token == "<<";
}

long long applyOperator(long long left, long long right, const std::string &op)
{
    if (op == "+") {
        return left + right;
    }
    if (op == "-") {
        return left - right;
    }
    if (op == "*") {
        return left * right;
    }
    if (op == "/") {
        if (right == 0) {
            throw std::runtime_error("Division by zero");
        }
        return left / right;
    }
    if (op == "%") {
        if (right == 0) {
            throw std::runtime_error("Modulo by zero");
        }
        return left % right;
    }
    if (op == "<<") {
        if (right < 0) {
            throw std::runtime_error("Negative shift count");
        }
        return left << right;
    }
    throw std::runtime_error("Unknown operator");
}

Token parseToken(const std::string &str)
{
    Token token;
    token.value_ = str;

    if (str == "(") {
        token.type_ = TokenType::LeftParen;
    } else if (str == ")") {
        token.type_ = TokenType::RightParen;
    } else if (isOperator(str)) {
        token.type_ = TokenType::Operator;
    } else {
        token.type_ = TokenType::Number;
        try {
            token.numberValue_ = std::stoll(str);
        } catch (...) {
            throw std::runtime_error("Invalid number: " + str);
        }
    }
    return token;
}

}
