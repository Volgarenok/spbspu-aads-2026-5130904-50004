#define BOOST_TEST_MODULE BiListTests
#include <boost/test/included/unit_test.hpp>
#include "BiList.hpp"

using namespace chadin;

BOOST_AUTO_TEST_CASE(test_basic_ops)
{
  BiList< int > l;
  BOOST_CHECK(l.isEmpty());

  l.pushBack(10);
  l.pushBack(20);
  l.pushFront(5);

  BOOST_CHECK_EQUAL(l.getSize(), 3);
  BOOST_CHECK_EQUAL(l.front(), 5);
  BOOST_CHECK_EQUAL(l.back(), 20);

  l.popFront();
  BOOST_CHECK_EQUAL(l.front(), 10);
}

BOOST_AUTO_TEST_CASE(test_iteration)
{
  BiList< int > l;
  l.pushBack(1);
  l.pushBack(2);
  l.pushBack(3);

  int sum = 0;
  for (auto it = l.begin(); it != l.end(); ++it)
  {
    sum += *it;
  }
  BOOST_CHECK_EQUAL(sum, 6);

  auto it = l.end();
  --it;
  BOOST_CHECK_EQUAL(*it, 3);
}

BOOST_AUTO_TEST_CASE(test_copying)
{
  BiList< int > l1;
  l1.pushBack(100);

  BiList< int > l2 = l1;
  BOOST_CHECK_EQUAL(l2.front(), 100);

  l2.pushBack(200);
  BOOST_CHECK_EQUAL(l1.getSize(), 1);
  BOOST_CHECK_EQUAL(l2.getSize(), 2);
}
