#ifndef SIPHASH_HPP
#define SIPHASH_HPP

#include <string>
#include <cstddef>

namespace ali
{
  struct SipHash
  {
    std::size_t operator()(const std::string & key) const
    {
      std::size_t hash = 1469598103934665603ull;

      for (char c: key)
      {
        hash ^= static_cast< std::size_t >(c);
        hash *= 1099511628211ull;
      }

      return hash;
    }
  };
}

#endif
