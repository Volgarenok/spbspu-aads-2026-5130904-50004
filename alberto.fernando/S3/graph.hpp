#ifndef GRAPH_HPP
#define GRAPH_HPP
#include "hashtable.hpp"
#include "slist.hpp"
#include <algorithm>
#include <string>
#include <utility>
#include <vector>

namespace alberto {

using EdgeKey     = std::pair< std::string, std::string >;
using WeightList  = SList< unsigned >;
using EdgeTable   = HashTable< EdgeKey, WeightList, pair_hash, pair_equal >;
using VertexTable = HashTable< std::string, bool, xx_hash >;
