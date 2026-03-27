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

}
