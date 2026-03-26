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
