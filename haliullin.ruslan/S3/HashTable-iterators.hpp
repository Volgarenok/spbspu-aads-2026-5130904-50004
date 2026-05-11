#ifndef HASHTABLE_ITERATORS_HPP
#define HASHTABLE_ITERATORS_HPP

namespace haliullin
{
  template< class Key, class Value, class Hash, class Equal >
  class HIter
  {
  public:
    using value_type = std::pair<Key, Value>;
    using reference = value_type&;
    using pointer = value_type*;

    HIter() noexcept;
    HIter(Vector< Slot >* slots, size_t idx) noexcept;

    reference operator*() const noexcept;
    pointer operator->() const noexcept;

    HIter& operator++() noexcept;
    HIter operator++(int) noexcept;
    HIter& operator--() noexcept;
    HIter operator--(int) noexcept;

    bool operator==(const HIter& other) const noexcept;
    bool operator!=(const HIter& other) const noexcept;

  private:
    Vector< Slot >* slots_;
    size_t idx;
    friend class HashTable< Key, Value, Hash, Equal >;
    friend class HCIter< Key, Value, Hash, Equal >
  };
}

#endif
