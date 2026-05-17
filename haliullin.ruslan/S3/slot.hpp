#ifndef SLOT_HPP
#define SLOT_HPP

namespace haliullin
{
  template< class Key, class Value >
  struct Slot
  {
    Key key_;
    Value value_;
    char info_; //'e' - empty, 'o' - occupied, 't' - tombstone

    Slot() noexcept:
      key_(),
      value_(),
      info_('e')
    {}
  };
}

#endif
