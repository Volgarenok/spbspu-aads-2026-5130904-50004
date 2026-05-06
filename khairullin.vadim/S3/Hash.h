#ifndef HASH_H
#define HASH_H
namespace khairullin {
    template <class Key >
    struct Hash {
        Hash() = default;
        size_t operator()(const Key & key);
    };
}

template <class Key >
size_t khairullin::Hash< Key >::operator()(const Key & key) {
    return key.length();
}


#endif
