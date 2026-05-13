#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP
#include "vector.hpp"
#include "../common/list.hpp"
#include <utility>
#include <stdexcept>
#include <string>
#include <boost/hash2/siphash.hpp>
#include <boost/hash2/hash_append.hpp>

namespace kuchukbaeva {

  template< class T >
  struct SipHashFunctor {
    std::size_t operator()(const T& val) const
    {
      boost::hash2::siphash_64 hasher;
      boost::hash2::hash_append(hasher, {}, val);
      return hasher.result();
    }
  };

  template< class T >
  struct EqualFunctor {
    bool operator()(const T& lhs, const T& rhs) const
    {
      return lhs == rhs;
    }
  };

  template< class Key, class Value, class Hash = SipHashFunctor< Key >, class Equal = EqualFunctor< Key > >
  class HTIter;

  template< class Key, class Value, class Hash = SipHashFunctor< Key >, class Equal = EqualFunctor< Key > >
  class HashTable {
  public:
    explicit HashTable(size_t slots = 16);
    HashTable(const HashTable& other);
    HashTable(HashTable&& other) noexcept;
    ~HashTable() = default;

    HashTable& operator=(const HashTable& other);
    HashTable& operator=(HashTable&& other) noexcept;

    void swap(HashTable& other) noexcept;

    void add(const Key& k, const Value& v);
    bool drop(const Key& k);
    bool has(const Key& k) const;
    Value* find(const Key& k);
    void rehash(size_t slots);

    size_t getSize() const;

    HTIter< Key, Value, Hash, Equal > begin();
    HTIter< Key, Value, Hash, Equal > end();

  private:
    friend class HTIter< Key, Value, Hash, Equal >;
    Vector< List< std::pair< Key, Value > > > mass_;
    size_t size_;
    Hash hashFn_;
    Equal equalFn_;
  };

  template< class Key, class Value, class Hash, class Equal >
  class HTIter {
  public:
    HTIter(Vector< List< std::pair< Key, Value > > >* mass, size_t idx, LIter< std::pair< Key, Value > > listIt) :
      mass_(mass),
      massIdx_(idx),
      listIt_(listIt)
    {
    }

    std::pair< Key, Value >& operator*()
    {
      return *listIt_;
    }

    std::pair< Key, Value >* operator->()
    {
      return &(*listIt_);
    }

    HTIter& operator++()
    {
      ++listIt_;
      if (listIt_ == (*mass_)[massIdx_].end()) {
        ++massIdx_;
        while (massIdx_ < mass_->getSize() && (*mass_)[massIdx_].isEmpty()) {
          ++massIdx_;
        }
        if (massIdx_ < mass_->getSize()) {
          listIt_ = (*mass_)[massIdx_].begin();
        } else {
          listIt_ = LIter< std::pair< Key, Value > >();
        }
      }
      return *this;
    }

    bool operator!=(const HTIter& other) const
    {
      return massIdx_ != other.massIdx_ || listIt_ != other.listIt_;
    }

    bool operator==(const HTIter& other) const
    {
      return !(*this != other);
    }

  private:
    Vector< List< std::pair< Key, Value > > >* mass_;
    size_t massIdx_;
    LIter< std::pair< Key, Value > > listIt_;
  };
  template< class Key, class Value, class Hash, class Equal >
  HashTable< Key, Value, Hash, Equal >::HashTable(size_t slots) :
    mass_(slots, List< std::pair< Key, Value > >()),
    size_(0),
    hashFn_(),
    equalFn_()
  {
  }

  template< class Key, class Value, class Hash, class Equal >
  HashTable< Key, Value, Hash, Equal >::HashTable(const HashTable& other) :
    mass_(other.mass_.getSize(), List< std::pair< Key, Value > >()),
    size_(0),
    hashFn_(other.hashFn_),
    equalFn_(other.equalFn_)
  {
    for (size_t i = 0; i < other.mass_.getSize(); ++i) {
      for (auto it = other.mass_[i].cbegin(); it != other.mass_[i].cend(); ++it) {
        this->add(it->first, it->second);
      }
    }
  }

  template< class Key, class Value, class Hash, class Equal >
  HashTable< Key, Value, Hash, Equal >::HashTable(HashTable&& other) noexcept :
    HashTable(1)
  {
    swap(other);
  }

