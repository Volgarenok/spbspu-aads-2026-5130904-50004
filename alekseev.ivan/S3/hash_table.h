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

    private:
      size_t capacity;
      List< T > ** slots;
      Hash count_hash;
      Equal is_equal;
  };

  template< class T, class Hash, class Equal >
  HashTable<T, Hash, Equal>::~HashTable()
  {
    for (size_t i = 0; i < capacity; ++i) {
      if (slots[i]) {
        clear(slots[i], slots[i]);
        rmfake(slots[i]);
      }
    }
    delete[] slots;
  }
}
#endif
