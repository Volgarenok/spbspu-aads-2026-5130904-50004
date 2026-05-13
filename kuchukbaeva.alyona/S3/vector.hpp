#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <cstddef>
#include <stdexcept>
#include <utility>

namespace kuchukbaeva
{
  template< class T > struct Viter;
  template< class T > struct Vciter;

  template< class T >
  struct Vector {
    public:
      ~Vector();
      Vector();
      Vector(const Vector< T >& rhs);
      Vector(Vector< T >&& rhs) noexcept;
      Vector(size_t size, const T& value);
      Vector< T >& operator=(const Vector< T >& rhs);
      Vector< T >& operator=(Vector< T >&& rhs) noexcept;
      void swap(Vector < T >& rhs) noexcept;

      void insert(size_t id, const T& t);
      void erase(size_t id);
      void insert(size_t id, const Vector< T >& rhs, size_t beg, size_t end_idx);
      void erase(size_t beg, size_t end_idx);

      bool isEmpty() const noexcept;
      size_t getSize() const noexcept;

      size_t getCapacity() const noexcept;
      void pushBack(const T&);
      void popBack();
      void pushFront(const T& v);
      void pushBackRepeat(const T& v, size_t k);

      T& operator[](size_t id) noexcept;
      const T& operator[](size_t id) const noexcept;
      T& at(size_t id);
      const T& at(size_t id) const;

      Viter< T > begin() noexcept;
      Viter< T > end() noexcept;
      Vciter< T > begin() const noexcept;
      Vciter< T > end() const noexcept;
      Vciter< T > cbegin() const noexcept;
      Vciter< T > cend() const noexcept;

      void insert(Vciter< T > pos, const T& value);
      void insert(Vciter< T > pos, size_t count, const T& value);
      void insert(Vciter< T > pos, Vciter< T > first, Vciter< T > last);

      void erase(Vciter< T > pos);
      void erase(Vciter< T > first, Vciter< T > last);
      void erase(Vciter< T > pos, size_t count);

    private:
      T* data_;
      size_t size_, capacity_;
      explicit Vector(size_t size);
  };

  template< class T >
  struct Viter {
      T* p;
      Viter(T* ptr = nullptr);
      T& operator*() const;
      Viter< T >& operator++();
      Viter< T > operator++(int);
      Viter< T >& operator--();
      Viter< T > operator--(int);
      Viter< T >& operator+=(size_t n);
      Viter< T >& operator-=(size_t n);
      Viter< T > operator+(size_t n) const;
      Viter< T > operator-(size_t n) const;
      long long operator-(const Viter< T >& other) const;
      bool operator==(const Viter< T >& other) const;
      bool operator!=(const Viter< T >& other) const;
      bool operator<(const Viter< T >& other) const;
  };

  template< class T >
  struct Vciter {
      const T* p;
      Vciter(const T* ptr = nullptr);
      Vciter(const Viter< T >& other);
      const T& operator*() const;
      Vciter< T >& operator++();
      Vciter< T > operator++(int);
      Vciter< T >& operator--();
      Vciter< T > operator--(int);
      Vciter< T >& operator+=(size_t n);
      Vciter< T >& operator-=(size_t n);
      Vciter< T > operator+(size_t n) const;
      Vciter< T > operator-(size_t n) const;
      long long operator-(const Vciter< T >& other) const;
      bool operator==(const Vciter< T >& other) const;
      bool operator!=(const Vciter< T >& other) const;
      bool operator<(const Vciter< T >& other) const;
  };
}

template< class T >
kuchukbaeva::Viter< T >::Viter(T* ptr):
  p(ptr)
{}

template< class T >
T& kuchukbaeva::Viter< T >::operator*() const {
  return *p;
}

template< class T >
kuchukbaeva::Viter< T >& kuchukbaeva::Viter< T >::operator++() {
  ++p;
  return *this;
}

template< class T >
kuchukbaeva::Viter< T > kuchukbaeva::Viter< T >::operator++(int) {
  Viter tmp = *this;
  ++p;
  return tmp;
}

template< class T >
kuchukbaeva::Viter< T >& kuchukbaeva::Viter< T >::operator--() {
  --p;
  return *this;
}

