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
    Graph graph;
    try {
        graph = vectorOfGraphs[index.second];
    }
    catch (std::bad_alloc & e) {
        throw;
    }
    Vector< std::pair< std::string, Vector< size_t > > > vertices;
    auto infoVertex = graph.hasVertex(vertex);
    if (!infoVertex.first) {
        throw std::logic_error("<INVALID COMMAND>");
    }
    List< size_t > * head = graph.connection[infoVertex.second];
    while (head) {
        Vector< size_t > Weights;
        std::string temp = graph.vertexes[head->value];
        if (hasInPair(vertices, temp)) {
            head = head->next;
            continue;
        }
        size_t indexEdge = graph.edges.findIndex(vertex + temp);
        auto slot = graph.edges.table[indexEdge];
        while (slot) {
            if (slot->value.second == vertex + temp) {
                try {
                    Weights.pushBack(slot->value.first);
                }
                catch (std::bad_alloc & e) {
                    throw;
                }
            }
            slot = slot->next;
        }
        try {
            vertices.pushBack(std::make_pair(temp, Weights));
        } catch (std::bad_alloc & e) {
            throw;
        }
    }

    for (size_t i = 0; i < vertices.getSize(); i++) {
        std::cout << vertices[i].first << " ";
        sortVector(vertices[i].second);
        for (size_t j = 0; j < vertices[i].second.getSize(); j++) {
            std::cout << vertices[i].second[j] << " ";
        }
        std::cout << "\n";
    }
}

void khairullin::GraphSystem::inbound(std::string & line) {
    std::string nameGraph = getToken(line);
    std::string vertex = getToken(line);
    auto index = graphExists(nameGraph);
    if (!index.first) {
        throw std::logic_error("<INVALID COMMAND>");
    }
    Graph graph;
    try {
        graph = vectorOfGraphs[index.second];
    }
    catch (std::bad_alloc & e) {
        throw;
    }
    Vector< std::pair< std::string, Vector< size_t > > > vertices;
    auto infoVertex = graph.hasVertex(vertex);
    if (!infoVertex.first) {
        std::cout << "<INVALID COMMAND>\n";
        return;
    }
    for (size_t i = 0; i < graph.vertexes.getSize(); i++) {
        List< size_t > * head = graph.connection[infoVertex.second];
        while (head) {
            std::string temp = graph.vertexes[head->value];
            Vector< size_t > Weights;
            if (temp == vertex) {
                size_t indexEdge = graph.edges.findIndex(graph.vertexes[i] + vertex);
                auto slot = graph.edges.table[indexEdge];
                while (slot) {
                    if (slot->value.second == graph.vertexes[i] + vertex) {
                        try {
                            Weights.pushBack(slot->value.first);
                        }
                        catch (std::bad_alloc & e) {
                            throw;
                        }
                    }
                    slot = slot->next;
                }
                try {
                    vertices.pushBack(std::make_pair(temp, Weights));
                }
                catch (std::bad_alloc & e) {
                    throw;
                }
            }
            head = head->next;
        }
    }
    for (size_t i = 0; i < vertices.getSize(); i++) {
        std::cout << vertices[i].first << " ";
        sortVector(vertices[i].second);
        for (size_t j = 0; j < vertices[i].second.getSize(); j++) {
            std::cout << vertices[i].second[j] << " ";
        }
        std::cout << "\n";
    }
}

void khairullin::GraphSystem::bind(std::string & line) {
    std::string graph = getToken(line);
    std::string Vertex1 = getToken(line);
    std::string Vertex2 = getToken(line);
    size_t weight = 0;
    auto infoGraph = graphExists(graph);
    if (!infoGraph.first) {
        std::cout << "<INVALID COMMAND>\n";
        return;
    }
    try {
        weight = std::stoi(getToken(line));
    }
    catch (...) {
        std::cout << "<INVALID COMMAND>\n";
        return;
    }
    try {
        vectorOfGraphs[infoGraph.second].addEdge(Vertex1, Vertex2, weight);
    }
    catch (std::logic_error & e) {
        std::cout << e.what() << "\n";
    }
}

void khairullin::GraphSystem::cut(std::string & line) {
    std::string graph = getToken(line);
    std::string Vertex1 = getToken(line);
    std::string Vertex2 = getToken(line);
    size_t weight = 0;
    auto infoGraph = graphExists(graph);
    if (!infoGraph.first) {
        std::cout << "<INVALID COMMAND>\n";
        return;
    }
    try {
        weight = std::stoi(getToken(line));
    }
    catch (...) {
        std::cout << "<INVALID COMMAND>\n";
    }
    try {
        vectorOfGraphs[infoGraph.second].cutEdge(Vertex1, Vertex2, weight);
    }
    catch (std::logic_error & e) {
        std::cout << e.what() << "\n";
    }
}

void khairullin::GraphSystem::create(std::string & line) {
    std::string nameGraph = getToken(line);
    auto infoGraph = graphExists(nameGraph);
    if (!infoGraph.first) {
        std::cout << "<INVALID COMMAND>\n";
        return;
    }
    size_t count = 0;
    try {
        count = std::stoi(getToken(line));
    }
    catch (...) {
        std::cout << "<INVALID COMMAND>\n";
        return;
    }
    Graph graph;
    for (size_t i = 0; i < count; i++) {
        std::string vertex = getToken(line);
        try {
            if (vertex == "") {
                throw std::logic_error("<INVALID COMMAND>");
            }
            graph.addVertex(vertex);
        }
        catch (std::logic_error & e) {
            std::cout << e.what() << "\n";
        }
    }
    try {
        vectorOfGraphs.pushBack(graph);
    }
    catch (...) {
        throw;
    }
}



#endif
