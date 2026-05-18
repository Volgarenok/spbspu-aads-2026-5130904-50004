#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include "stack.hpp"
#include "queue.hpp"

namespace ali
{
  bool is_operation(const std::string & token)
  {
    return token == "+" || token == "-" || token == "*" ||
           token == "/" || token == "%" || token == "^";
  }

  int priority(const std::string & op)
  {
    if (op == "*" || op == "/" || op == "%")
    {
      return 3;
    }
    if (op == "+" || op == "-")
    {
      return 2;
    }
    if (op == "^")
    {
      return 1;
    }
    return 0;
  }

  long long to_number(const std::string & token)
  {
    if (token.empty())
    {
      throw std::logic_error("bad number");
    }

    long long result = 0;
    bool negative = false;
    std::size_t i = 0;

    if (token[0] == '-')
    {
      negative = true;
      i = 1;
    }

    if (i == token.size())
    {
      throw std::logic_error("bad number");
    }

    for (; i < token.size(); ++i)
    {
      if (token[i] < '0' || token[i] > '9')
      {
        throw std::logic_error("bad number");
      }

      result = result * 10 + (token[i] - '0');
    }

    if (negative)
    {
      result = -result;
    }

    return result;
  }

  long long apply_operation(long long left, long long right, const std::string & op)
  {
    if (op == "+")
    {
      return left + right;
    }
    if (op == "-")
    {
      return left - right;
    }
    if (op == "*")
    {
      return left * right;
    }
    if (op == "/")
    {
      if (right == 0)
      {
        throw std::logic_error("division by zero");
      }
      return left / right;
    }
    if (op == "%")
    {
      if (right == 0)
      {
        throw std::logic_error("division by zero");
      }
      return left % right;
    }
    if (op == "^")
    {
      return left ^ right;
    }

    throw std::logic_error("bad operation");
  }

  Queue< std::string > make_postfix(const std::string & line)
  {
    Queue< std::string > output;
    Stack< std::string > operations;

    std::size_t pos = 0;

    while (pos < line.size())
    {
      std::string token;

      while (pos < line.size() && line[pos] == ' ')
      {
        ++pos;
      }

      while (pos < line.size() && line[pos] != ' ')
      {
        token += line[pos];
        ++pos;
      }

      if (token.empty())
      {
        continue;
      }

      if (token == "(")
      {
        operations.push(token);
      }
      else if (token == ")")
      {
        while (!operations.empty() && operations.top() != "(")
        {
          output.push(operations.top());
          operations.drop();
        }

        if (operations.empty())
        {
          throw std::logic_error("bad expression");
        }

        operations.drop();
      }
      else if (is_operation(token))
      {
        while (!operations.empty() &&
               is_operation(operations.top()) &&
               priority(operations.top()) >= priority(token))
        {
          output.push(operations.top());
          operations.drop();
        }

        operations.push(token);
      }
      else
      {
        output.push(token);
      }
    }

    while (!operations.empty())
    {
      if (operations.top() == "(")
      {
        throw std::logic_error("bad expression");
      }

      output.push(operations.top());
      operations.drop();
    }

    return output;
  }

  long long calculate_postfix(Queue< std::string > postfix)
  {
    Stack< long long > values;

    while (!postfix.empty())
    {
      std::string token = postfix.front();
      postfix.drop();

      if (is_operation(token))
      {
        if (values.empty())
        {
          throw std::logic_error("bad expression");
        }

        long long right = values.top();
        values.drop();

        if (values.empty())
        {
          throw std::logic_error("bad expression");
        }

        long long left = values.top();
        values.drop();

        values.push(apply_operation(left, right, token));
      }
      else
      {
        values.push(to_number(token));
      }
    }

    if (values.empty())
    {
      throw std::logic_error("bad expression");
    }

    long long result = values.top();
    values.drop();

    if (!values.empty())
    {
      throw std::logic_error("bad expression");
    }

    return result;
  }

  void process_input(std::istream & input)
  {
    Stack< long long > results;
    std::string line;

    while (std::getline(input, line))
    {
      if (line.empty())
      {
        continue;
      }

      Queue< std::string > postfix = make_postfix(line);
      results.push(calculate_postfix(postfix));
    }

    bool first = true;

    while (!results.empty())
    {
      if (!first)
      {
        std::cout << ' ';
      }

      std::cout << results.top();
      results.drop();
      first = false;
    }

    std::cout << '\n';
  }
}

int main(int argc, char ** argv)
{
  try
  {
    if (argc > 2)
    {
      std::cerr << "error\n";
      return 1;
    }

    if (argc == 2)
    {
      std::ifstream input(argv[1]);

      if (!input)
      {
        std::cerr << "error\n";
        return 1;
      }

      ali::process_input(input);
    }
    else
    {
      ali::process_input(std::cin);
    }
  }
  catch (const std::exception &)
  {
    std::cerr << "error\n";
    return 1;
  }

  return 0;
}
