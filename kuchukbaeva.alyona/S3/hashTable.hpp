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
}
