#ifndef LIST_H
#define LIST_H

#include <stdexcept>

template <class T> class List;

template <class T>
class Iter {
    friend class List<T>;

public:
    Iter() noexcept : ptr_(nullptr) {}
    Iter(const Iter&) noexcept = default;
    Iter(Iter&&) noexcept = default;
    ~Iter() = default;
    Iter& operator=(const Iter&) noexcept = default;
    Iter& operator=(Iter&&) noexcept = default;


    T& operator*() const noexcept {
        return ptr_->data_;
    }
    T* operator->() const noexcept {
        return &(ptr_->data_);
    }

    Iter& operator++() noexcept {
        ptr_ = ptr_->next_;
        return *this;
    }

    bool operator==(const Iter& other) const noexcept {
        return ptr_ == other.ptr_;
    }
    bool operator!=(const Iter& other) const noexcept {
        return ptr_ != other.ptr_;
    }

private:
    typename List<T>::Elem* ptr_;
    explicit Iter(typename List<T>::Elem* p) noexcept : ptr_(p) {}
};

template <class T>
class List {
  struct Elem {
    T data_;
    Elem* next_;
  };

};

#endif
