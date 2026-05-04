//
// Created by Vadim Khairullin on 5/4/26.
//

#ifndef KEY_H
#define KEY_H
#include <string>

namespace khairullin {
    struct Key {
        std::string getKey();

        Key();
        Key(const std::string & key);
    private:
        std::string key;
    };
}

khairullin::Key::Key(const std::string & key):
key(key)
{}

khairullin::Key::Key():
key("")
{}

std::string khairullin::Key::getKey() {
    return key;
}
#endif
