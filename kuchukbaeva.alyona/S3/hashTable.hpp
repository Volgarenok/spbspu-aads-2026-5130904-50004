#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP
#include "vector.hpp"
#include "../common/list.hpp"
#include <utility>
#include <stdexcept>
#include <string>
#include <boost/hash2/siphash.hpp>
#include <boost/hash2/hash_append.hpp>

namespace kuchukbaeva {

  template< class T >
  struct SipHashFunctor {
    std::size_t operator()(const T& val) const
    {
      boost::hash2::siphash_64 hasher;
      boost::hash2::hash_append(hasher, {}, val);
      return hasher.result();
    }
  };

  template< class T >
  struct EqualFunctor {
    bool operator()(const T& lhs, const T& rhs) const
    {
      return lhs == rhs;
    }
  };
}
