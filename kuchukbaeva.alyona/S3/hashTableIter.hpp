#ifndef HASHTABLEITER_HPP
#define HASHTABLEITER_HPP

#include "vector.hpp"
#include "../common/list.hpp"
#include <utility>

namespace kuchukbaeva {

  template< class Key, class Value, class Hash, class Equal >
  class HashTable;

  template< class Key, class Value, class Hash, class Equal >
  class HTCiter;

  template< class Key, class Value, class Hash, class Equal >
  class HTIter {
  public:
    HTIter(Vector< List< std::pair< Key, Value > > >* mass = nullptr, size_t idx = 0, LIter< std::pair< Key, Value > > listIt = LIter< std::pair< Key, Value > >());

    std::pair< Key, Value >& operator*();
    std::pair< Key, Value >* operator->();

    HTIter& operator++();
    HTIter operator++(int);

    bool operator==(const HTIter& other) const;
    bool operator!=(const HTIter& other) const;

  private:
    friend class HashTable< Key, Value, Hash, Equal >;
    friend class HTCiter< Key, Value, Hash, Equal >;
    Vector< List< std::pair< Key, Value > > >* mass_;
    size_t massIdx_;
    LIter< std::pair< Key, Value > > listIt_;
  };


  template< class Key, class Value, class Hash, class Equal >
  class HTCiter {
  public:
    HTCiter(const Vector< List< std::pair< Key, Value > > >* mass = nullptr, size_t idx = 0, LCIter< std::pair< Key, Value > > listIt = LCIter< std::pair< Key, Value > >());
    HTCiter(const HTIter< Key, Value, Hash, Equal >& other);

    const std::pair< Key, Value >& operator*() const;
    const std::pair< Key, Value >* operator->() const;

    HTCiter& operator++();
    HTCiter operator++(int);

    bool operator==(const HTCiter& other) const;
    bool operator!=(const HTCiter& other) const;

  private:
    friend class HashTable< Key, Value, Hash, Equal >;
    const Vector< List< std::pair< Key, Value > > >* mass_;
    size_t massIdx_;
    LCIter< std::pair< Key, Value > > listIt_;
  };

}

template< class Key, class Value, class Hash, class Equal >
kuchukbaeva::HTIter< Key, Value, Hash, Equal >::HTIter(Vector< List< std::pair< Key, Value > > >* mass, size_t idx, LIter< std::pair< Key, Value > > listIt) :
  mass_(mass),
  massIdx_(idx),
  listIt_(listIt)
{
}

template< class Key, class Value, class Hash, class Equal >
std::pair< Key, Value >& kuchukbaeva::HTIter< Key, Value, Hash, Equal >::operator*()
{
  return *listIt_;
}

template< class Key, class Value, class Hash, class Equal >
std::pair< Key, Value >* kuchukbaeva::HTIter< Key, Value, Hash, Equal >::operator->()
{
  return &(*listIt_);
}

template< class Key, class Value, class Hash, class Equal >
kuchukbaeva::HTIter< Key, Value, Hash, Equal >& kuchukbaeva::HTIter< Key, Value, Hash, Equal >::operator++()
{
  ++listIt_;
  if (mass_ && listIt_ == (*mass_)[massIdx_].end()) {
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

template< class Key, class Value, class Hash, class Equal >
kuchukbaeva::HTIter< Key, Value, Hash, Equal > kuchukbaeva::HTIter< Key, Value, Hash, Equal >::operator++(int)
{
  HTIter tmp = *this;
  ++(*this);
  return tmp;
}

template< class Key, class Value, class Hash, class Equal >
bool kuchukbaeva::HTIter< Key, Value, Hash, Equal >::operator==(const HTIter& other) const
{
  return massIdx_ == other.massIdx_ && listIt_ == other.listIt_;
}

template< class Key, class Value, class Hash, class Equal >
bool kuchukbaeva::HTIter< Key, Value, Hash, Equal >::operator!=(const HTIter& other) const
{
  return !(*this == other);
}

template< class Key, class Value, class Hash, class Equal >
kuchukbaeva::HTCiter< Key, Value, Hash, Equal >::HTCiter(const Vector< List< std::pair< Key, Value > > >* mass, size_t idx, LCIter< std::pair< Key, Value > > listIt) :
  mass_(mass),
  massIdx_(idx),
  listIt_(listIt)
{
}

template< class Key, class Value, class Hash, class Equal >
kuchukbaeva::HTCiter< Key, Value, Hash, Equal >::HTCiter(const HTIter< Key, Value, Hash, Equal >& other) :
  mass_(other.mass_),
  massIdx_(other.massIdx_),
  listIt_(other.listIt_)
{
}

template< class Key, class Value, class Hash, class Equal >
const std::pair< Key, Value >& kuchukbaeva::HTCiter< Key, Value, Hash, Equal >::operator*() const
{
  return *listIt_;
}

template< class Key, class Value, class Hash, class Equal >
const std::pair< Key, Value >* kuchukbaeva::HTCiter< Key, Value, Hash, Equal >::operator->() const
{
  return &(*listIt_);
}

template< class Key, class Value, class Hash, class Equal >
kuchukbaeva::HTCiter< Key, Value, Hash, Equal >& kuchukbaeva::HTCiter< Key, Value, Hash, Equal >::operator++()
{
  ++listIt_;
  if (mass_ && listIt_ == (*mass_)[massIdx_].cend()) {
    ++massIdx_;
    while (massIdx_ < mass_->getSize() && (*mass_)[massIdx_].isEmpty()) {
      ++massIdx_;
    }
    if (massIdx_ < mass_->getSize()) {
      listIt_ = (*mass_)[massIdx_].cbegin();
    } else {
      listIt_ = LCIter< std::pair< Key, Value > >();
    }
  }
  return *this;
}

template< class Key, class Value, class Hash, class Equal >
kuchukbaeva::HTCiter< Key, Value, Hash, Equal > kuchukbaeva::HTCiter< Key, Value, Hash, Equal >::operator++(int)
{
  HTCiter tmp = *this;
  ++(*this);
  return tmp;
}

template< class Key, class Value, class Hash, class Equal >
bool kuchukbaeva::HTCiter< Key, Value, Hash, Equal >::operator==(const HTCiter& other) const
{
  return massIdx_ == other.massIdx_ && listIt_ == other.listIt_;
}

template< class Key, class Value, class Hash, class Equal >
bool kuchukbaeva::HTCiter< Key, Value, Hash, Equal >::operator!=(const HTCiter& other) const
{
  return !(*this == other);
}

#endif
