#ifndef TREE_TRAVERSE_HPP
#define TREE_TRAVERSE_HPP

#include "TreeNode.hpp"

namespace haliullin
{
  template< class Key, class Value >
  TreeNode< Key, Value >* fallLeft(TreeNode< Key, Value >* node) noexcept;

  template< class Key, class Value >
  TreeNode< Key, Value >* fallRight(TreeNode< Key, Value >* node) noexcept;

  template< class Key, class Value >
  TreeNode< Key, Value >* next(TreeNode< Key, Value >* node) noexcept;

  template< class Key, class Value >
  TreeNode< Key, Value >* previous(TreeNode< Key, Value >* node) noexcept;
}

template< class Key, class Value >
haliullin::TreeNode< Key, Value >* haliullin::fallLeft(TreeNode< Key, Value >* node) noexcept
{
  while (!node->left_->isFake())
  {
    node = node->left_;
  }
  return node;
}

template< class Key, class Value >
haliullin::TreeNode< Key, Value >* haliullin::fallRight(TreeNode< Key, Value >* node) noexcept
{
  while (!node->right_->isFake())
  {
    node = node->right_;
  }
  return node;
}

template< class Key, class Value >
haliullin::TreeNode< Key, Value >* haliullin::next(TreeNode< Key, Value >* node) noexcept
{
  if (!node->right_->isFake())
  {
    return fallLeft(node->right_);
  }

  TreeNode< Key, Value >* parent = node->parent_;
  while (parent && (parent->right_ == node))
  {
    node = parent;
    parent = parent->parent_;
  }
  return parent;
}

template< class Key, class Value >
haliullin::TreeNode< Key, Value >* haliullin::previous(TreeNode< Key, Value >* node) noexcept
{
  if (!node->left_->isFake())
  {
    return fallRight(node->left_);
  }

  TreeNode< Key, Value >* parent = node->parent_;
  while (parent && (parent->left_ == node))
  {
    node = parent;
    parent = parent->parent_;
  }
  return parent;
}

#endif
