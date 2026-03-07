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
List< T > * fake()
{
  List< T > * fake_node = static_cast< List< T > * >(::operator new(sizeof(List< T > *)));
  fake_node->next = fake_node;
  return fake_node;
}

template< class T >
List< T > * rmfake(List< T > * fake_node)
{
  List< T > * head = fake_node->next;
  ::operator delete(fake_node);
  return head;
}

template< class T >
List< T > add(List< T > * element, const T & value)
{
  List< T > * new_node = new List< T >();
  new_node->data = value;
  new_node->next = element->next;
  element->next = new_node;
  return new_node;
}

template< class T >
List< T > insert(List< T > * element, const T & value)
{
  element->next->data = value;
  return element->next;
}

#endif
