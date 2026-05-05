#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "List.h"
#include "Vector.h"
#include "Equal.h"
#include "Hash.h"
#include "Key.h"

namespace khairullin {
    template< class T, class Key, class Hash, class Equal >
    struct HashTable {
        Vector< List< std::pair<T, Key> > * > table;
        Equal equal;
        Hash hasher;

        void add(const Key & key, const T & value);
        T drop(const Key & key);
        bool has(const Key & key);
        void rehash(size_t new_size);

        HashTable();
        HashTable(size_t size);
        ~HashTable() = default;

    private:
        size_t size = 11;
        size_t count = 0;
    };
}

template< class T, class Key, class Hash, class Equal >
khairullin::HashTable< T, Key, Hash, Equal >::HashTable():
table(Vector< List< std::pair<T, Key> > * >(11, nullptr)),
equal(Equal()),
hasher(Hash())
{}

template< class T, class Key, class Hash, class Equal >
khairullin::HashTable<T, Key, Hash, Equal >::HashTable(size_t size):
table(Vector< List< std::pair<T, Key> > * >(size, nullptr)),
equal(Equal()),
hasher(Hash())
{}

template< class T, class Key, class Hash, class Equal >
void khairullin::HashTable< T, Key, Hash, Equal >::add(const Key & key, const T & value) {
    size_t index = hasher(key) % size;
    if (table[index] == nullptr) {
        table[index] = new List< T >(value, nullptr);
    }
    else {
        auto tail = table[index];
        while (tail->next != nullptr) {
            tail = tail->next;
        }
        tail->insert(std::make_pair(value, key), tail);
    }
    count++;
}

template< class T, class Key, class Hash, class Equal >
T khairullin::HashTable< T, Key, Hash, Equal >::drop(const Key & key) {
    size_t index = hasher(key) % size;
    auto slot = table[index];
    if (!has(key)) {
        throw std::logic_error("This element doesn't exist");
    }
    else {
        while (slot->value.second != key.getKey()) {
            slot = slot->next;
        }
    }
    return slot->value.first;
}

template< class T, class Key, class Hash, class Equal >
bool khairullin::HashTable< T, Key, Hash, Equal >::has(const Key & key) {
    size_t index = hasher(key) % size;
    auto slot = table[index];
    while (slot->value.second != key.getKey()) {
        slot = slot->next;
    }
    return slot;
}

template< class T, class Key, class Hash, class Equal >
void khairullin::HashTable< T, Key, Hash, Equal >::rehash(size_t new_size) {
    Vector< List< std::pair<T, Key> > * > new_table;
    try {
        new_table = Vector< List< std::pair<T, Key> > * >(new_size, nullptr);
    }
    catch (...) {
        throw std::bad_alloc();
    }
    for (size_t i = 0; i < size; i++) {
        auto slot = table[i];
        while (slot != nullptr) {
            size_t index = hasher(slot->value.second) % new_size;
            if (new_table[index] == nullptr) {
                new_table[index] = new List< std::pair<T, Key> >(std::make_pair(slot->value.first,
                    slot->value.second), nullptr);
            }
            else {
                auto tail = new_table[index];
                while (tail->next != nullptr) {
                    tail = tail->next;
                }
                tail->insert(std::make_pair(slot->value.first, slot->value.second), tail);
            }
            slot = slot->next;
        }
    }
    try {
        table = new_table;
        size = new_size;
    }
    catch (...) {
        throw std::bad_alloc();
    }
}

#endif
