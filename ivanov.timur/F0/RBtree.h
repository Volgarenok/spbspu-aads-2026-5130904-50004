#ifndef RBTREE_H
#define RBTREE_H

template <class Key, class Value>
class RBtree {
private:

  struct Node {
    Key key;
    Value val;
    bool color; //true - true, false - false
    Node *left;
    Node *right;
    Node *parent;

    Node(const Key& k, const Value& v, bool c = true)
        : key(k), val(v), color(c), left(nullptr), right(nullptr), parent(nullptr) {}
  };

  Node *root;
  Node *NIL;

  void leftRotate(Node *x) {
    Node *y = x->right;
    x->right = y->left;
    if (y->left != NIL)
      y->left->parent = x;

    y->parent = x->parent;
    if (x->parent == NIL)
      root = y;
    else if (x == x->parent->left)
      x->parent->left = y;
    else
      x->parent->right = y;

    y->left = x;
    x->parent = y;
  }

  void rightRotate(Node *x) {
    Node *y = x->left;
    x->left = y->right;
    if (y->right != NIL)
      y->right->parent = x;

    y->parent = x->parent;
    if (x->parent == NIL)
      root = y;
    else if (x == x->parent->right)
      x->parent->right = y;
    else
      x->parent->left = y;

    y->right = x;
    x->parent = y;
  }
  void insertFixUp(Node *z) {
    while (z->parent->colour == true) {
      if (z->parent == z->parent->parent->left) {   // родитель — левый
        Node *y = z->parent->parent->right;
        //дядя красный
        if (y->colour == true) {
          z->parent->colour = false;
          y->colour = false;
          z->parent->parent->colour = true;
          z = z->parent->parent;
        } else {
          //дядя чёрный, z — правый потомок
          if (z == z->parent->right) {
            z = z->parent;
            leftRotate(z);
          }
          //дядя чёрный, z — левый потомок
          z->parent->colour = false;
          z->parent->parent->colour = true;
          rightRotate(z->parent->parent);
        }
      } else { // родитель — правый
        Node *y = z->parent->parent->left;
        if (y->colour == true) {
          z->parent->colour = false;
          y->colour = false;
          z->parent->parent->colour = true;
          z = z->parent->parent;
        } else {
          if (z == z->parent->left) {
            z = z->parent;
            rightRotate(z);
          }
          z->parent->colour = false;
          z->parent->parent->colour = true;
          leftRotate(z->parent->parent);
        }
      }
    }
    root->colour = false;
  }

public:
};

#endif
