#define BOOST_TEST_MODULE ListTests
#include <boost/test/included/unit_test.hpp>
#include "List.hpp"

using namespace em;

BOOST_AUTO_TEST_CASE(push) {
  List<int> list;
  BOOST_CHECK(list.empty());
  list.push_back(10);
  list.push_front(5);
  BOOST_CHECK_EQUAL(list.front(), 5);
  BOOST_CHECK_EQUAL(list.back(), 10);
}

BOOST_AUTO_TEST_CASE(pop) {
  List<int> list;
  list.push_back(10);
  list.push_front(5);
  list.pop_front();
  BOOST_CHECK_EQUAL(list.front(), 10);
  list.pop_back();
  BOOST_CHECK(list.empty());
}

BOOST_AUTO_TEST_CASE(iterators) {
  List<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  int expected = 1;
  for (auto it = list.begin(); it != list.end(); ++it) {
    BOOST_CHECK_EQUAL(*it, expected);
    expected++;
  }
}

BOOST_AUTO_TEST_CASE(copy_construct) {
  List<int> list1;
  list1.push_back(10);
  list1.push_back(20);

  List<int> list2(list1);
  BOOST_CHECK_EQUAL(list2.front(), 10);
  BOOST_CHECK_EQUAL(list2.back(), 20);
  BOOST_CHECK_EQUAL(list2.size(), 2);
}

BOOST_AUTO_TEST_CASE(move_construct) {
  List<int> list1;
  list1.push_back(10);
  list1.push_back(20);

  List<int> list2(std::move(list1));
  BOOST_CHECK_EQUAL(list2.front(), 10);
  BOOST_CHECK_EQUAL(list2.back(), 20);
  BOOST_CHECK(list1.empty());
}
