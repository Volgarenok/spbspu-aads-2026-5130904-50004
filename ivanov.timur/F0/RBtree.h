#ifndef RBTREE_H
#define RBTREE_H

template <class Key, class Value>
class RBtree {
private:

  struct Node {
    Key key;
    Value val;
    bool color; //red - true, black - false
    Node *left;
    Node *right;
    Node *parent;

    Node(const Key& k, const Value& v, bool c = true)
        : key(k), val(v), color(c), left(nullptr), right(nullptr), parent(nullptr) {}
  };

  Node *root;
  Node *NIL;
public:
};

#endif