template< class T >
kuchukbaeva::Viter< T > kuchukbaeva::Viter< T >::operator--(int) {
  Viter tmp = *this;
  --p;
  return tmp;
}

template< class T >
kuchukbaeva::Viter< T >& kuchukbaeva::Viter< T >::operator+=(size_t n) {
  p += n;
  return *this;
}

template< class T >
kuchukbaeva::Viter< T >& kuchukbaeva::Viter< T >::operator-=(size_t n) {
  p -= n;
  return *this;
}

template< class T >
kuchukbaeva::Viter< T > kuchukbaeva::Viter< T >::operator+(size_t n) const {
  return Viter(p + n);
}

template< class T >
kuchukbaeva::Viter< T > kuchukbaeva::Viter< T >::operator-(size_t n) const {
  return Viter(p - n);
}

template< class T >
long long kuchukbaeva::Viter< T >::operator-(const Viter< T >& other) const {
  return p - other.p;
}

template< class T >
bool kuchukbaeva::Viter< T >::operator==(const Viter< T >& other) const {
  return p == other.p;
}

template< class T >
bool kuchukbaeva::Viter< T >::operator!=(const Viter< T >& other) const {
  return p != other.p;
}

template< class T >
bool kuchukbaeva::Viter< T >::operator<(const Viter< T >& other) const {
  return p < other.p;
}

template< class T >
kuchukbaeva::Vciter< T >::Vciter(const T* ptr):
  p(ptr)
{}

template< class T >
kuchukbaeva::Vciter< T >::Vciter(const Viter< T >& other):
  p(other.p)
{}

template< class T >
const T& kuchukbaeva::Vciter< T >::operator*() const {
  return *p;
}

template< class T >
kuchukbaeva::Vciter< T >& kuchukbaeva::Vciter< T >::operator++() {
  ++p;
  return *this;
}

template< class T >
kuchukbaeva::Vciter< T > kuchukbaeva::Vciter< T >::operator++(int) {
  Vciter tmp = *this;
  ++p;
  return tmp;
}

template< class T >
kuchukbaeva::Vciter< T >& kuchukbaeva::Vciter< T >::operator--() {
  --p;
  return *this;
}

template< class T >
kuchukbaeva::Vciter< T > kuchukbaeva::Vciter< T >::operator--(int) {
  Vciter tmp = *this;
  --p;
  return tmp;
}

template< class T >
kuchukbaeva::Vciter< T >& kuchukbaeva::Vciter< T >::operator+=(size_t n) {
  p += n;
  return *this;
}

template< class T >
kuchukbaeva::Vciter< T >& kuchukbaeva::Vciter< T >::operator-=(size_t n) {
  p -= n;
  return *this;
}

template< class T >
kuchukbaeva::Vciter< T > kuchukbaeva::Vciter< T >::operator+(size_t n) const {
  return Vciter(p + n);
}

template< class T >
kuchukbaeva::Vciter< T > kuchukbaeva::Vciter< T >::operator-(size_t n) const {
  return Vciter(p - n);
}

template< class T >
long long kuchukbaeva::Vciter< T >::operator-(const Vciter< T >& other) const {
  return p - other.p;
}

template< class T >
bool kuchukbaeva::Vciter< T >::operator==(const Vciter< T >& other) const {
  return p == other.p;
}

template< class T >
bool kuchukbaeva::Vciter< T >::operator!=(const Vciter< T >& other) const {
  return p != other.p;
}

template< class T >
bool kuchukbaeva::Vciter< T >::operator<(const Vciter< T >& other) const {
  return p < other.p;
}

template< class T >
kuchukbaeva::Vector< T >::Vector():
  data_(nullptr),
  size_(0),
  capacity_(0)
{}

template< class T >
kuchukbaeva::Vector< T >::~Vector() {
  delete[] data_;
}

template< class T >
kuchukbaeva::Vector< T >::Vector(Vector < T >&& rhs) noexcept:
  Vector()
{
  swap(rhs);
}

template< class T >
kuchukbaeva::Vector< T >& kuchukbaeva::Vector < T >::operator=(Vector< T >&& rhs) noexcept
{
  Vector< T > cpy(std::move(rhs));
  swap(cpy);
  return *this;
}

