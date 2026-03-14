#define BOOST_TEST_MODULE BiListTests
#include <boost/test/included/unit_test.hpp>
#include "biList.hpp"

using namespace pozdeev;

BOOST_AUTO_TEST_CASE(isEmptyCheck)
{
  BiList<int> lst;
  BOOST_CHECK(lst.isEmpty());
  lst.pushBack(1);
  BOOST_CHECK(!lst.isEmpty());
}

BOOST_AUTO_TEST_CASE(getSizeCheck)
{
  BiList<int> lst;
  BOOST_CHECK_EQUAL(lst.getSize(), 0);
  lst.pushBack(1);
  lst.pushBack(2);
  BOOST_CHECK_EQUAL(lst.getSize(), 2);
}
