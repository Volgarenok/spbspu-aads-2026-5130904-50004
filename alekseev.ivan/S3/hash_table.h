#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "../common/List.h"
#include <cstddef>

namespace alekseev {
  template< class Key, class Value, class Hash, class Equal >
  struct HashTable {
    using Pair = std::pair< Key, Value >;
    ~HashTable();
    HashTable(const HashTable & rhs);
    HashTable & operator=(const HashTable & rhs);
    HashTable(HashTable && rhs) noexcept;
    HashTable & operator=(HashTable && rhs) noexcept;

    void swap(HashTable & rhs) noexcept;
    void clear();

    private:
      size_t capacity;
      List< Pair > ** slots;
      Hash count_hash;
      Equal is_equal;
  };

  template< class Key, class Value, class Hash, class Equal >
  HashTable< Key, Value, Hash, Equal >::~HashTable()
  {
    for (size_t i = 0; i < capacity; ++i) {
      if (slots[i]) {
        clear(slots[i]->next, slots[i]);
        rmfake(slots[i]);
      }
    }
    delete[] slots;
  }

  template< class Key, class Value, class Hash, class Equal >
  HashTable< Key, Value, Hash, Equal >::HashTable(const HashTable & rhs):
    capacity(rhs.capacity),
    is_equal(rhs.is_equal),
    count_hash(rhs.count_hash)
  {
    slots = new List< Pair > *[capacity]{nullptr};
    for (size_t i = 0; i < rhs.capacity; ++i) {
      if (rhs.slots[i]) {
        slots[i] = deep_copy(rhs.slots[i]);
      }
    }
  }

  template< class Key, class Value, class Hash, class Equal >
  HashTable< Key, Value, Hash, Equal > & HashTable< Key, Value, Hash, Equal >::operator=(
      const HashTable & rhs)
  {
    HashTable< Key, Value, Hash, Equal > temp(rhs);
    swap(temp);
    return *this;
  }

  template< class Key, class Value, class Hash, class Equal >
  HashTable< Key, Value, Hash, Equal >::HashTable(HashTable && rhs) noexcept:
    capacity(rhs.capacity),
    is_equal(rhs.is_equal),
    count_hash(rhs.count_hash),
    slots(rhs.slots)
  {
    rhs.slots = nullptr;
  }

  template< class Key, class Value, class Hash, class Equal >
  HashTable< Key, Value, Hash, Equal > & HashTable< Key, Value, Hash, Equal >::operator=(
      HashTable && rhs) noexcept
  {
    swap(rhs);
    return *this;
  }

  template< class Key, class Value, class Hash, class Equal >
  void HashTable< Key, Value, Hash, Equal >::swap(HashTable & rhs) noexcept
  {
    std::swap(capacity, rhs.capacity);
    std::swap(is_equal, rhs.is_equal);
    std::swap(count_hash, rhs.count_hash);
    std::swap(slots, rhs.slots);
  }

  template< class Key, class Value, class Hash, class Equal >
  void HashTable<Key, Value, Hash, Equal>::clear()
  {
    for (size_t i = 0; i < capacity; ++i) {
      if (slots[i]) {
        clear(slots[i]->next, slots[i]);
        rmfake(slots[i]);
      }
    }
  }
}
#endif
