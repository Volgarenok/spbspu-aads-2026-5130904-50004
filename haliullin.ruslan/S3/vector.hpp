#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "vector-iterators.hpp"
#include <stdexcept>

namespace haliullin
{
  template< class T >
  class Vector
  {
  public:
    ~Vector();
    Vector();
    Vector(size_t size, const T& value);

    Vector(const Vector< T >& rhs);
    Vector(Vector< T >&& rhs) noexcept;

    Vector< T >& operator=(const Vector< T >& rhs);
    Vector< T >& operator=(Vector< T >&& rhs) noexcept;

    void swap(Vector< T >& rhs) noexcept;

    T& at(size_t id);
    const T& at(size_t id) const;
    T& operator[](size_t id) noexcept;
    const T& operator[](size_t id) const noexcept;

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;
    size_t getCapacity() const noexcept;
    bool operator==(const Vector< T >& rhs) const noexcept;
    bool operator!=(const Vector< T >& rhs) const noexcept;

    void pushBack(const T& val);
    void pushBackRepeat(const T& val, size_t k);
    void pushFront(const T& val);
    void popBack();

    void insert(size_t id, const T& val);
    void insert(size_t id, const Vector< T >& rhs, size_t begin, size_t end);

    void erase(size_t id);
    void erase(size_t begin, size_t end);

    VIter< T > begin() noexcept;
    VIter< T > end() noexcept;
    VCIter< T > begin() const noexcept;
    VCIter< T > end() const noexcept;
    VIter< T > iter(size_t idx) noexcept;

    VCIter< T > cbegin() const noexcept;
    VCIter< T > cend() const noexcept;
    VCIter< T > citer(size_t idx) const noexcept;

    VIter< T > insert(VIter< T > pos, const T& val);
    VIter< T > insert(VIter< T > pos, VCIter< T > begin, VCIter< T > end);
    VIter< T > insert(VIter< T > pos, const T& val, size_t k);

    VIter< T > erase(VIter< T > pos);
    VIter< T > erase(VIter< T > begin, VIter< T > end);
    VIter< T > erase(VIter< T > pos, size_t k);

  private:
    T* data_;
    size_t size_, capacity_;
    explicit Vector(size_t size);
    friend class VIter< T >;
    friend class VCIter< T >;
  };
}

template< class T >
haliullin::Vector< T >::~Vector()
{
  delete[] data_;
}

template< class T >
haliullin::Vector< T >::Vector():
  data_(nullptr),
  size_(0),
  capacity_(0)
{}

template< class T>
haliullin::Vector< T >::Vector(size_t size):
  data_(size ? new T[size] : nullptr),
  size_(size),
  capacity_(size)
{}

template< class T >
haliullin::Vector< T >::Vector(size_t size, const T& value):
  Vector(size)
{
  for (size_t i = 0; i < size; ++i)
  {
    data_[i] = value;
  }
}

template< class T>
haliullin::Vector< T >::Vector(const Vector< T >& rhs):
  Vector(rhs.getSize())
{
  for (size_t i = 0; i < rhs.getSize(); ++i)
  {
    data_[i] = rhs.data_[i];
  }
}

template< class T >
haliullin::Vector< T >::Vector(Vector< T >&& rhs) noexcept:
  Vector()
{
  swap(rhs);
}

template< class T >
haliullin::Vector< T >& haliullin::Vector<T>::operator=(const Vector< T >& rhs)
{
  if (this == std::addressof(rhs))
  {
    return *this;
  }
  Vector< T > cpy(rhs);
  swap(cpy);
  return *this;
}

template< class T >
haliullin::Vector< T >& haliullin::Vector< T >::operator=(Vector< T >&& rhs) noexcept
{
  Vector< T > cpy(std::move(rhs));
  swap(cpy);
  return *this;
}

template< class T >
void haliullin::Vector< T >::swap(Vector< T >& rhs) noexcept
{
  std::swap(data_, rhs.data_);
  std::swap(size_, rhs.size_);
  std::swap(capacity_, rhs.capacity_);
}

template< class T >
T& haliullin::Vector< T >::at(size_t id)
{
  const Vector< T >* cthis = this;
  const T& cr = cthis->at(id);
  T& r = const_cast< T& >(cr);
  return r;
}

