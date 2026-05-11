#ifndef XXHASH_HPP
#define XXHASH_HPP
#include <cstddef>
#include <cstdint>
#include <cstring>

namespace xxhash_impl {

static constexpr uint32_t PRIME1 = 0x9E3779B1u;
static constexpr uint32_t PRIME2 = 0x85EBCA77u;
static constexpr uint32_t PRIME3 = 0xC2B2AE3Du;
static constexpr uint32_t PRIME4 = 0x27D4EB2Fu;
static constexpr uint32_t PRIME5 = 0x165667B1u;
inline uint32_t
rotl32(uint32_t x, int r)
{
  return (x << r) | (x >> (32 - r));
}
