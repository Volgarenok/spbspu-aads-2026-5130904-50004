#include "expression_processor.hpp"
#include <stdexcept>
#include <limits>
#include <cctype>

int chadin::getPriority(char op)
{
  if (op == '*' || op == '/' || op == '%') return 3;
  if (op == '+' || op == '-') return 2;
  if (op == '|') return 1;
  return 0;
}

long long chadin::performOp(char op, long long a, long long b)
{
  const long long maxV = std::numeric_limits< long long >::max();
  const long long minV = std::numeric_limits< long long >::min();

  if (op == '+')
  {
    if ((b > 0 && a > maxV - b) || (b < 0 && a < minV - b)) throw std::overflow_error("Overflow");
    return a + b;
  }
  if (op == '-')
  {
    if ((b < 0 && a > maxV + b) || (b > 0 && a < minV + b)) throw std::overflow_error("Overflow");
    return a - b;
  }
  if (op == '*')
  {
    if (a != 0 && (b > maxV / a || b < minV / a)) throw std::overflow_error("Overflow");
    return a * b;
  }
  if (op == '/')
  {
    if (b == 0) throw std::runtime_error("Div by zero");
    return a / b;
  }
  if (op == '%')
  {
    if (b == 0) throw std::runtime_error("Div by zero");
    return (a % b + b) % b;
  }
  if (op == '|') return a | b;
  throw std::invalid_argument("Op error");
}