template< class T >
const T& haliullin::Vector< T >::at(size_t id) const
{
  if (id < getSize())
  {
    return (*this)[id];
  }
  throw std::out_of_range("id out of bound");
}

template< class T >
T& haliullin::Vector< T >::operator[](size_t id) noexcept
{
  return const_cast< T& >((*static_cast< const Vector< T >* >(this))[id]);
}

template< class T >
const T& haliullin::Vector< T >::operator[](size_t id) const noexcept
{
  return data_[id];
}

template< class T >
bool haliullin::Vector< T >::isEmpty() const noexcept
{
  return !size_;
}

template< class T >
size_t haliullin::Vector< T >::getSize() const noexcept
{
  return size_;
}

template< class T >
size_t haliullin::Vector< T >::getCapacity() const noexcept
{
  return capacity_;
}

template< class T >
bool haliullin::Vector< T >::operator==(const Vector< T >& rhs) const noexcept
{
  bool isEqual = (getSize() == rhs.getSize());
  for (size_t i = 0; i < getSize() && isEqual; ++i)
  {
    isEqual = ((*this)[i] == rhs[i]);
  }
  return isEqual;
}

template< class T >
bool haliullin::Vector< T >::operator!=(const Vector< T >& rhs) const noexcept
{
  return !(*this == rhs);
}

template< class T >
void haliullin::Vector< T >::pushBack(const T& val)
{
  if (size_ == capacity_)
  {
    size_t new_cap = capacity_ ? capacity_ * 2 : 1;
    T* temp_data = new T[new_cap];

    try
    {
      for (size_t i = 0; i < size_; ++i)
      {
        temp_data[i] = data_[i];
      }

      temp_data[size_++] = val;
    }
    catch (...)
    {
      delete[] temp_data;
      throw;
    }

    delete[] data_;
    data_ = temp_data;
    capacity_ = new_cap;
  }
  else
  {
    data_[size_++] = val;
  }
}

template< class T >
void haliullin::Vector< T >::pushBackRepeat(const T& val, size_t k)
{
  Vector< T > cpy(*this);
  for (size_t i = 0; i < k; ++i)
  {
    cpy.pushBack(val);
  }
  swap(cpy);
}

template< class T >
void haliullin::Vector< T >::pushFront(const T& val)
{
  Vector< T > v;
  v.pushBack(val);
  for (size_t i = 0; i < getSize(); ++i)
  {
    v.pushBack((*this)[i]);
  }
  swap(v);
}

template< class T >
void haliullin::Vector< T >::popBack()
{
  if (!size_)
  {
    throw std::out_of_range("Vector is empty");
  }
  --size_;
}

template< class T >
void haliullin::Vector< T >::insert(size_t id, const T& val)
{
  if (id > getSize())
  {
    throw std::out_of_range("id out of bound");
  }
  Vector< T > v;
  for(size_t i = 0; i < id; ++i)
  {
    v.pushBack((*this)[i]);
  }
  v.pushBack(val);
  for(size_t i = id; i < getSize(); ++i)
  {
    v.pushBack((*this)[i]);
  }
  swap(v);
}

template< class T >
void haliullin::Vector< T >::insert(size_t id, const Vector< T >& rhs, size_t begin, size_t end)
{
  if (id > getSize())
  {
    throw std::out_of_range("id out of bound");
  }
  if (begin == end)
  {
    return;
  }
  if (begin > rhs.getSize() || end > rhs.getSize() || begin > end)
  {
    throw std::out_of_range("range out of bound");
  }
  Vector< T > v;
  for (size_t i = 0; i < id; ++i)
  {
    v.pushBack((*this)[i]);
  }
  for (size_t i = begin; i < end; ++i)
  {
    v.pushBack(rhs[i]);
  }
  for(size_t i = id; i < getSize(); ++i)
  {
    v.pushBack((*this)[i]);
  }
  swap(v);
}

template< class T >
void haliullin::Vector< T >::erase(size_t id)
{
  if (id >= getSize())
  {
    throw std::out_of_range("id out of bound");
  }
  Vector< T > v(getSize() - 1);
  for (size_t i = 0; i < id; ++i)
  {
    v[i] = (*this)[i];
  }
  for (size_t i = id; i < v.getSize(); ++i)
  {
    v[i] = (*this)[i + 1];
  }
  swap(v);
}

