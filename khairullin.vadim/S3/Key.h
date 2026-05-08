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


while (tail && tail->next && tail->next->value != infoVert2.second) {
    tail = tail->next;
}
if (tail && tail->next) {
    tail->next = tail->cut(tail->next);
    connection[infoVert1.second] = head;
}
else if (tail == head) {
    connection[infoVert1.second] = tail->cut(tail);
}
else {
    throw std::logic_error("This edge does not exist");
}