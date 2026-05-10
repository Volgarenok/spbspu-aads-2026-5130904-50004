#if defined(__GNUC__) || defined(__clang__)
__attribute__((weak)) int main(int argc, char* argv[]);
#endif

#define BOOST_TEST_MODULE S2
#include <boost/test/included/unit_test.hpp>
#include "GraphSystem.h"

BOOST_AUTO_TEST_SUITE(main_test)
{
  khairullin::HashTable hashTable;
  BOOST_TEST(table);
}
