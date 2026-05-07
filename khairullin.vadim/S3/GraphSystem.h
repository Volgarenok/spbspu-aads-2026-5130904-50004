#ifndef GRAPHSYSTEM_H
#define GRAPHSYSTEM_H
#include <iostream>
#include <ostream>
#include "Functions.h"

#include "Graph.h"
namespace khairullin {
    struct GraphSystem {
        using func_t = void(GraphSystem::*)(std::string & line);
        Vector< Graph > vectorOfGraphs;
        HashTable<func_t, std::string, Hash<std::string>, Equal<func_t>> functions;

        void func(std::string & function, std::string & line);
        std::pair<bool, size_t> graphExists(std::string & name);

        void graphs(std::string & line);
        void vertexes(std::string & line);
        void outbound(std::string & line);
        void inbound(std::string & line);
        void bind(std::string & line);
        void cut (std::string & line);
        void create(std::string & line);
        void merge(std::string & line);
        void extract(std::string & line);

    };
}

void khairullin::GraphSystem::func(std::string & function, std::string & line) {
    auto method = functions.drop(function);
    (this->*method)(line);
}

void khairullin::GraphSystem::graphs(std::string &line) {
    for (size_t i = 0; i < vectorOfGraphs.getSize(); i++) {
        std::cout << vectorOfGraphs[i].name << "\n";
    }
}

std::pair<bool, size_t > khairullin::GraphSystem::graphExists(std::string &name) {
    for (size_t i = 0; i < vectorOfGraphs.getSize(); i++) {
        if (vectorOfGraphs[i].name == name) {
            return std::make_pair(true, i);
        }
    }
    return std::make_pair(false, 0);
}

void khairullin::GraphSystem::vertexes(std::string &line) {
    std::pair< bool, size_t > result = graphExists(line);
    if (!result.first) {
        throw std::logic_error("<INVALID COMMAND>");
    }
    Graph graph = vectorOfGraphs[result.second];
    for (size_t i = 0; i < graph.vertexes.getSize(); i++) {
        std::cout << graph.vertexes[i] << "\n";
    }
}

void khairullin::GraphSystem::outbound(std::string & line) {
    std::string nameGraph = getToken(line);
    std::string vertex = getToken(line);
    std::pair< bool, size_t > index = graphExists(nameGraph);
    if (!index.first) {
        throw std::logic_error("<INVALID COMMAND>");
    }
    Graph graph = vectorOfGraphs[index.second];
    auto infoVert = graph.hasVertex(vertex);
    if (!infoVert.first) {
        throw std::logic_error("<INVALID COMMAND>");
    }
    List< size_t > * head = graph.connection[infoVert.second];
    Vector< std::pair< std::string, size_t > > vertices;
    while (head) {
        std::string temp = graph.vertexes[head->value];
        size_t weight = graph.edges.drop(vertex + temp);
        vertices.push_back(std::make_pair(temp, weight));
        head = head->next;
    }
    sortPair(vertices);
    for (size_t i = 0; i < vertices.getSize(); i++) {
        std::cout << vertices[i].first << " " << vertices[i].second << "\n";
    }
}

#endif
