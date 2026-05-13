#ifndef EQUAL_HPP
#define EQUAL_HPP

namespace haliullin
{
  struct Equal
  {
    template< class T >
    bool operator()(const T& lhs, const T& rhs) const noexcept
    {
      return lhs == rhs;
    }
  };
}

#endif
