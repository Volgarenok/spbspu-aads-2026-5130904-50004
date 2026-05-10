#ifndef VECTOR_ITERATORS_HPP
#define VECTOR_ITERATORS_HPP

#include <cstddef>

namespace haliullin
{
  template< class T >
  class Vector;

  template< class T >
  class VCIter;

  template< class T >
  class VIter
  {
  public:
    VIter(T* ptr) noexcept;
    VIter(Vector< T >& vec, size_t idx) noexcept;
    ~VIter() = default;

    T& operator*() const noexcept;
    T* operator->() const noexcept;

    VIter< T >& operator++() noexcept;
    VIter< T > operator++(int) noexcept;
    VIter< T >& operator--() noexcept;
    VIter< T > operator--(int) noexcept;

    VIter< T >& operator+=(size_t n) noexcept;
    VIter< T >& operator-=(size_t n) noexcept;
    VIter< T > operator+(size_t n) const noexcept;
    VIter< T > operator-(size_t n) const noexcept;
    int operator-(const VIter< T >& other) const noexcept;

    size_t getId(const Vector< T >& vec) const noexcept;

    bool operator==(const VIter< T >& other) const noexcept;
    bool operator!=(const VIter< T >& other) const noexcept;
    bool operator<(const VIter< T >& other) const noexcept;
    bool operator<=(const VIter< T >& other) const noexcept;
    bool operator>(const VIter< T >& other) const noexcept;
    bool operator>=(const VIter< T >& other) const noexcept;

  private:
    T* ptr_;
    friend class VCIter< T >;
  };

  template< class T >
  class VCIter
  {
  public:
    VCIter(const T* ptr) noexcept;
    VCIter(const Vector< T >&vec, size_t idx) noexcept;
    VCIter(const VIter< T >& other) noexcept;
    ~VCIter() = default;

    const T& operator*() const noexcept;
    const T* operator->() const noexcept;

    VCIter< T >& operator++() noexcept;
    VCIter< T > operator++(int) noexcept;
    VCIter< T >& operator--() noexcept;
    VCIter< T > operator--(int) noexcept;

    VCIter< T >& operator+=(size_t n) noexcept;
    VCIter< T >& operator-=(size_t n) noexcept;
    VCIter< T > operator+(size_t n) const noexcept;
    VCIter< T > operator-(size_t n) const noexcept;
    int operator-(const VCIter< T >& other) const noexcept;

    size_t getId(const Vector< T >& vec) const noexcept;

    bool operator==(const VCIter< T >& other) const noexcept;
    bool operator!=(const VCIter< T >& other) const noexcept;
    bool operator<(const VCIter< T >& other) const noexcept;
    bool operator<=(const VCIter< T >& other) const noexcept;
    bool operator>(const VCIter< T >& other) const noexcept;
    bool operator>=(const VCIter< T >& other) const noexcept;

  private:
    const T* cptr_;
  };
}

template< class T >
haliullin::VIter< T >::VIter(T* ptr) noexcept:
  ptr_(ptr)
{}

template< class T >
haliullin::VIter< T >::VIter(Vector< T >& vec, size_t idx) noexcept:
  ptr_(&vec[idx])
{}

template< class T >
T& haliullin::VIter< T >::operator*() const noexcept
{
  return *ptr_;
}

template< class T >
T* haliullin::VIter< T >::operator->() const noexcept
{
  return ptr_;
}

template< class T >
haliullin::VIter< T >& haliullin::VIter< T >::operator++() noexcept
{
  ++ptr_;
  return *this;
}

template< class T >
haliullin::VIter< T > haliullin::VIter< T >::operator++(int) noexcept
{
  VIter< T > tmp = *this;
  ++ptr_;
  return tmp;
}

template< class T >
haliullin::VIter< T >& haliullin::VIter< T >::operator--() noexcept
{
  --ptr_;
  return *this;
}

template< class T >
haliullin::VIter< T > haliullin::VIter< T >::operator--(int) noexcept
{
  VIter< T > tmp = *this;
  --ptr_;
  return tmp;
}

template< class T >
haliullin::VIter< T >& haliullin::VIter< T >::operator+=(size_t n) noexcept
{
  ptr_ += n;
  return *this;
}

template< class T >
haliullin::VIter< T >& haliullin::VIter< T >::operator-=(size_t n) noexcept
{
  ptr_ -= n;
  return *this;
}

template< class T >
haliullin::VIter< T > haliullin::VIter< T >::operator+(size_t n) const noexcept
{
  VIter< T > tmp = *this;
  tmp += n;
  return tmp;
}

template< class T >
haliullin::VIter< T > haliullin::VIter< T >::operator-(size_t n) const noexcept
{
  VIter< T > tmp = *this;
  tmp -= n;
  return tmp;
}

