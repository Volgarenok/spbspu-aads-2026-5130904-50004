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

    HashTable(Hash count_hash, Equal is_equal, size_t capacity);

    void swap(HashTable & rhs) noexcept;
    void clear();
    void add(const Key & key, const Value & value);
    void remove(const Key & key);
    bool contains(const Key & key) const;
    double load_factor() const;
    void refactor(size_t new_capacity);
    size_t capacity() const;
    size_t size() const;

    private:
      size_t capacity_, size_;
      List< Pair > ** slots_;
      Hash count_hash_;
      Equal is_equal_;
  };

  template< class Key, class Value, class Hash, class Equal >
  HashTable< Key, Value, Hash, Equal >::~HashTable()
  {
    for (size_t i = 0; i < capacity_; ++i) {
      if (slots_[i]) {
        clear(slots_[i]->next, slots_[i]);
        rmfake(slots_[i]);
      }
    }
    delete[] slots_;
  }

  template< class Key, class Value, class Hash, class Equal >
  HashTable< Key, Value, Hash, Equal >::HashTable(const HashTable & rhs):
    capacity_(rhs.capacity_),
    size_(rhs.size_),
    is_equal_(rhs.is_equal_),
    count_hash_(rhs.count_hash_)
  {
    slots_ = new List< Pair > *[capacity_]{nullptr};
    for (size_t i = 0; i < rhs.capacity_; ++i) {
      if (rhs.slots_[i]) {
        slots_[i] = deep_copy(rhs.slots_[i]);
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
    capacity_(rhs.capacity_),
    size_(rhs.size_),
    is_equal_(rhs.is_equal_),
    count_hash_(rhs.count_hash_),
    slots_(rhs.slots_)
  {
    rhs.slots_ = nullptr;
  }

  template< class Key, class Value, class Hash, class Equal >
  HashTable< Key, Value, Hash, Equal > & HashTable< Key, Value, Hash, Equal >::operator=(
      HashTable && rhs) noexcept
  {
    swap(rhs);
    return *this;
  }

  template< class Key, class Value, class Hash, class Equal >
  HashTable< Key, Value, Hash, Equal >::HashTable(Hash count_hash, Equal is_equal, size_t capacity):
    capacity_(capacity),
    size_(0),
    is_equal_(is_equal),
    count_hash_(count_hash),
    slots_(new List< Pair > *[capacity]{nullptr})
  {
  }

  template< class Key, class Value, class Hash, class Equal >
  void HashTable< Key, Value, Hash, Equal >::swap(HashTable & rhs) noexcept
  {
    std::swap(capacity_, rhs.capacity_);
    std::swap(size_, rhs.size_);
    std::swap(is_equal_, rhs.is_equal_);
    std::swap(count_hash_, rhs.count_hash_);
    std::swap(slots_, rhs.slots_);
  }

  template< class Key, class Value, class Hash, class Equal >
  void HashTable< Key, Value, Hash, Equal >::clear()
  {
    for (size_t i = 0; i < capacity_; ++i) {
      if (slots_[i]) {
        clear(slots_[i]->next, slots_[i]);
        rmfake(slots_[i]);
      }
    }
  }

  template< class Key, class Value, class Hash, class Equal >
  void HashTable< Key, Value, Hash, Equal >::add(const Key & key, const Value & value)
  {
    Hash hash = count_hash(key);
    size_t index = hash % capacity_;
    List< Pair > ** tail = nullptr;
    if (slots_[index]) {
      List< Pair > * fake = slots_[index];
      List< Pair > * current = fake;
      while (current->next != fake) {
        current = current->next;
        if (is_equal(current->data.first, key)) {
          return;
        }
      }
      tail = current;
    } else {
      slots_[index] = fake< Pair >();
      tail = slots_[index];
    }
    insert_after(tail, std::pair< Key, Value >(key, value));
    ++size_;
  }

  template< class Key, class Value, class Hash, class Equal >
  void HashTable< Key, Value, Hash, Equal >::remove(const Key & key)
  {
    Hash hash = count_hash(key);
    size_t index = hash % capacity_;
    if (!slots_[index]) {
      return;
    }
    List< Pair > * fake = slots_[index];
    List< Pair > * current = fake;
    while (current->next != fake) {
      if (is_equal(current->next->data.first, key)) {
        erase_after(current->next);
        --size_;
        break;
      }
      current = current->next;
    }
    if (fake->next == fake) {
      rmfake(slots_[index]);
      slots_[index] = nullptr;
    }
  }

  template< class Key, class Value, class Hash, class Equal >
  bool HashTable< Key, Value, Hash, Equal >::contains(const Key & key) const
  {
    Hash hash = count_hash(key);
    size_t index = hash % capacity_;
    if (slots_[index]) {
      List< Pair > * fake = slots_[index];
      List< Pair > * current = fake;
      while (current != fake) {
        if (is_equal(current->data.first, key)) {
          return true;
        }
        current = current->next;
      }
    }
    return false;
  }

  template< class Key, class Value, class Hash, class Equal >
  double HashTable< Key, Value, Hash, Equal >::load_factor() const
  {
    double s = size_;
    return s / capacity_;
  }

  template< class Key, class Value, class Hash, class Equal >
  size_t HashTable< Key, Value, Hash, Equal >::capacity() const
  {
    return capacity_;
  }

  template< class Key, class Value, class Hash, class Equal >
  size_t HashTable< Key, Value, Hash, Equal >::size() const
  {
    return size_;
  }
}
#endif
