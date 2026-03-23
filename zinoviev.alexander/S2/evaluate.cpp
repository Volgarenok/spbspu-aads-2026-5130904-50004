#include "evaluate.hpp"
#include "Stack.hpp"

namespace zinoviev
{
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
