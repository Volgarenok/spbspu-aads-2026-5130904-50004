//
// Created by Vadim Khairullin on 5/5/26.
//

#ifndef GRAPH_H
#define GRAPH_H
#include "HashTable.h"
namespace khairullin {
    template< class T >
    struct Graph {
        std::string name;
        Vector< std::string > vertexes;
        HashTable< size_t, std::string, Hash, Equal< size_t > > edges;

        void addEdge(const std::string & vert1, const std::string & vert2, size_t weight);
        void cutEdge(const std::string & vert1, const std::string & vert2);

    };
}

#endif
