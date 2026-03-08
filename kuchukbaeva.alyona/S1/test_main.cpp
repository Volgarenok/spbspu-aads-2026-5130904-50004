#include <boost/test/unit_test.hpp>
#include "list.hpp"

BOOST_AUTO_TEST_SUITE(ListTests)

BOOST_AUTO_TEST_CASE(testInsertAndIterate)
{
  kuchukbaeva::List< int > list;
  BOOST_CHECK(list.isEmpty());

  kuchukbaeva::LIter< int > it = list.beforeBegin();
  it = list.insertAfter(it, 10);
  it = list.insertAfter(it, 20);
  list.insertAfter(it, 30);

  BOOST_CHECK(!list.isEmpty());

  kuchukbaeva::LIter< int > iter = list.begin();
  BOOST_CHECK_EQUAL(*iter, 10);
  ++iter;
  BOOST_CHECK_EQUAL(*iter, 20);
  ++iter;
  BOOST_CHECK_EQUAL(*iter, 30);
  ++iter;
  BOOST_CHECK(iter == list.end());
}
