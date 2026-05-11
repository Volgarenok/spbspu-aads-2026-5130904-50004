#ifndef HASHTABLE_ITERATORS_HPP
#define HASHTABLE_ITERATORS_HPP

#include "vector.hpp"
#include <cstddef>
#include <utility>

namespace haliullin
{
  template< class Key, class Value >
  using SlotType = std::pair< std::pair< Key, Value >, char >;

  template< class Key, class Value, class Hash, class Equal >
  class HashTable;

  template< class Key, class Value, class Hash, class Equal >
  class HIter
  {
  public:
   ~HIter() = default;
    HIter() noexcept;
    HIter(Vector< SlotType< Key, Value > >* slots, size_t idx) noexcept;

    std::pair< Key, Value >& operator*() const noexcept;
    std::pair< Key, Value >* operator->() const noexcept;

    HIter& operator++() noexcept;
    HIter operator++(int) noexcept;
    HIter& operator--() noexcept;
    HIter operator--(int) noexcept;

    bool operator==(const HIter& other) const noexcept;
    bool operator!=(const HIter& other) const noexcept;

  private:
    Vector< SlotType< Key, Value > >* slots_;
    size_t idx_;
    friend class HashTable< Key, Value, Hash, Equal >;
    friend class HCIter< Key, Value, Hash, Equal >;
  };

  template< class Key, class Value, class Hash, class Equal >
  class HCIter
  {
  public:
    ~HCIter() = default;
    HCIter() noexcept;
    HCIter(const Vector< SlotType< Key, Value > >* slots, size_t idx) noexcept;
    HCIter(const HIter< Key, Value, Hash, Equal >& it) noexcept;

    const std::pair< Key, Value >& operator*() const noexcept;
    const std::pair< Key, Value >* operator->() const noexcept;

    HCIter& operator++() noexcept;
    HCIter operator++(int) noexcept;
    HCIter& operator--() noexcept;
    HCIter operator--(int) noexcept;

    bool operator==(const HCIter& other) const noexcept;
    bool operator!=(const HCIter& other) const noexcept;

  private:
    const Vector< SlotType< Key, Value > >* slots_;
    size_t idx_;
    friend class HashTable< Key, Value, Hash, Equal >;
  };
}

template< class Key, class Value, class Hash, class Equal >
haliullin::HIter< Key, Value, Hash, Equal >::HIter() noexcept:
  slots_(nullptr),
  idx_(0)
{}

template< class Key, class Value, class Hash, class Equal >
haliullin::HIter< Key, Value, Hash, Equal >::HIter(Vector< SlotType< Key, Value > >* slots, size_t idx) noexcept:
  slots_(slots),
  idx_(idx)
{}

template< class Key, class Value, class Hash, class Equal >
std::pair< Key, Value >& haliullin::HIter< Key, Value, Hash, Equal >::operator*() const noexcept
{
  return (*slots_)[idx_].first;
}

template< class Key, class Value, class Hash, class Equal >
std::pair< Key, Value >* haliullin::HIter< Key, Value, Hash, Equal >::operator->() const noexcept
{
  return &((*slots_)[idx_].first);
}

template< class Key, class Value, class Hash, class Equal >
haliullin::HIter< Key, Value, Hash, Equal >& haliullin::HIter< Key, Value, Hash, Equal >::operator++() noexcept
{
  ++idx_;
  while (idx_ < slots_->getSize() && (*slots_)[idx_].second != 'o')
  {
    ++idx_;
  }
  return *this;
}

template< class Key, class Value, class Hash, class Equal >
haliullin::HIter< Key, Value, Hash, Equal > haliullin::HIter< Key, Value, Hash, Equal >::operator++(int) noexcept
{
  HIter tmp = *this;
  ++(*this);
  return tmp;
}