template< class T >
void kuchukbaeva::Vector< T >::pushFront(const T& v)
{
  Vector< T > tmp(getSize() + 1);
  tmp[0] = v;
  for (size_t i = 0; i < getSize(); ++i) {
    tmp[i + 1] = data_[i];
  }
  swap(tmp);
}

template< class T >
T& kuchukbaeva::Vector< T >::operator[](size_t id) noexcept {
  return const_cast< T& >((*static_cast< const Vector< T >* >(this))[id]);
}

template< class T >
const T& kuchukbaeva::Vector< T >::operator[](size_t id) const noexcept {
  return data_[id];
}

template< class T>
T& kuchukbaeva::Vector< T >::at(size_t id) {
  const Vector< T >* cthis = this;
  const T& cr = cthis->at(id);
  T& r = const_cast< T& >(cr);
  return r;
}

template< class T >
const T& kuchukbaeva::Vector< T >::at(size_t id) const {
  if (id < getSize()) {
    return (*this)[id];
  }
  throw std::out_of_range("id out of bound");
}

template< class T >
kuchukbaeva::Vector< T >::Vector(const Vector< T >& rhs):
  Vector(rhs.getSize())
{
  for (size_t i = 0; i < rhs.getSize(); ++i) {
    data_[i] = rhs.data_[i];
  }
}

template< class T >
kuchukbaeva::Vector< T >& knk::Vector< T >::operator=(const Vector< T >& rhs)
{
  if (this == std::addressof(rhs)) {
    return *this;
  }
  Vector< T > cpy(rhs);
  swap(cpy);
  return *this;
}

template< class T >
void kuchukbaeva::Vector< T >::swap(Vector< T >& rhs) noexcept
{
  std::swap(data_, rhs.data_);
  std::swap(size_, rhs.size_);
  std::swap(capacity_, rhs.capacity_);
}

template< class T >
kuchukbaeva::Vector< T >::Vector(size_t size):
  data_(size ? new T[size] : nullptr),
  size_(size),
  capacity_(size)
{}

template< class T >
kuchukbaeva::Vector< T >::Vector(size_t size, const T& value):
  Vector(size)
{
  for (size_t i = 0; i < size; ++i) {
    data_[i] = value;
  }
}

template< class T >
size_t kuchukbaeva::Vector< T >::getSize() const noexcept {
  return size_;
}

template< class T >
bool kuchukbaeva::Vector< T >::isEmpty() const noexcept {
  return !size_;
}

template< class T >
size_t kuchukbaeva::Vector< T >::getCapacity() const noexcept {
  return capacity_;
}

template< class T >
void kuchukbaeva::Vector< T >::pushBack(const T& value) {
  if (size_ == capacity_) {
    size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
    T* new_data = new T[new_capacity];
    try {
      for (size_t i = 0; i < size_; ++i) {
        new_data[i] = data_[i];
      }
      new_data[size_] = value;
    } catch (...) {
      delete[] new_data;
      throw;
    }

    delete[] data_;
    data_ = new_data;
    capacity_ = new_capacity;
    ++size_;
  } else {
    data_[size_] = value;
    ++size_;
  }
}

template< class T >
void kuchukbaeva::Vector< T >::popBack() {
  if (size_ > 0) {
    --size_;
  }
}

template< class T >
void kuchukbaeva::Vector< T >::pushBackRepeat(const T& t, size_t k)
{
  Vector< T > cpy(*this);
  for (size_t i = 0; i < k; ++i) {
    cpy.pushBack(t);
  }
  swap(cpy);
}

template< class T >
void kuchukbaeva::Vector< T >::insert(size_t id, const T& t) {
  if (id > getSize()) {
    throw std::out_of_range("id out of bound");
  }
  Vector< T > tmp(getSize() + 1);
  for (size_t i = 0; i < id; ++i) {
    tmp[i] = data_[i];
  }
  tmp[id] = t;
  for (size_t i = id; i < getSize(); ++i) {
    tmp[i + 1] = data_[i];
  }
  swap(tmp);
}

