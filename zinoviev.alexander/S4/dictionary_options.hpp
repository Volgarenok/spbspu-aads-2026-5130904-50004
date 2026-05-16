#ifndef DICTIONARY_OPTIONS_HPP
#define DICTIONARY_OPTIONS_HPP

#include <string>
#include "DictionaryEntry.hpp"

namespace zinoviev
{
  int findDict(zinoviev::DictionaryEntry** dicts, size_t count, const std::string& name);
  void addDict(zinoviev::DictionaryEntry**& dicts, size_t& count, const std::string& name);
}

#endif
