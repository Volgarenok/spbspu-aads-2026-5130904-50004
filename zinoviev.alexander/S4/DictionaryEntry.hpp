#ifndef DICTIONARYENTRY_HPP
#define DICTIONARYENTRY_HPP

#include <string>
#include "BSTree.hpp"

namespace zinoviev
{
  class DictionaryEntry
  {
    std::string name_;
    BSTree<int, std::string> tree_;

  public:
    DictionaryEntry(std::string name) :
      name_(name)
    {}


  };
}

#endif
