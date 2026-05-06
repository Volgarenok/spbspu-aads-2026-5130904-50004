#ifndef GRAPH_H
#define GRAPH_H
#include "HashTable.h"
namespace khairullin {
    struct Graph {
        std::string name;
        Vector< std::string > vertexes;
        Vector< List<size_t> * > connection;
        HashTable< size_t, std::string, Hash< std::string> , Equal< size_t > > edges;

        Graph(const std::string & name);
        Graph();

        std::pair<bool, size_t> hasVertex(const std::string & vert);

        void addEdge(const std::string & vert1, const std::string & vert2, size_t weight);
        void cutEdge(const std::string & vert1, const std::string & vert2);
        void addVertex(const std::string & vert);
    };
}

khairullin::Graph::Graph():
name(""),
vertexes(Vector< std::string >()),
edges(HashTable< size_t, std::string, Hash< std::string> , Equal< size_t > >())
{}

khairullin::Graph::Graph(const std::string & name):
name(name),
vertexes(Vector< std::string >()),
edges(HashTable< size_t, std::string, Hash< std::string>, Equal< size_t > >())
{}

std::pair<bool, size_t> khairullin::Graph::hasVertex(const std::string & vert) {
    for (size_t i = 0; i < vertexes.getSize(); i++) {
        if (vertexes[i] == vert) {
            return std::make_pair(true, i);
        }
    }
    return std::make_pair(false, 0);
}

void khairullin::Graph::addEdge(const std::string & vert1, const std::string & vert2, size_t weight) {
    std::string key = vert1 + vert2;
    std::pair<bool, size_t> infoVert1 = hasVertex(vert1);
    std::pair<bool, size_t> infoVert2 = hasVertex(vert2);
    if (infoVert1.first == infoVert2.first) {
        edges.add(key, weight);
    }
    size_t index1 = infoVert1.second;
    size_t index2 = infoVert2.second;
    if (connection[index1] == nullptr) {
        connection[index1] = new List<size_t>(index2, nullptr);
    }
    else {
        auto tail = connection[index1];
        while (tail->next) {
            tail = tail->next;
        }
        tail->insert(index2, tail);
    }
}

void khairullin::Graph::cutEdge(const std::string & vert1, const std::string & vert2) {
    std::string key = vert1 + vert2;
    std::pair<bool, size_t> infoVert1 = hasVertex(vert1);
    std::pair<bool, size_t> infoVert2 = hasVertex(vert2);
    if (!infoVert1.first || !infoVert2.first) {
        throw std::logic_error("This vertex does not exist");
    }

    List< size_t > * tail = connection[infoVert1.second];
    if (tail == nullptr) {
        throw std::logic_error("This edge does not exist");
    }
    else if (tail->next == nullptr) {
        connection[infoVert1.second] = tail->cut(tail);
    }
    else {
        auto previous = tail;
        while (tail) {
            if (tail->value == infoVert2.second) {
                break;
            }
            previous = tail;
            tail = tail->next;
        }
        if (previous != tail) {
            previous->next = tail->cut(tail);
        } else {
            connection[infoVert1.second] = tail->cut(tail);
        }
    }

    size_t index = edges.findIndex(key);
    auto slot = edges.table[index];
    List< std::pair< size_t, std::string> > * prev = slot;
    while (slot && slot->value.second != key) {
        prev = slot;
        slot = slot->next;
    }
    if (slot && prev) {
        prev->next = slot->cut(slot);
    }
    else {
        throw std::logic_error("This edge does not exist");
    }
    std::cout << "Completed\n";
}

void khairullin::Graph::addVertex(const std::string & vert) {
    vertexes.pushBack(vert);
    connection.pushBack(nullptr);
}


#endif
