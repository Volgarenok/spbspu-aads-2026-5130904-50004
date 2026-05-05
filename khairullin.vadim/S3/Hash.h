#ifndef HASH_H
#define HASH_H
#include "Key.h"

namespace khairullin {
    struct Hash {
        Hash() = default;
        size_t operator()(Key & key) const;
    };
}

size_t khairullin::Hash::operator()(Key & key) const {
    return (key.getKey()).length();
}


#endif
