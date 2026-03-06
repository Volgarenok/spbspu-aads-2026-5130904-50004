#define BOOST_TEST_MODULE ListTests
#include <boost/test/included/unit_test.hpp>
#include "List.h"

using namespace ivanov;

BOOST_AUTO_TEST_CASE(push)
{
  List<int> list;
  BOOST_CHECK(list.isEmpty());

  list.pushBack(10);
  list.pushFront(5);
  BOOST_CHECK_EQUAL(list.front(), 5);
  BOOST_CHECK_EQUAL(list.back(), 10);

}

BOOST_AUTO_TEST_CASE(pop)
{
  List<int> list;
  l1.pushBack(10);
  l1.pushFront(5);

  list.popFront();
  BOOST_CHECK_EQUAL(list.front(), 10);
  list.popBack();
  BOOST_CHECK(list.isEmpty());
}
