#include "evaluate.hpp"
#include "Stack.hpp"
#include <cctype>
#include <sstream>
#include <stdexcept>
#include <cstdlib>
#include <limits>

namespace zinoviev
{
  long long gcd(long long a, long long b)
  {
    while (b != 0)
    {
      long long temp = b;
      b = a % b;
      a = temp;
    }
    return a;
  }

  long long lcm(long long a, long long b)
  {
    a = std::llabs(a);
    b = std::llabs(b);
    long long g = gcd(a, b);
    return g ? (a / g) * b : 0;
  }

  int priority(char oper)
  {
    if (oper == '+' || oper == '-')
      return 1;
    else if (oper == '/' || oper == '*' || oper == '%' || oper == 'l')
      return 2;
    else
      throw std::logic_error("Bad operator");
  }

  long long calculate(long long first, char oper, long long second)
  {
    if (oper == '/')
    {
      if (second == 0)
        throw std::logic_error("Division by zero");
      return first / second;
    }
    else if (oper == '%')
    {
      if (second == 0)
        throw std::logic_error("Division by zero");
      long long rem = first % second;
      if (rem < 0)
        rem += std::llabs(second);

      return rem;
    }
    else if (oper == '+')
    {
      if ((first > 0 && second > 0 && first > std::numeric_limits<long long>::max() - second) ||
          (first < 0 && second < 0 && first < std::numeric_limits<long long>::min() - second))
        throw std::logic_error("Overflow");

      return first + second;
    }
    else if (oper == '-')
    {
      if ((first > 0 && second < 0 && first > std::numeric_limits<long long>::max() + second) ||
          (first < 0 && second > 0 && first < std::numeric_limits<long long>::min() + second))
        throw std::logic_error("Overflow");

      return first - second;
    }
    else if (oper == '*')
    {
      if (first != 0 && second != 0)
      {
        if ((first > 0 && second > 0 && first > std::numeric_limits<long long>::max() / second) ||
            (first > 0 && second < 0 && second < std::numeric_limits<long long>::min() / first) ||
            (first < 0 && second > 0 && first < std::numeric_limits<long long>::min() / second) ||
            (first < 0 && second < 0 && first < std::numeric_limits<long long>::max() / second))
          throw std::logic_error("Overflow");
      }

      return first * second;
    }
    else if (oper == 'l')
    {
      return lcm(first, second);
    }
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
        is_oper = true;

      if (is_oper)
      {
        if (token[0] == '(')
          operators.push(token[0]);

        else if (token[0] == ')')
        {
          while (!operators.empty() && operators.top() != '(')
          {
            if (operands.size() < 2)
              throw std::logic_error("Not enough operands");

            char oper = operators.top();
            operators.pop();

            long long second = operands.top();
            operands.pop();
            long long first = operands.top();
            operands.pop();

            operands.push(calculate(first, oper, second));
          }

          if (!operators.empty() && operators.top() == '(')
            operators.pop();
          else
            throw std::logic_error("Error with operators");
        }
        else if (priority(token[0]) == 1 || priority(token[0]) == 2)
        {
          while (!operators.empty() && operators.top() != '(' &&
                 priority(operators.top()) >= priority(token[0]))
          {
            if (operands.size() < 2)
              throw std::logic_error("Not enough operands");

            char oper = operators.top();
            operators.pop();

            long long second = operands.top();
            operands.pop();
            long long first = operands.top();
            operands.pop();

            operands.push(calculate(first, oper, second));
          }
          operators.push(token[0]);
        }
      }
      else
      {
        operands.push(std::stoll(token));
      }
    }

    while (!operators.empty())
    {
      if (operators.top() == '(')
        throw std::logic_error("Mismatched parentheses");

      if (operands.size() < 2)
        throw std::logic_error("Not enough operands");

      char oper = operators.top();
      operators.pop();
      long long second = operands.top();
      operands.pop();
      long long first = operands.top();
      operands.pop();

      operands.push(calculate(first, oper, second));
    }

    if (operands.size() != 1)
      throw std::logic_error("Bad expression");

    long long res = operands.top();
    operands.pop();
    return res;
  }
}
