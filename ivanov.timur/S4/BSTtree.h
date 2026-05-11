
#ifndef BSTTREE_H
#define BSTTREE_H
#include <stdexcept>
#include <utility>

template<class Key, class Value, class Compare> class BSTtree;

template<class Key, class Value, class Compare>
class BSTIterator {
private:
  friend class BSTtree<Key, Value, Compare>;
public:
  using tree = BSTtree<Key, Value, Compare>;
private:
  tree* ptr;
  explicit BSTIterator(const tree* p): ptr(p) {}
public:

};

template<class Key, class Value>
class BSTConstIterator {
private:
  friend class BSTtree<Key, Value, Compare>;
public:
  using tree = BSTtree<Key, Value, Compare>;
private:
  const tree* ptr;
  explicit BSTConstIterator(const tree* p): ptr(p) {}
public:

};

template<class Key, class Value, class Compare>
class BSTtree {
private:
  Value val;
  Key key;
  Compare comp;
  BSTtree *right, *left;
  BSTtree *parent;
  bool isFakeRoot;

  static BSTtree nil;

public:
  BSTtree(): left(&nil), right(&nil), parent(&nil), isFakeRoot(true) {}
  BSTtree(std::pair<Value, Key> init): val(init.first), key(init.second),
  right(&nil), left(&nil), parent(&nil), isFakeRoot(false) {}
  BSTtree(std::pair<Value, Key> init, BSTtree *parnt = nullptr): val(init.first), key(init.second),
  right(&nil), left(&nil), parent(parnt), isFakeRoot(false) {}
  ~BSTtree() = default;

  void push(const Key& k, const Value& v) {
    BSTtree *p = this;
    BSTtree *curr = left;
    while (curr != &nil) {
      p = curr;
      if (comp(k, curr->key)) curr = curr->left;
      else if (comp(curr->key, k)) curr = curr->right;
      else {
        curr->val = v;
        return;
      }
    }
    BSTtree *nw = new BSTtree(k, v, p);
    if (p == this || comp(p, p->key)) p->left = nw; //вставка
    else p->right = nw;

  }
  Value get(Key k) {
    BSTtree *curr = left; //первый же фейк?
    while (curr != &nil) {
      if (comp(k, curr->key)) curr = curr->left;
      else if (comp(curr->key, k)) curr = curr->right;
      else return curr->val;
    }
    throw std::out_of_range("No such element here");
  }
  Value drop(Key k) {
    BSTtree *curr = left;
    while (curr != &nil) {
      if (comp(k, curr->key)) curr = curr->left;
      else if (comp(curr->key, k)) curr = curr->right;
      else break;
    }
    if (curr == &nil) throw std::out_of_range("No such element here");

    Value rmv = curr->val;

    if (curr->left != &nil && curr->right != &nil) {
      BSTtree *mRight = curr->right;
      while (mRight->left != &nil) mRight = mRight->left;
      curr->val = mRight->val;
      curr = mRight;
      rmv = curr->val;
    }

    BSTtree *child = (curr->left != &nil) ? curr->left : curr->right;
    child->parent = curr->parent;
    if (curr->parent->left == curr) curr->parent->left = child;
    else curr->parent->right = child;

    delete curr;
    return rmv;
  }

  using const_iterator = BSTConstIterator<Key, Value>;
  const_iterator rotateLeft(const_iterator it);
  const_iterator rotateRight(const_iterator it);

  const_iterator rotateLargeLeft(const_iterator it);
  const_iterator rotateLargeRight(const_iterator it);

  size_t height(const_iterator it);
  size_t height();
};


#endif //BSTTREE_H
