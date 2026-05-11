#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP
#include "slist.hpp"
#include "xxhash.hpp"
#include <cstddef>
#include <functional>
#include <stdexcept>
#include <string>
#include <utility>

namespace alberto {

struct xx_hash {
  size_t operator()(const std::string& key) const
  {
    return static_cast< size_t >(
        xxhash_impl::xxhash32(key.data(), key.size()));
  }

  template< class T >
  size_t operator()(const T& key) const
  {
    return static_cast< size_t >(
        xxhash_impl::xxhash32(&key, sizeof(T)));
  }
};

struct pair_hash {
  size_t operator()(const std::pair< std::string, std::string >& p) const
  {
    const size_t h1 = xxhash_impl::xxhash32(
        p.first.data(), p.first.size());
    const size_t h2 = xxhash_impl::xxhash32(
        p.second.data(), p.second.size(), 0x9747b28cu);
    return h1 ^ (h2 * 2654435761ull);
  }
};

struct pair_equal {
  bool operator()(const std::pair< std::string, std::string >& a,
                  const std::pair< std::string, std::string >& b) const
  {
    return a == b;
  }
};
template< class Key, class Value,
          class Hash  = xx_hash,
          class Equal = std::equal_to< Key > >
class HashTable {
public:

  using Pair   = std::pair< Key, Value >;
  using Bucket = SList< Pair >;

private:

  Bucket* buckets_     = nullptr;
  size_t  numBuckets_  = 0;
  size_t  count_       = 0;
  size_t  bucketSize_  = 0;
  Hash    hash_;
  Equal   equal_;

  size_t bucketIndex(const Key& k) const
  {
    return hash_(k) % numBuckets_;
  }

  void destroy() noexcept
  {
    delete[] buckets_;
    buckets_    = nullptr;
    numBuckets_ = 0;
    count_      = 0;
  }

public:

  explicit HashTable(size_t slots     = 16,
                     size_t bucketCap = 0,
                     Hash   h         = Hash{},
                     Equal  eq        = Equal{}):
    numBuckets_(slots > 0 ? slots : 1),
    bucketSize_(bucketCap),
    hash_(h),
    eq(eq)
  {
    buckets_ = new Bucket[numBuckets_];
  }

  HashTable(const HashTable& o):
    numBuckets_(o.numBuckets_),
    count_(o.count_),
    bucketSize_(o.bucketSize_),
    hash_(o.hash_),
    equal_(o.equal_)
  {
    buckets_ = new Bucket[numBuckets_];
    for (size_t i = 0; i < numBuckets_; ++i) {
      buckets_[i] = o.buckets_[i];
    }
  }

  HashTable(HashTable&& o) noexcept:
    buckets_(o.buckets_),
    numBuckets_(o.numBuckets_),
    count_(o.count_),
    bucketSize_(o.bucketSize_),
    hash_(std::move(o.hash_)),
    equal_(std::move(o.equal_))
  {
    o.buckets_    = nullptr;
    o.numBuckets_ = 0;
    o.count_      = 0;
  }

  HashTable& operator=(HashTable o) noexcept
  {
    swap(o);
    return *this;
  }

  ~HashTable()
  {
    destroy();
  }

  void swap(HashTable& o) noexcept
  {
    std::swap(buckets_,    o.buckets_);
    std::swap(numBuckets_, o.numBuckets_);
    std::swap(count_,      o.count_);
    std::swap(bucketSize_, o.bucketSize_);
    std::swap(hash_,       o.hash_);
    std::swap(equal_,      o.equal_);
  }
