
#ifndef BSTTREE_H
#define BSTTREE_H
#include <stdexcept>
#include <utility>

template<class Key, class Value, class Compare> class BSTtree;
template<class Key, class Value, class Compare> class BSTConstIterator;

template<class Key, class Value, class Compare>
class BSTIterator {
private:
  friend class BSTtree<Key, Value, Compare>;
public:
  using tree = BSTtree<Key, Value, Compare>;
private:
  tree* ptr;
  explicit BSTIterator(tree* p): ptr(p) {}

public:
  BSTIterator(): ptr(nullptr) {}
  operator BSTConstIterator<Key, Value, Compare>() const {
    return BSTConstIterator<Key, Value, Compare>(ptr);
  }

  bool operator==(const BSTIterator& other) const {
    return ptr == other.ptr;
  }
  bool operator!=(const BSTIterator& other) const {
    return !operator==(other);
  }

  std::pair<const Key&, Value&> operator*() const {
    return {ptr->key, ptr->val};
  }

  BSTIterator& operator++() {
    if (!(ptr->isFakeRoot) && ptr->right != &tree::nil) {
      ptr = ptr->right;
      while (ptr->left != &tree::nil) ptr = ptr->left;
    } else {
      tree* parent = ptr->parent;
      while (parent != &tree::nil && ptr == parent->right) {
        ptr = parent;
        parent = parent->parent;
      }
      ptr = parent;
    }
    return *this;
  }
  BSTIterator operator++(int) {
    BSTIterator tmp = *this;
    ++*this;
    return tmp;
  }
};

template<class Key, class Value, class Compare>
class BSTConstIterator {
private:
  friend class BSTtree<Key, Value, Compare>;
public:
  using tree = BSTtree<Key, Value, Compare>;
private:
  const tree* ptr;
  explicit BSTConstIterator(const tree* p): ptr(p) {}
public:
  BSTConstIterator(): ptr(nullptr) {}
  bool operator==(const BSTConstIterator& other) const {
    return ptr == other.ptr;
  }
  bool operator!=(const BSTConstIterator& other) const {
    return !operator==(other);
  }

  std::pair<const Key&, Value&> operator*() const {
    return {ptr->key, ptr->val};
  }

  BSTConstIterator& operator++() {
    if (!(ptr->isFakeRoot) && ptr->right != &tree::nil) {
      ptr = ptr->right;
      while (ptr->left !=  &tree::nil) ptr = ptr->left;
    } else {
      const tree* parent = ptr->parent;
      while (parent != &tree::nil && ptr == parent->right) {
        ptr = parent;
        parent = parent->parent;
      }
      ptr = parent;
    }
    return *this;
  }
  BSTConstIterator& operator++(int) {
    BSTConstIterator tmp = *this;
    ++*this;
    return tmp;
  }
};

template<class Key, class Value, class Compare>
class BSTtree {
private:
  friend class BSTIterator<Key, Value, Compare>;
  using iterator = BSTIterator<Key, Value, Compare>;
  friend class BSTConstIterator<Key, Value, Compare>;
  using const_iterator = BSTConstIterator<Key, Value, Compare>;

  Value val;
  Key key;
  Compare comp;
  BSTtree *right, *left;
  BSTtree *parent;
  bool isFakeRoot;

  static BSTtree nil;

  size_t subHg(const BSTtree *tree) const {
    if (tree == &nil) return 0;
    size_t leftH = subHg(tree->left);
    size_t rightH = subHg(tree->right);
    return 1 + std::max(leftH, rightH);
  }

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

  iterator begin() {
    if (left == &nil) return iterator(this);
    BSTtree* cur = left;
    while (cur->left != &nil) cur = cur->left;
    return iterator(cur);
  }
  const_iterator begin() const {
    if (left == &nil) return const_iterator(this);
    const BSTtree* cur = left;
    while (cur->left != &nil) cur = cur->left;
    return const_iterator(cur);
  }
  iterator end() {
    return iterator(this);
  }
  const_iterator end() const {
    return const_iterator(this);
  }
  const_iterator cbegin() const { return begin(); }
  const_iterator cend() const { return end(); }

  const_iterator rotateLeft(const_iterator it);
  const_iterator rotateRight(const_iterator it);

  const_iterator rotateLargeLeft(const_iterator it);
  const_iterator rotateLargeRight(const_iterator it);

  size_t height(const_iterator it) {
    if (it.ptr->isFakeRoot) return height();
    return subHg(it.ptr);
  }
  size_t height() const {
    return subHg(left);
  }
};


#endif //BSTTREE_H