template< class Key, class Value, class Hash, class Equal >
haliullin::HIter< Key, Value, Hash, Equal >& haliullin::HIter< Key, Value, Hash, Equal >::operator--() noexcept
{
  if (!idx_)
  {
    return *this;
  }
  --idx_;
  while (idx_ < slots_->getSize() && (*slots_)[idx_].second != 'o')
  {
    --idx_;
  }
  return *this;
}

template< class Key, class Value, class Hash, class Equal >
haliullin::HIter< Key, Value, Hash, Equal > haliullin::HIter< Key, Value, Hash, Equal >::operator--(int) noexcept
{
  HIter tmp = *this;
  --(*this);
  return tmp;
}

template< class Key, class Value, class Hash, class Equal >
bool haliullin::HIter< Key, Value, Hash, Equal >::operator==(const HIter& other) const noexcept
{
  return slots_ == other.slots_ && idx_ == other.idx_;
}

template< class Key, class Value, class Hash, class Equal >
bool haliullin::HIter< Key, Value, Hash, Equal >::operator!=(const HIter& other) const noexcept
{
  return !(*this == other);
}


template< class Key, class Value, class Hash, class Equal >
haliullin::HCIter< Key, Value, Hash, Equal >::HCIter() noexcept:
  slots_(nullptr),
  idx_(0)
{}

template< class Key, class Value, class Hash, class Equal >
haliullin::HCIter< Key, Value, Hash, Equal >::HCIter(const Vector< SlotType<Key, Value > >*, size_t idx) noexcept:
  slots_(slots),
  idx_(idx)
{}

template< class Key, class Value, class Hash, class Equal >
haliullin::HCIter< Key, Value, Hash, Equal >::HCIter(const HIter< Key, Value, Hash, Equal >& it) noexcept:
  slots_(it.slots_),
  idx_(it.idx_)
{}

template< class Key, class Value, class Hash, class Equal >
const std::pair< Key, Value >& haliullin::HCIter< Key, Value, Hash, Equal >::operator*() const noexcept
{
  return (*slots_)[idx_].first;
}

template< class Key, class Value, class Hash, class Equal >
const std::pair< Key, Value >* haliullin::HCIter< Key, Value, Hash, Equal >::operator->() const noexcept
{
  return &((*slots_)[idx_].first);
}

template< class Key, class Value, class Hash, class Equal >
haliullin::HCIter< Key, Value, Hash, Equal >& haliullin::HCIter< Key, Value, Hash, Equal >::operator++() noexcept
{
  ++idx_;
  while (idx_ < slots_->getSize() && (*slots_)[idx_].second != 'o')
  {
    ++idx_;
  }
  return *this;
}

template< class Key, class Value, class Hash, class Equal >
haliullin::HCIter< Key, Value, Hash, Equal > haliullin::HCIter< Key, Value, Hash, Equal >::operator++(int) noexcept
{
  HCIter tmp = *this;
  ++(*this);
  return tmp;
}

template< class Key, class Value, class Hash, class Equal >
haliullin::HCIter< Key, Value, Hash, Equal >& haliullin::HCIter< Key, Value, Hash, Equal >::operator--() noexcept
{
  if (!idx_)
  {
    return *this;
  }
  --idx_;
  while (idx_ < slots_->getSize() && (*slots_)[idx_].second != 'o')
  {
    --idx_;
  }
  return *this;
}

template< class Key, class Value, class Hash, class Equal >
haliullin::HCIter< Key, Value, Hash, Equal > haliullin::HCIter< Key, Value, Hash, Equal >::operator--(int) noexcept
{
  HCIter tmp = *this;
  --(*this);
  return tmp;
}

template< class Key, class Value, class Hash, class Equal >
bool haliullin::HCIter< Key, Value, Hash, Equal >::operator==(const HCIter& other) const noexcept
{
  return slots_ == other.slots_ && idx_ == other.idx_;
}

template< class Key, class Value, class Hash, class Equal >
bool haliullin::HCIter< Key, Value, Hash, Equal >::operator!=(const HCIter& other) const noexcept
{
  return !(*this == other);
}

#endif