template< class T >
int haliullin::VIter< T >::operator-(const VIter< T >& other) const noexcept
{
  return static_cast< int >(ptr_ - other.ptr_);
}

template< class T >
size_t haliullin::VIter< T >::getId(const Vector< T >& vec) const noexcept
{
  return static_cast< size_t >(ptr_ - vec.data_);
}

template< class T >
bool haliullin::VIter< T >::operator==(const VIter< T >& other) const noexcept
{
  return ptr_ == other.ptr_;
}

template< class T >
bool haliullin::VIter< T >::operator!=(const VIter< T >&other) const noexcept
{
  return !(*this == other);
}

template< class T >
bool haliullin::VIter< T >::operator<(const VIter< T >& other) const noexcept
{
  return ptr_ <  other.ptr_;
}

template< class T >
bool haliullin::VIter< T >::operator<=(const VIter< T >& other) const noexcept
{
  return ptr_ <= other.ptr_;
}

template< class T >
bool haliullin::VIter< T >::operator>(const VIter< T >& other) const noexcept
{
  return ptr_ > other.ptr_;
}

template< class T >
bool haliullin::VIter< T >::operator>=(const VIter< T >& other) const noexcept
{
  return ptr_ >= other.ptr_;
}

template< class T >
haliullin::VCIter< T >::VCIter(const T* ptr) noexcept:
  cptr_(ptr)
{}

template< class T >
haliullin::VCIter< T >::VCIter(const Vector< T >& vec, size_t idx) noexcept:
  cptr_(&vec[idx])
{}

template< class T >
haliullin::VCIter< T >::VCIter(const VIter< T >& other) noexcept:
  cptr_(other.ptr_)
{}

template< class T >
const T& haliullin::VCIter< T >::operator*() const noexcept
{
  return *cptr_;
}

template< class T >
const T* haliullin::VCIter< T >::operator->() const noexcept
{
  return cptr_;
}

template< class T >
haliullin::VCIter< T >& haliullin::VCIter< T >::operator++() noexcept
{
  ++cptr_;
  return *this;
}

template< class T >
haliullin::VCIter< T > haliullin::VCIter< T >::operator++(int) noexcept
{
  VCIter< T > tmp = *this;
  ++cptr_;
  return tmp;
}

template< class T >
haliullin::VCIter< T >& haliullin::VCIter< T >::operator--() noexcept
{
  --cptr_;
  return *this;
}

template< class T >
haliullin::VCIter< T > haliullin::VCIter< T >::operator--(int) noexcept
{
  VCIter< T > tmp = *this;
  --cptr_;
  return tmp;
}

template< class T >
haliullin::VCIter< T >& haliullin::VCIter< T >::operator+=(size_t n) noexcept
{
  cptr_ += n;
  return *this;
}

template< class T >
haliullin::VCIter< T >& haliullin::VCIter< T >::operator-=(size_t n) noexcept
{
  cptr_ -= n;
  return *this;
}

template< class T >
haliullin::VCIter< T > haliullin::VCIter< T >::operator+(size_t n) const noexcept
{
  VCIter< T > tmp = *this;
  tmp += n;
  return tmp;
}

template< class T >
haliullin::VCIter< T > haliullin::VCIter< T >::operator-(size_t n) const noexcept
{
  VCIter< T > tmp = *this;
  tmp -= n;
  return tmp;
}

template< class T >
int haliullin::VCIter< T >::operator-(const VCIter< T >& other) const noexcept
{
  return static_cast< int >(cptr_ - other.cptr_);
}

template< class T >
size_t haliullin::VCIter< T >::getId(const Vector< T >& vec) const noexcept
{
  return static_cast< size_t >(cptr_ - vec.data_);
}

template< class T >
bool haliullin::VCIter< T >::operator==(const VCIter< T >& other) const noexcept
{
  return cptr_ == other.cptr_;
}

template< class T >
bool haliullin::VCIter< T >::operator!=(const VCIter< T >& other) const noexcept
{
  return !(*this == other);
}

template< class T >
bool haliullin::VCIter< T >::operator<(const VCIter< T >& other) const noexcept
{
  return cptr_ < other.cptr_;
}

template< class T >
bool haliullin::VCIter< T >::operator<=(const VCIter< T >& other) const noexcept
{
  return cptr_ <= other.cptr_;
}

template< class T >
bool haliullin::VCIter< T >::operator>(const VCIter< T >& other) const noexcept
{
  return cptr_ > other.cptr_;
}

template< class T >
bool haliullin::VCIter< T >::operator>=(const VCIter< T >& other) const noexcept
{
  return cptr_ >= other.cptr_;
}

#endif
