#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "../common/List.h"
#include <cstddef>

namespace alekseev {
  template< class T, class Hash, class Equal >
  struct HashTable {
    ~HashTable();
    HashTable(const HashTable & rhs);
    HashTable & operator=(const HashTable & rhs);
    HashTable(HashTable && rhs);
    HashTable & operator=(HashTable && rhs);

    void swap(HashTable & rhs);

    private:
      size_t capacity;
      List< T > ** slots;
      Hash count_hash;
      Equal is_equal;
  };

  template< class T, class Hash, class Equal >
  HashTable< T, Hash, Equal >::~HashTable()
  {
    for (size_t i = 0; i < capacity; ++i) {
      if (slots[i]) {
        clear(slots[i]->next, slots[i]);
        rmfake(slots[i]);
      }
    }
    delete[] slots;
  }

  template< class T, class Hash, class Equal >
  HashTable< T, Hash, Equal >::HashTable(const HashTable & rhs):
    capacity(rhs.capacity),
    is_equal(rhs.is_equal),
    count_hash(rhs.count_hash)
  {
    slots = new List< T > *[capacity]{nullptr};
    for (size_t i = 0; i < rhs.capacity; ++i) {
      if (rhs.slots[i]) {
        slots[i] = deep_copy(rhs.slots[i]);
      }
    }
  }

  template< class T, class Hash, class Equal >
  HashTable< T, Hash, Equal > & HashTable< T, Hash, Equal >::operator=(const HashTable & rhs)
  {
    HashTable< T, Hash, Equal > temp(rhs);
    swap(temp);
  }

  template< class T, class Hash, class Equal >
  void HashTable<T, Hash, Equal>::swap(HashTable & rhs)
  {
    std::swap(capacity, rhs.capacity);
    std::swap(is_equal, rhs.is_equal);
    std::swap(count_hash, rhs.count_hash);
    std::swap(slots, rhs.slots);
  }
}
#endif
