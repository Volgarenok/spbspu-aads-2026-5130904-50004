#ifndef LIST_H
#define LIST_H

template< class T >
struct List {
  T data;
  List< T > * next;
};

template< class T >
struct LIter {
  friend class List< T >;
  List< T > * node;

  LIter():
    node(nullptr)
  {
  }

  LIter< T > & operator++();
  LIter< T > operator++(int);

  T & operator*();
  T & operator->();

  bool operator==(const LIter< T > & other) const;
  bool operator!=(const LIter< T > & other) const;
};

template< class T >
struct LCIter {
  friend class List< T >;

  List< T > * node;

  LIter():
    node(nullptr)
  {
  }

  LIter< T > & operator++();
  LIter< T > operator++(int);

  T & operator*();
  T & operator->();

  bool operator==(const LIter< T > & other) const;
  bool operator!=(const LIter< T > & other) const;
};

template< class T >
List< T > * fake(List< T > * head)
{
  List< T > * fake_node = static_cast< List< T > * >(::operator new(sizeof(List< T > *)));
  fake_node->next = head;
  head->next = fake_node;
  return fake_node;
}

template< class T >
List< T > * rmfake(List< T > * fake_node)
{
  List< T > * head = fake_node->next;
  ::operator delete(fake_node);
  return head;
}

#endif