  template< class Key, class Value, class Hash, class Equal >
  HashTable< Key, Value, Hash, Equal >& HashTable< Key, Value, Hash, Equal >::operator=(const HashTable& other)
  {
    if (this != &other) {
      HashTable tmp(other);
      swap(tmp);
    }
    return *this;
  }

  template< class Key, class Value, class Hash, class Equal >
  HashTable< Key, Value, Hash, Equal >& HashTable< Key, Value, Hash, Equal >::operator=(HashTable&& other) noexcept
  {
    if (this != &other) {
      HashTable tmp(std::move(other));
      swap(tmp);
    }
    return *this;
  }

  template< class Key, class Value, class Hash, class Equal >
  void HashTable< Key, Value, Hash, Equal >::swap(HashTable& other) noexcept
  {
    mass_.swap(other.mass_);
    std::swap(size_, other.size_);
  }

  template< class Key, class Value, class Hash, class Equal >
  void HashTable< Key, Value, Hash, Equal >::add(const Key& k, const Value& v)
  {
    size_t idx = hashFn_(k) % mass_.getSize();
    for (auto it = mass_[idx].begin(); it != mass_[idx].end(); ++it) {
      if (equalFn_(it->first, k)) {
        it->second = v;
        return;
      }
    }
    mass_[idx].push_front(std::make_pair(k, v));
    ++size_;
  }

  template< class Key, class Value, class Hash, class Equal >
  bool HashTable< Key, Value, Hash, Equal >::drop(const Key& k)
  {
    size_t idx = hashFn_(k) % mass_.getSize();
    auto beforeIt = mass_[idx].beforeBegin();
    auto it = mass_[idx].begin();
    while (it != mass_[idx].end()) {
      if (equalFn_(it->first, k)) {
        mass_[idx].eraseAfter(beforeIt);
        --size_;
        return true;
      }
      ++it;
      ++beforeIt;
    }
    return false;
  }

  template< class Key, class Value, class Hash, class Equal >
  bool HashTable< Key, Value, Hash, Equal >::has(const Key& k) const
  {
    size_t idx = hashFn_(k) % mass_.getSize();
    for (auto it = mass_[idx].cbegin(); it != mass_[idx].cend(); ++it) {
      if (equalFn_(it->first, k)) {
        return true;
      }
    }
    return false;
  }

  template< class Key, class Value, class Hash, class Equal >
  Value* HashTable< Key, Value, Hash, Equal >::find(const Key& k)
  {
    size_t idx = hashFn_(k) % mass_.getSize();
    for (auto it = mass_[idx].begin(); it != mass_[idx].end(); ++it) {
      if (equalFn_(it->first, k)) {
        return &(it->second);
      }
    }
    return nullptr;
  }

  template< class Key, class Value, class Hash, class Equal >
  void HashTable< Key, Value, Hash, Equal >::rehash(size_t slots)
  {
    if (slots == 0) {
      slots = 1;
    }
    HashTable tmp(slots);
    for (size_t i = 0; i < mass_.getSize(); ++i) {
      for (auto it = mass_[i].begin(); it != mass_[i].end(); ++it) {
        tmp.add(it->first, it->second);
      }
    }
    swap(tmp);
  }

  template< class Key, class Value, class Hash, class Equal >
  size_t HashTable< Key, Value, Hash, Equal >::getSize() const
  {
    return size_;
  }

  template< class Key, class Value, class Hash, class Equal >
  HTIter< Key, Value, Hash, Equal > HashTable< Key, Value, Hash, Equal >::begin()
  {
    for (size_t i = 0; i < mass_.getSize(); ++i) {
      if (!mass_[i].isEmpty()) {
        return HTIter< Key, Value, Hash, Equal >(&mass_, i, mass_[i].begin());
      }
    }
    return end();
  }

  template< class Key, class Value, class Hash, class Equal >
  HTIter< Key, Value, Hash, Equal > HashTable< Key, Value, Hash, Equal >::end()
  {
    return HTIter< Key, Value, Hash, Equal >(&mass_, mass_.getSize(), LIter< std::pair< Key, Value > >());
  }

}

#endif