template< class T >
void haliullin::Vector< T >::erase(size_t begin, size_t end)
{
  if (begin == end)
  {
    return;
  }
  if (begin > getSize() || end > getSize() || begin > end)
  {
    throw std::out_of_range("range out of bound");
  }
  size_t count = end - begin;
  Vector< T > v(getSize() - count);
  for(size_t i = 0; i < begin; ++i)
  {
    v[i] = (*this)[i];
  }
  for(size_t i = begin; i < v.getSize(); ++i)
  {
    v[i] = (*this)[i + count];
  }
  swap(v);
}

template< class T >
haliullin::VIter< T > haliullin::Vector< T >::begin() noexcept
{
  return VIter< T >(*this, 0);
}

template< class T >
haliullin::VIter< T > haliullin::Vector< T >::end() noexcept
{
  return VIter< T >(*this, size_);
}

template< class T >
haliullin::VCIter< T > haliullin::Vector< T >::begin() const noexcept
{
  return VCIter< T >(*this, 0);
}

template< class T >
haliullin::VCIter< T > haliullin::Vector< T >::end() const noexcept
{
  return VCIter< T >(*this, size_);
}

template< class T >
haliullin::VIter< T > haliullin::Vector< T >::iter(size_t idx) noexcept
{
  return VIter< T >(*this, idx);
}

template< class T >
haliullin::VCIter< T > haliullin::Vector< T >::cbegin() const noexcept
{
  return VCIter< T >(*this, 0);
}

template< class T >
haliullin::VCIter< T > haliullin::Vector< T >::cend() const noexcept
{
  return VCIter< T >(*this, size_);
}

template< class T >
haliullin::VCIter< T > haliullin::Vector< T >::citer(size_t idx) const noexcept
{
  return VCIter< T >(*this, idx);
}

template< class T >
haliullin::VIter< T > haliullin::Vector< T >::insert(VIter< T > pos, const T& val)
{
  size_t id = pos.getId(*this);
  insert(id, val);
  return iter(id);
}

template< class T >
haliullin::VIter< T > haliullin::Vector< T >::insert(VIter< T > pos, VCIter< T > begin, VCIter< T > end)
{
  size_t id = pos.getId(*this);
  if (id > getSize())
  {
    throw std::out_of_range("id out of bound");
  }
  if (begin == end)
  {
    return pos;
  }
  if (begin > end)
  {
    throw std::out_of_range("range out of bound");
  }
  Vector< T > v;
  for (size_t i = 0; i < id; ++i)
  {
    v.pushBack((*this)[i]);
  }
  for (auto it = begin; it != end; ++it)
  {
    v.pushBack(*it);
  }
  for (size_t i = id; i < getSize(); ++i)
  {
    v.pushBack((*this)[i]);
  }
  swap(v);
  return iter(id);
}

template< class T >
haliullin::VIter< T > haliullin::Vector< T >::insert(VIter< T > pos, const T& val, size_t k)
{
  size_t id = pos.getId(*this);
  if (id > getSize())
  {
    throw std::out_of_range("id out of bound");
  }
  if (k == 0)
  {
    return pos;
  }
  Vector< T > v;
  for (size_t i = 0; i < id; ++i)
  {
    v.pushBack((*this)[i]);
  }
  for (size_t i = 0; i < k; ++i)
  {
    v.pushBack(val);
  }
  for (size_t i = id; i < getSize(); ++i)
  {
    v.pushBack((*this)[i]);
  }
  swap(v);
  return iter(id);
}

template< class T >
haliullin::VIter< T > haliullin::Vector< T >::erase(VIter< T > pos)
{
  size_t id = pos.getId(*this);
  erase(id);
  return iter(id);
}

template< class T >
haliullin::VIter< T > haliullin::Vector< T >::erase(VIter< T > begin, VIter< T > end)
{
  if (begin == end)
  {
    return begin;
  }
  size_t b = begin.getId(*this);
  erase(b, end.getId(*this));
  return iter(b);
}

template< class T >
haliullin::VIter< T > haliullin::Vector< T >::erase(VIter< T > pos, size_t k)
{
  size_t id = pos.getId(*this);
  erase(id, id + k);
  return iter(id);
}

#endif
