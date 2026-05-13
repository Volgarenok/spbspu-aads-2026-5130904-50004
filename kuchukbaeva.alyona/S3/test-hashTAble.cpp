#include <boost/test/unit_test.hpp>
#include "hashTable.hpp"

BOOST_AUTO_TEST_CASE(testAddAndHas)
{
  kuchukbaeva::HashTable< std::string, int > ht(16);
  ht.add("test1", 100);
  ht.add("test2", 200);

  BOOST_CHECK(ht.has("test1"));
  BOOST_CHECK(ht.has("test2"));
  BOOST_CHECK(!ht.has("test3"));
}

BOOST_AUTO_TEST_CASE(testFindAndModify)
{
  kuchukbaeva::HashTable< std::string, int > ht(16);
  ht.add("key1", 5);
  int* valPtr = ht.find("key1");
  BOOST_REQUIRE(valPtr != nullptr);
  BOOST_CHECK_EQUAL(*valPtr, 5);

  *valPtr = 15;
  BOOST_CHECK_EQUAL(*(ht.find("key1")), 15);
}

BOOST_AUTO_TEST_CASE(testDrop)
{
  kuchukbaeva::HashTable< std::string, int > ht(16);
  ht.add("removeMe", 99);
  BOOST_CHECK(ht.has("removeMe"));

  bool result = ht.drop("removeMe");
  BOOST_CHECK(result);
  BOOST_CHECK(!ht.has("removeMe"));

  bool resultFalse = ht.drop("notThere");
  BOOST_CHECK(!resultFalse);
}

BOOST_AUTO_TEST_CASE(testRehash)
{
  kuchukbaeva::HashTable< std::string, int > ht(2);
  ht.add("a", 1);
  ht.add("b", 2);
  ht.add("c", 3);
  ht.add("d", 4);

  ht.rehash(10);
  BOOST_CHECK(ht.has("a"));
  BOOST_CHECK(ht.has("d"));
}

BOOST_AUTO_TEST_CASE(testExceptionSafetyCopyAndSwap)
{
  kuchukbaeva::HashTable< std::string, int > ht1(4);
  ht1.add("A", 10);
  ht1.add("B", 20);

  kuchukbaeva::HashTable< std::string, int > ht2 = ht1;
  BOOST_CHECK(ht2.has("A"));
  ht2.drop("B");
  BOOST_CHECK(!ht2.has("B"));
  BOOST_CHECK(ht1.has("B"));
}
