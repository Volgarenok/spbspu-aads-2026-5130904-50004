namespace zinoviev
{
  template <class Key, class Value,  class Compare>
  class BSTree
  {
    struct Node
    {
      Key key_;
      Value value_;

      Node* left_;
      Node* right_;
      Node* parent_;

      Node(const Key& k, const Value& val, Node* p) :
        key_(k),
        value_(val),
        left_(nullptr),
        right_(nullptr),
        parent_(p)
      {}
    };

    Node* root_;
    size_t size_;
    Compare compare_;

   public:

    class Iterator
    {};

    class CIterator
    {};

    BSTree(Compare& com)
      root_(nullptr),
      size_(0),
      compare_(com)
    {}
  };
}
