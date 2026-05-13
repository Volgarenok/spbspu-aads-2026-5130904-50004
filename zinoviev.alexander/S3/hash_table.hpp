#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <cstddef>
#include <utility>
#include <stdexcept>
#include <string>
#include "vector.hpp"

namespace zinoviev
{
  template< class Key, class Value, class Hash, class Equal >
  class HashTable
  {
    struct Slot
    {
      Key key;
      Value value;
      bool occupied;

      Slot() :
        occupied(false),
        key(),
        value()
      {}
    };

    Vector< Slot > slots_;
    size_t buckets_;
    size_t bucket_capacity_;
    size_t overflow_capacity_;
    size_t size_;

    Hash hasher_;
    Equal equal_;

  public:

    class Iterator;
    class ConstIterator;
  }
}
#endif