template< class T >
void kuchukbaeva::Vector< T >::insert(size_t id, const Vector< T >& rhs, size_t beg, size_t end_idx) {
  if (id > getSize() || beg > end_idx || end_idx > rhs.getSize()) {
    throw std::out_of_range("id out of bound");
  }
  size_t count = end_idx - beg;
  Vector< T > tmp(getSize() + count);
  for (size_t i = 0; i < id; ++i) {
    tmp[i] = data_[i];
  }
  for (size_t i = 0; i < count; ++i) {
    tmp[id + i] = rhs.data_[beg + i];
  }
  for (size_t i = id; i < getSize(); ++i) {
    tmp[i + count] = data_[i];
  }
  swap(tmp);
}

template< class T >
void kuchukbaeva::Vector< T >::erase(size_t id) {
  if (id >= getSize()) {
    throw std::out_of_range("id out of bound");
  }
  Vector< T > tmp(getSize() - 1);
  for (size_t i = 0; i < id; ++i) {
    tmp[i] = data_[i];
  }
  for (size_t i = id + 1; i < getSize(); ++i) {
    tmp[i - 1] = data_[i];
  }
  swap(tmp);
}

template< class T >
void kuchukbaeva::Vector< T >::erase(size_t beg, size_t end_idx) {
  if (beg > end_idx || end_idx > getSize()) {
    throw std::out_of_range("id out of bound");
  }
  size_t count = end_idx - beg;
  Vector< T > tmp(getSize() - count);
  for (size_t i = 0; i < beg; ++i) {
    tmp[i] = data_[i];
  }
  for (size_t i = end_idx; i < getSize(); ++i) {
    tmp[i - count] = data_[i];
  }
  swap(tmp);
}

template< class T >
kuchukbaeva::Viter< T > kuchukbaeva::Vector< T >::begin() noexcept {
  return Viter< T >(data_);
}

template< class T >
kuchukbaeva::Viter< T > kuchukbaeva::Vector< T >::end() noexcept {
  return Viter< T >(data_ + size_);
}

template< class T >
kuchukbaeva::Vciter< T > kuchukbaeva::Vector< T >::begin() const noexcept {
  return Vciter< T >(data_);
}

template< class T >
kuchukbaeva::Vciter< T > kuchukbaeva::Vector< T >::end() const noexcept {
  return Vciter< T >(data_ + size_);
}

template< class T >
kuchukbaeva::Vciter< T > kuchukbaeva::Vector< T >::cbegin() const noexcept {
  return Vciter< T >(data_);
}

template< class T >
kuchukbaeva::Vciter< T > kuchukbaeva::Vector< T >::cend() const noexcept {
  return Vciter< T >(data_ + size_);
}

template< class T >
void kuchukbaeva::Vector< T >::insert(Vciter< T > pos, const T& value) {
  insert(pos.p - data_, value);
}

template< class T >
void kuchukbaeva::Vector< T >::insert(Vciter< T > pos, size_t count, const T& value) {
  size_t id = pos.p - data_;
  Vector< T > tmp(getSize() + count);
  for (size_t i = 0; i < id; ++i) {
    tmp[i] = data_[i];
  }
  for (size_t i = 0; i < count; ++i) {
    tmp[id + i] = value;
  }
  for (size_t i = id; i < getSize(); ++i) {
    tmp[i + count] = data_[i];
  }
  swap(tmp);
}

template< class T >
void kuchukbaeva::Vector< T >::insert(Vciter< T > pos, Vciter< T > first, Vciter< T > last) {
  size_t id = pos.p - data_;
  size_t count = 0;
  for (Vciter< T > it = first; it != last; ++it) {
    ++count;
  }
  Vector< T > tmp(getSize() + count);
  for (size_t i = 0; i < id; ++i) {
    tmp[i] = data_[i];
  }
  size_t i = 0;
  for (Vciter< T > it = first; it != last; ++it) {
    tmp[id + i] = *it;
    ++i;
  }
  for (size_t j = id; j < getSize(); ++j) {
    tmp[j + count] = data_[j];
  }
  swap(tmp);
}

template< class T >
void kuchukbaeva::Vector< T >::erase(Vciter< T > pos) {
  erase(pos.p - data_);
}

template< class T >
void kuchukbaeva::Vector< T >::erase(Vciter< T > first, Vciter< T > last) {
  erase(first.p - data_, last.p - data_);
}

template< class T >
void kuchukbaeva::Vector< T >::erase(Vciter< T > pos, size_t count) {
  erase(pos.p - data_, pos.p - data_ + count);
}

#endif
