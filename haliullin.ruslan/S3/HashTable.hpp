#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include "vector.hpp"
#include <cstddef>
#include <stdexcept>
#include <utility>

namespace haliullin
{
  template< class Key, class Value, class Hash, class Equal >
  class HashTable
  {
  public:
    ~HashTable() = default;
    HashTable(size_t capacity = 16);

    HashTable(const HashTable& other);
    HashTable(HashTable&& other);

    HashTable& operator=(const HashTable& other);
    HashTable& operator=(HashTable&& other) noexcept;

    void swap(HashTable& other) noexcept;

    void add(const Key& k, const Value& v);
    Value drop(const Key& k);
    bool has(const Key& k) const;
    Value& get(const Key& k);
    const Value& get(const Key& k) const;
    void rehash(size_t newSize);

    size_t getSize() const noexcept;
    size_t getCapacity() const noexcept;

  private:
    using Slot = std::pair< std::pair<Key, Value>, char >;

    Vector< Slot > slots_;
    size_t size_;
    Hash hasher_;
    Equal equal_;

    size_t findIndex(const Key& k) const;
    size_t probe(size_t hash, size_t i) const noexcept;
  };
}

#endif
