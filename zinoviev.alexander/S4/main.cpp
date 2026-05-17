#include <iostream>
#include <fstream>
#include <string>
#include "BSTree.hpp"
#include "DictionaryEntry.hpp"
#include "dictionary_options.hpp"

int main(int argc, const char** argv)
{
  if (argc < 2)
  {
    std::cout << "No filename provided\n";
    return 1;
  }

  std::ifstream file(argv[1]);

  if (!file.is_open())
  {
    std::cout << "Can't open file\n";
    return 1;
  }

  zinoviev::DictionaryEntry** dictionaries = nullptr;
  size_t dictCount = 0;

  std::string line;
  while (std::getline(file, line))
  {
    if (line.empty())
      continue;

    size_t pos = 0;
    size_t size = line.size();
    while (pos < size && line[pos] == ' ')
      ++pos;

    if (pos == size)
      continue;

    std::string name_dict;
    while (pos < size && line[pos] != ' ')
    {
      name_dict += line[pos];
      ++pos;
    }

    size_t id = zinoviev::findDict(dictionaries, dictCount, name_dict);
    if (id == dictCount)
      zinoviev::addDict(dictionaries, dictCount, name_dict);

    while (pos < size)
    {
      while (pos < size && line[pos] == ' ')
        ++pos;

      std::string key_str;
      while (pos < size && line[pos] != ' ')
      {
        key_str += line[pos];
        ++pos;
      }

      unsigned long long key = 0.;
      try
      {
        key = std::stoull(key_str);
      }
      catch (...)
      {
        continue;
      }

      while (pos < size && line[pos] == ' ')
        ++pos;

      std::string val_str;
      while (pos < size && line[pos] != ' ')
      {
        val_str += line[pos];
        ++pos;
      }

      dictionaries[id]->getTree().push(key, val_str);
    }
  }
}
