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

      Slot(const Slot& other) :
        key(other.key),
        value(other.value),
        occupied(other.occupied)
      {}

      Slot(const Key& k, const Value& v) :
        key(k),
        value(v),
        occupied(true)
      {}

      void swap_slots(Slot& other) noexcept
      {
        std::swap(key, other.key);
        std::swap(value, other.value);
        std::swap(occupied, other.occupied);
      }
    };

    Vector< Slot > slots_;
    size_t buckets_;
    size_t bucket_capacity_;
    size_t overflow_capacity_;
    size_t size_;

    Hash hasher_;
    Equal equal_;

    size_t bucket_index(const Key& k) const;
    size_t bucket_start(size_t bucket_idx) const;

    const Slot* find_slot(const Key& k) const;
    Slot* find_slot(const Key& k);

  public:

    class Iterator;
    class ConstIterator;

    HashTable();
    HashTable(size_t buckets, size_t bucket_capacity, size_t overflow_capacity, const Hash& hash = Hash(), const Equal& equal = Equal());
    HashTable(const HashTable& other);

    Value* find(const Key& k);
    const Value* find(const Key& k) const;
    bool has(const Key& k) const;
    void add(const Key& k, const Value& val);
    void drop(const Key& k, Value& out);
    void rehash(size_t new_buckets);
    void erase(const Key& k) noexcept;

    void swap(HashTable& other) noexcept;

    Iterator begin();
    Iterator end();
    ConstIterator cbegin() const;
    ConstIterator cend() const;
  };

  template < class Key, class Value, class Hash, class Equal >
  HashTable< Key, Value, Hash, Equal >::HashTable() :
    HashTable(16, 4, 16)
  {}

  template < class Key, class Value, class Hash, class Equal >
  HashTable< Key, Value, Hash, Equal >::HashTable(size_t buckets, size_t bucket_capacity,
      size_t overflow_capacity, const Hash& hash, const Equal& equal) :
    buckets_(buckets),
    bucket_capacity_(bucket_capacity),
    overflow_capacity_(overflow_capacity),
    size_(0),
    hasher_(hash),
    equal_(equal)
  {
    size_t total_slots = buckets_ * bucket_capacity_ + overflow_capacity_;
    Vector<Slot> tmp(total_slots);
    slots_.swap(tmp);
  }

  template <class Key, class Value, class Hash, class Equal>
  HashTable< Key, Value, Hash, Equal >::HashTable(const HashTable& other) :
    slots_(other.slots_),
    buckets_(other.buckets_),
    bucket_capacity_(other.bucket_capacity_),
    overflow_capacity_(other.overflow_capacity_),
    size_(other.size_),
    hasher_(other.hasher_),
    equal_(other.equal_)
  {}

  template < class Key, class Value, class Hash, class Equal >
  size_t HashTable< Key, Value, Hash, Equal >::bucket_index(const Key& k) const
  {
    return hasher_(k) % buckets_;
  }

  template < class Key, class Value, class Hash, class Equal >
  size_t HashTable< Key, Value, Hash, Equal >::bucket_start(size_t bucket_idx) const
  {
    return bucket_idx * bucket_capacity_;
  }

  template < class Key, class Value, class Hash, class Equal >
  const typename HashTable< Key, Value, Hash, Equal >::Slot*
    HashTable< Key, Value, Hash, Equal >::find_slot(const Key& k) const
  {
    size_t id = bucket_start(bucket_index(k));
    for (size_t i = id; i < id + bucket_capacity_; ++i)
      if (slots_[i].occupied && equal_(slots_[i].key, k))
        return &slots_[i];

    id = buckets_ * bucket_capacity_;
    for (size_t i = id; i < id + overflow_capacity_; ++i)
      if (slots_[i].occupied && equal_(slots_[i].key, k))
        return &slots_[i];

    return nullptr;
  }

  template < class Key, class Value, class Hash, class Equal >
  typename HashTable< Key, Value, Hash, Equal >::Slot*
    HashTable< Key, Value, Hash, Equal >::find_slot(const Key& k)
  {
    size_t id = bucket_start(bucket_index(k));
    for (size_t i = id; i < id + bucket_capacity_; ++i)
      if (slots_[i].occupied && equal_(slots_[i].key, k))
        return &slots_[i];

    id = buckets_ * bucket_capacity_;
    for (size_t i = id; i < id + overflow_capacity_; ++i)
      if (slots_[i].occupied && equal_(slots_[i].key, k))
        return &slots_[i];

    return nullptr;
  }

  template < class Key, class Value, class Hash, class Equal >
  const Value* HashTable< Key, Value, Hash, Equal >::find(const Key& k) const
  {
    const Slot* s = find_slot(k);
    return s ? &s->value : nullptr;
  }

  template < class Key, class Value, class Hash, class Equal >
  Value* HashTable< Key, Value, Hash, Equal >::find(const Key& k)
  {
    Slot* s = find_slot(k);
    return s ? &s->value : nullptr;
  }

  template < class Key, class Value, class Hash, class Equal >
  bool HashTable< Key, Value, Hash, Equal >::has(const Key& k) const
  {
    return find_slot(k) != nullptr;
  }
}

#endif
