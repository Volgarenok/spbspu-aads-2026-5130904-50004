#ifndef GRAPH_H
#define GRAPH_H
#include "HashTable.h"
namespace khairullin {
    struct Graph {
        std::string name;
        Vector< std::string > vertexes;
        Vector< List<size_t> * > connection;
        HashTable< size_t, std::string, Hash< std::string> , Equal< std::pair<size_t, std::string> > > edges;

        Graph(const std::string & name);
        Graph();
        ~Graph();
        Graph(const Graph & other);
        Graph & operator=(const Graph & other);
        Graph(Graph && other);
        Graph & operator=(Graph && other);
        bool operator==(const Graph & other) const noexcept;

        std::pair<bool, size_t> hasVertex(const std::string & vert);
        void swap(Graph & graph);

        void addEdge(const std::string & vert1, const std::string & vert2, size_t weight);
        void cutEdge(const std::string & vert1, const std::string & vert2, size_t weight);
        void addVertex(const std::string & vert);
    };
}

khairullin::Graph::Graph():
name(""),
vertexes(Vector< std::string >()),
connection(Vector< List<size_t> * >()),
edges(HashTable< size_t, std::string, Hash< std::string> , Equal< std::pair<size_t, std::string> > >())
{}

khairullin::Graph::Graph(const Graph &other):
Graph(other.name)
{
    vertexes = other.vertexes;
    edges = other.edges;
    for (size_t i = 0; i < other.connection.getSize(); i++) {
        try {
            connection.pushBack(nullptr);
        }
        catch (...) {
            throw std::bad_alloc();
        }
        List< size_t > * head = nullptr;
        try {
            head = other.connection[i]->copy(other.connection[i]);
        }
        catch (...) {
            throw std::bad_alloc();
        }
        std::swap(connection[i], head);
    }
}

khairullin::Graph & khairullin::Graph::operator=(const Graph & other) {
    if (*this == other) {
        return *this;
    }
    Graph temp(other);
    swap(temp);
}

khairullin::Graph::Graph(Graph &&other):
Graph(other.name)
{
    vertexes.swap(other.vertexes);
    edges.swap(other.edges);
    connection.swap(other.connection);
}

khairullin::Graph & khairullin::Graph::operator=(Graph && other) {
    if (*this == other) {
        return *this;
    }
    auto temp(std::move(other));
    swap(temp);
}

khairullin::Graph::~Graph() {
    for (size_t i = 0; i < connection.getSize(); i++) {
        if (connection[i]) {
            connection[i]->clear(connection[i]);
        }
    }
}

khairullin::Graph::Graph(const std::string & name):
name(name),
vertexes(Vector< std::string >()),
connection(Vector< List<size_t> * >()),
edges(HashTable< size_t, std::string, Hash< std::string>, Equal< std::pair<size_t, std::string> > >())
{}

bool khairullin::Graph::operator==(const Graph &other) const noexcept {
    if (name != other.name || vertexes != other.vertexes || edges != other.edges) {
        return false;
    }
    if (connection.getSize() != other.connection.getSize()) {
        return false;
    }
    for (size_t i = 0; i < connection.getSize(); i++) {
        auto Slot = connection[i];
        auto otherSlot = other.connection[i];
        while (Slot && otherSlot) {
            if (Slot->value != otherSlot->value) {
                return false;
            }
            if (Slot != otherSlot) {
                return false;
            }
        }
    }
    return true;
}

std::pair<bool, size_t> khairullin::Graph::hasVertex(const std::string & vert) {
    for (size_t i = 0; i < vertexes.getSize(); i++) {
        if (vertexes[i] == vert) {
            return std::make_pair(true, i);
        }
    }
    return std::make_pair(false, 0);
}

void khairullin::Graph::swap(Graph & graph) {
    vertexes.swap(graph.vertexes);
    edges.swap(graph.edges);
    connection.swap(graph.connection);
    std::swap(name, graph.name);
}

void khairullin::Graph::addEdge(const std::string & vert1, const std::string & vert2, size_t weight) {
    std::string key = vert1 + vert2;
    std::pair<bool, size_t> infoVert1 = hasVertex(vert1);
    std::pair<bool, size_t> infoVert2 = hasVertex(vert2);
    if (!infoVert1.first || !infoVert2.first) {
        throw std::logic_error("<INVALID COMMAND>");
    }
    edges.add(key, weight);
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

void khairullin::Graph::cutEdge(const std::string & vert1, const std::string & vert2, size_t weight) {
    std::string key = vert1 + vert2;
    std::pair<bool, size_t> infoVert1 = hasVertex(vert1);
    std::pair<bool, size_t> infoVert2 = hasVertex(vert2);
    if (!infoVert1.first || !infoVert2.first) {
        throw std::logic_error("<INVALID COMMAND>");
    }
    List< size_t > * tail = connection[infoVert1.second];
    if (tail == nullptr) {
        throw std::logic_error("<INVALID COMMAND>");
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

    edges.cut(key, weight);

    /*size_t index = edges.findIndex(key);
    auto slot = edges.table[index];
    List< std::pair< size_t, std::string> > * prev = slot;
    while (slot && (slot->value.second != key && slot->value.first != weight)) {
        prev = slot;
        slot = slot->next;
    }
    if (slot && prev) {
        prev->next = slot->cut(slot);
    }
    else if (!prev && slot) {
        edges.table[index] = slot->cut(slot);
    }
    else {
        throw std::logic_error("<INVALID COMMAND>");
    } */
    std::cout << "Completed\n";
}

void khairullin::Graph::addVertex(const std::string & vert) {
    auto index = hasVertex(vert);
    if (index.first) {
        throw std::logic_error("<INVALID COMMAND>");
    }
    try {
        vertexes.pushBack(vert);
        connection.pushBack(nullptr);
    } catch (std::bad_alloc & e) {
        throw std::bad_alloc();
    }
}


#endif
