#ifndef SIPHASH_HPP
#define SIPHASH_HPP

#include <boost/container_hash/hash.hpp>
#include <cstddef>

namespace haliullin
{
  struct SipHash
  {
    template< class T >
    size_t operator()(const T& key) const noexcept
    {
      return boost::hash< T >()(key);
    }
  };
}

#endif
