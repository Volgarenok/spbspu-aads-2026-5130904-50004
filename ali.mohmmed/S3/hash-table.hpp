#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <cstddef>
#include <stdexcept>

namespace ali
{
  enum SlotState
  {
    EMPTY,
    BUSY,
    DELETED
  };

  template< class Key, class Value, class Hash, class Equal >
  class HashTable
  {
  private:
    struct Slot
    {
      Key key;
      Value value;
      SlotState state;

      Slot():
        key(),
        value(),
        state(EMPTY)
      {}
    };

    Slot * data_;
    std::size_t capacity_;
    std::size_t size_;
    Hash hash_;
    Equal equal_;

  public:
    HashTable(std::size_t capacity = 101):
      data_(new Slot[capacity]),
      capacity_(capacity),
      size_(0),
      hash_(),
      equal_()
    {}

    ~HashTable()
    {
      delete[] data_;
    }

    bool has(const Key & key) const
    {
      std::size_t index = hash_(key) % capacity_;

      for (std::size_t i = 0; i < capacity_; ++i)
      {
        std::size_t pos = (index + i) % capacity_;

        if (data_[pos].state == EMPTY)
        {
          return false;
        }

        if (data_[pos].state == BUSY && equal_(data_[pos].key, key))
        {
          return true;
        }
      }

      return false;
    }

    Value & get(const Key & key)
    {
      std::size_t index = hash_(key) % capacity_;

      for (std::size_t i = 0; i < capacity_; ++i)
      {
        std::size_t pos = (index + i) % capacity_;

        if (data_[pos].state == EMPTY)
        {
          break;
        }

        if (data_[pos].state == BUSY && equal_(data_[pos].key, key))
        {
          return data_[pos].value;
        }
      }

      throw std::logic_error("key not found");
    }

    void add(const Key & key, const Value & value)
    {
      if (size_ == capacity_)
      {
        throw std::logic_error("hash table is full");
      }

      std::size_t index = hash_(key) % capacity_;
      std::size_t firstDeleted = capacity_;

      for (std::size_t i = 0; i < capacity_; ++i)
      {
        std::size_t pos = (index + i) % capacity_;

        if (data_[pos].state == BUSY && equal_(data_[pos].key, key))
        {
          data_[pos].value = value;
          return;
        }

        if (data_[pos].state == DELETED && firstDeleted == capacity_)
        {
          firstDeleted = pos;
        }

        if (data_[pos].state == EMPTY)
        {
          if (firstDeleted != capacity_)
          {
            pos = firstDeleted;
          }

          data_[pos].key = key;
          data_[pos].value = value;
          data_[pos].state = BUSY;
          ++size_;
          return;
        }
      }

      if (firstDeleted != capacity_)
      {
        data_[firstDeleted].key = key;
        data_[firstDeleted].value = value;
        data_[firstDeleted].state = BUSY;
        ++size_;
        return;
      }

      throw std::logic_error("hash table is full");
    }

    Value drop(const Key & key)
    {
      std::size_t index = hash_(key) % capacity_;

      for (std::size_t i = 0; i < capacity_; ++i)
      {
        std::size_t pos = (index + i) % capacity_;

        if (data_[pos].state == EMPTY)
        {
          break;
        }

        if (data_[pos].state == BUSY && equal_(data_[pos].key, key))
        {
          Value value = data_[pos].value;
          data_[pos].state = DELETED;
          --size_;
          return value;
        }
      }

      throw std::logic_error("key not found");
    }

    std::size_t size() const
    {
      return size_;
    }
  };
}

#endif
