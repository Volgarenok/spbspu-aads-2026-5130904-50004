#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP
#include "slist.hpp"
#include "xxhash.hpp"
#include <cstddef>
#include <functional>
#include <stdexcept>
#include <string>
#include <utility>

namespace alberto {

struct xx_hash {
  size_t operator()(const std::string& key) const
  {
    return static_cast< size_t >(
        xxhash_impl::xxhash32(key.data(), key.size()));
  }

  template< class T >
  size_t operator()(const T& key) const
  {
    return static_cast< size_t >(
        xxhash_impl::xxhash32(&key, sizeof(T)));
  }
};

struct pair_hash {
  size_t operator()(const std::pair< std::string, std::string >& p) const
  {
    const size_t h1 = xxhash_impl::xxhash32(
        p.first.data(), p.first.size());
    const size_t h2 = xxhash_impl::xxhash32(
        p.second.data(), p.second.size(), 0x9747b28cu);
    return h1 ^ (h2 * 2654435761ull);
  }
};

struct pair_equal {
  bool operator()(const std::pair< std::string, std::string >& a,
                  const std::pair< std::string, std::string >& b) const
  {
    return a == b;
  }
};
