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

template< class Key, class Value, class Hash, class Equal >
haliullin::HashTable< Key, Value, Hash, Equal >::HashTable(size_t capacity):
  slots_(capacity),
  size_(0),
  hasher_()
  equal_()
{
  for (size_t i = 0; i < slots_.getSize(); ++i)
  {
    slots_[i].second = 'e';
  }
}

template< class Key, class Value, class Hash, class Equal >
haliullin::HashTable< Key, Value, Hash, Equal >::HashTable(const HashTable& other):
  slots_(other.slots_),
  size_(other.size_),
  hasher_(other.hasher_),
  equal_(other.equal_)
{}

template< class Key, class Value, class Hash, class Equal >
void haliullin::HashTable< Key, Value, Hash, Equal >::swap(HashTable& other) noexcept
{
  std::swap(slots_, other.slots_);
  std::swap(size_, other.size_);
  std::swap(hasher_, other.hasher_);
  std::swap(equal_, other.equal_);
}

