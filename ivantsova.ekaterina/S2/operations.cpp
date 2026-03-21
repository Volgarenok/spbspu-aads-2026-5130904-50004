#include "operations.hpp"

int ivantsova::getPriority(const std::string& op) {}
bool ivantsova::isOperator(const std::string& token) {}
bool ivantsova::isNumber(const std::string& token) {}
long long ivantsova::useOperation(long long a, long long b, const std::string& line) {}
ivantsova::Queue< std::string > ivantsova::convertToPostfix(const std::string& line) {}
long long ivantsova::calculatePostfix(Queue< std::string >& postfix) {}
long long ivantsova::calculateExpression(const std::string& line) {}
