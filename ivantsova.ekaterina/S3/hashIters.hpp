#ifndef HASH_ITERS_HPP
#define HASH_ITERS_HPP

#include "hashTable.hpp"

namespace ivantsova {

  template< typename Key, typename Value, typename Hash, typename Equal >
  class HashIter {
    friend class HashTable< Key, Value, Hash, Equal >;

  public:
    HashIter();
    HashIter(HashTable< Key, Value, Hash, Equal >* table, size_t bucket_index, typename List<std::pair<Key, Value>>::Iterator it);

    HashIter& operator++();
    bool operator!=(const HashIter& other) const;
    std::pair<Key, Value>& operator*();
    std::pair<Key, Value>* operator->();

  private:
    HashTable< Key, Value, Hash, Equal >* table_;
    size_t bucket_index_;
    typename List<std::pair<Key, Value>>::Iterator it_;
  };

  template< typename Key, typename Value, typename Hash, typename Equal >
  class HashConstIter {
  friend class HashTable< Key, Value, Hash, Equal >;

  public:
    HashConstIter();
    HashConstIter(const HashTable< Key, Value, Hash, Equal >* table, size_t bucket_index,
        typename List<std::pair<Key, Value>>::ConstIterator it);

    HashConstIter& operator++();
    bool operator!=(const HashConstIter& other) const;
    const std::pair<Key, Value>& operator*() const;
    const std::pair<Key, Value>* operator->() const;

  private:
    const HashTable< Key, Value, Hash, Equal >* table_;
    size_t bucket_index_;
    typename List<std::pair<Key, Value>>::ConstIterator it_;
  };
}

#endif
