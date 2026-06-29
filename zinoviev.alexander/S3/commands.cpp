#include "commands.hpp"

zinoviev::Vector<std::string> zinoviev::split(const std::string& line)
{
  Vector<std::string> res;

  if (line.empty())
    return res;

  std::string word;

  for (size_t i = 0; i < line.size(); ++i)
  {
    char ch = line[i];

    if (ch == ' ')
    {
      if (!word.empty())
      {
        res.push_back(word);
        word.clear();
      }
    }
    else
      word.push_back(ch);
  }

  if (!word.empty())
  {
    res.push_back(word);
  }
  return res;
}

std::ostream& zinoviev::print_name_graphs(std::ostream& out, GraphTable::ConstIterator cbegin, GraphTable::ConstIterator cend)
{
  Vector<std::string> names;

  for ( ; cbegin != cend; ++cbegin)
    names.push_back((*cbegin).first);

  zinoviev::sortVector(names);

  for (size_t i = 0; i < names.getSize(); ++i)
    out << names[i] << '\n';

  return out;
}
