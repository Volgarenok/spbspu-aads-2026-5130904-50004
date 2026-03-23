#include "evaluate.hpp"
#include "Stack.hpp"

namespace zinoviev
{
  int priority(char oper)
  {
    if (oper == '+' || oper == '-')
      return 1;
    else if (oper == '/' || oper == '*' || oper == '%')
      return 2;
    else
      throw std::logic_error("Bad operator");
  }

  long long calculate(long long first, char oper, long long second)
  {
    if (oper == '/')
    {
      if (second == 0)
        throw std::logic_error("Dividing by 0");
      return first / second;
    }
    else if (oper == '%')
    {
      if (second == 0)
        throw std::logic_error("Dividing by 0");
      return first % second;
    }
    else if (oper == '+')
      return first + second;
    else if (oper == '-')
      return first - second;
    else if (oper == '*')
      return first * second;
    else if (oper == 'l')
      return lcm(first, second);
    else
      throw std::logic_error("Unknown operation");
  }

  long long evaluate(std::string& expression)
  {
    Stack<long long> operands;
    Stack<char> operators;
    std::string token;

    std::istringstream in(expression);

    while (in >> token)
    {
      bool is_oper = false;

      if (!isdigit(token[0]) && token.size() == 1)
        is_oper = true;
      else if (token == "lcm")
      {
        is_oper = true;
      }

      if (is_oper)
      {}
      else
      {
        operands.push(std::stoll(token));
      }
    }
  }
}
