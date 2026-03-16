#ifndef LISTITERATORS1_H
#define LISTITERATORS1_H

#include "List.h"
#include <stdexcept>

namespace alekseev {
  template< class T, bool Is_const >
  struct ListIteratorBase {
    List< T > * node_;

    friend class List< T >;

    ListIteratorBase() = default;

    ListIteratorBase(List< T > * node);
    template< bool Other_Is_const >
    ListIteratorBase(ListIteratorBase< T, Other_Is_const > & other);

    ListIteratorBase & operator++();
    ListIteratorBase operator++(int);

    template< bool Other_Is_const >
    bool operator==(const ListIteratorBase< T, Other_Is_const > & other) const noexcept;

    template< bool Other_Is_const >
    bool operator!=(const ListIteratorBase< T, Other_Is_const > & other) const noexcept;

    T & operator*() const;
    T * operator->() const;

    ListIteratorBase & insert_after(T & value);
    ListIteratorBase & erase_after();
    ListIteratorBase & clear(ListIteratorBase & end);
  };

  template< class T, bool Is_const >
  ListIteratorBase< T, Is_const >::ListIteratorBase(List< T > * node):
    node_(node)
  {
  }

  template< class T, bool Is_const >
  template< bool Other_Is_const >
  ListIteratorBase<T, Is_const>::ListIteratorBase(ListIteratorBase<T, Other_Is_const> & other)
  {
    if (Other_Is_const && !Is_const) {
      throw std::logic_error("Cannot construct non-const iterator from const");
    }
    node_ = other.node_;
  }

  template< class T, bool Is_const >
  ListIteratorBase<T, Is_const> & ListIteratorBase<T, Is_const>::operator++()
  {
    node_ = node_->next;
    return *this;
  }

  template< class T, bool Is_const >
  ListIteratorBase<T, Is_const> ListIteratorBase<T, Is_const>::operator++(int)
  {
    ListIteratorBase<T, Is_const> tmp = *this;
    node_ = node_->next;
    return tmp;
  }

  template< class T, bool Is_const >
  template< bool Other_Is_const >
  bool ListIteratorBase<T, Is_const>::operator==(
      const ListIteratorBase<T, Other_Is_const> & other) const noexcept
  {
    return node_ == other.node_;
  }

  template< class T, bool Is_const >
  template< bool Other_Is_const >
  bool ListIteratorBase<T, Is_const>::operator!=(
      const ListIteratorBase<T, Other_Is_const> & other) const noexcept
  {
    return node_ != other.node_;
  }

  template< class T, bool Is_const >
  ListIteratorBase<T, Is_const> ListIteratorBase<T, Is_const>::insert_after(T & value)
  {
    if (Is_const) {
      throw std::logic_error("this action is not available with the const iterator");
    }
    node_ = insert_after(node_, value);
    return *this;
  }

  template< class T, bool Is_const >
  ListIteratorBase<T, Is_const> ListIteratorBase<T, Is_const>::erase_after()
  {
    node_ = erase_after(node_);
    return *this;
  }

  template< class T, bool Is_const >
  ListIteratorBase<T, Is_const> ListIteratorBase<T, Is_const>::clear(ListIteratorBase & end)
  {
    node_ = clear(node_, end.node_);
    return *this;
  }

  template< class T >
  using LIter = ListIteratorBase< T, false >;
  template< class T >
  using LCIter = ListIteratorBase< T, true >;
}

#endif
