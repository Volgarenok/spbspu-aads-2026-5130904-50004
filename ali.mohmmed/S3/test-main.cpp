#define BOOST_TEST_MODULE S3
#include <boost/test/included/unit_test.hpp>

#include "hash-table.hpp"
#include "siphash.hpp"
#include "graph.hpp"

namespace ali
{
  struct StringEqual
  {
    bool operator()(const std::string & a, const std::string & b) const
    {
      return a == b;
    }
  };
}

BOOST_AUTO_TEST_CASE(hash_table_test)
{
  ali::HashTable< std::string, int, ali::SipHash, ali::StringEqual > table;

  table.add("one", 1);
  table.add("two", 2);

  BOOST_TEST(table.get("one") == 1);
  BOOST_TEST(table.get("two") == 2);
}

BOOST_AUTO_TEST_CASE(graph_test)
{
  ali::Graph graph;

  graph.bind("a", "b", 10);

  BOOST_TEST(graph.has("a"));
  BOOST_TEST(graph.has("b"));
}
