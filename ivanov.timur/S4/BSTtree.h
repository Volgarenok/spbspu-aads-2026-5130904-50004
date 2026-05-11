
#ifndef BSTTREE_H
#define BSTTREE_H
#include <utility>

template<class Key, class Value>
class BSTIterator {
  ...
};

template<class Key, class Value>
class BSTConstIterator {
  ...
};

template<class Key, class Value, class Compare>
class BSTtree {
  Value val;
  Key key;
  BSTtree *right, *left;
  BSTtree *parent;

public:
  BSTtree(std::pair<Value, Key> init): val(init.first), key(init.second),
  right(nullptr), left(nullptr), parent(nullptr) {}
  ~BSTtree() = default;

  void push(Key k, Value v);
  Value get(Key k);
  Value drop(Key k);

  using const_iterator = BSTConstIterator<Key, Value>;
  const_iterator rotateLeft(const_iterator it);
  const_iterator rotateRight(const_iterator it);

  const_iterator rotateLargeLeft(const_iterator it);
  const_iterator rotateLargeRight(const_iterator it);

  size_t height(const_iterator it);
  size_t height();
};


#endif //BSTTREE_H
