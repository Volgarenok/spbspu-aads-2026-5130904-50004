#define BOOST_TEST_MODULE ListTests
#include <boost/test/included/unit_test.hpp>
#include "list.h"

using namespace aushev;

BOOST_AUTO_TEST_CASE(push_front_basic)
{
  List<int> lst;
  lst.push_front(5);
  BOOST_CHECK_EQUAL(lst.size(), 1);
  lst.push_front(15);
  BOOST_CHECK_EQUAL(lst.size(), 2);
  auto it = lst.begin();
  BOOST_CHECK_EQUAL(*it, 15);
  ++it;
  BOOST_CHECK_EQUAL(*it, 5);
}

BOOST_AUTO_TEST_CASE(push_back_basic)
{
  List<int> lst;
  lst.push_back(100);
  BOOST_CHECK_EQUAL(lst.size(), 1);
  lst.push_back(200);
  BOOST_CHECK_EQUAL(lst.size(), 2);
  auto it = lst.begin();
  BOOST_CHECK_EQUAL(*it, 100);
  ++it;
  BOOST_CHECK_EQUAL(*it, 200);
}

BOOST_AUTO_TEST_CASE(pop_front_test)
{
  List<int> lst;
  lst.push_back(7);
  lst.push_back(14);
  lst.push_back(21);
  lst.pop_front();
  BOOST_CHECK_EQUAL(lst.size(), 2);
  auto it = lst.begin();
  BOOST_CHECK_EQUAL(*it, 14);
  ++it;
  BOOST_CHECK_EQUAL(*it, 21);
  lst.pop_front();
  BOOST_CHECK_EQUAL(lst.size(), 1);
  BOOST_CHECK_EQUAL(*lst.begin(), 21);
  lst.pop_front();
  BOOST_CHECK(lst.size() == 0);
}

BOOST_AUTO_TEST_CASE(pop_back_test)
{
  List<int> lst;
  lst.push_back(5);
  lst.push_back(10);
  lst.push_back(15);
  lst.pop_back();
  BOOST_CHECK_EQUAL(lst.size(), 2);
  auto it = lst.begin();
  BOOST_CHECK_EQUAL(*it, 5);
  ++it;
  BOOST_CHECK_EQUAL(*it, 10);
  lst.pop_back();
  BOOST_CHECK_EQUAL(lst.size(), 1);
  BOOST_CHECK_EQUAL(*lst.begin(), 5);
  lst.pop_back();
  BOOST_CHECK(lst.size() == 0);
}

BOOST_AUTO_TEST_CASE(clear_operation)
{
  List<int> lst;
  lst.push_back(3);
  lst.push_back(6);
  lst.push_back(9);
  lst.clear();
  BOOST_CHECK(lst.size() == 0);
  BOOST_CHECK(lst.begin() == lst.end());
}

BOOST_AUTO_TEST_CASE(empty_check)
{
  List<int> lst;
  BOOST_CHECK(lst.empty());
  BOOST_CHECK_EQUAL(lst.size(), 0);
  lst.push_back(42);
  BOOST_CHECK(!lst.empty());
}

BOOST_AUTO_TEST_CASE(front_back_values)
{
  List<int> lst;
  lst.push_back(11);
  lst.push_back(22);
  lst.push_back(33);
  BOOST_CHECK_EQUAL(lst.front(), 11);
  BOOST_CHECK_EQUAL(lst.back(), 33);
}

BOOST_AUTO_TEST_CASE(copy_construction)
{
  List<int> lst1;
  lst1.push_back(8);
  lst1.push_back(16);
  List<int> lst2(lst1);
  BOOST_CHECK_EQUAL(lst2.front(), 8);
  BOOST_CHECK_EQUAL(lst2.back(), 16);
}

BOOST_AUTO_TEST_CASE(move_construction)
{
  List<int> lst1;
  lst1.push_back(8);
  lst1.push_back(16);
  List<int> lst2(std::move(lst1));
  BOOST_CHECK(lst1.empty());
  BOOST_CHECK_EQUAL(lst2.front(), 8);
}

BOOST_AUTO_TEST_CASE(iterator_traversal)
{
  List<int> lst;
  lst.push_back(2);
  lst.push_back(4);
  lst.push_back(6);
  auto it = lst.begin();
  BOOST_CHECK_EQUAL(*it, 2);
  ++it;
  BOOST_CHECK_EQUAL(*it, 4);
  ++it;
  BOOST_CHECK_EQUAL(*it, 6);
  ++it;
  BOOST_CHECK(it == lst.end());
}

BOOST_AUTO_TEST_CASE(const_iterator)
{
  List<int> lst;
  lst.push_back(100);
  lst.push_back(200);
  const List<int>& clst = lst;
  auto it = clst.cbegin();
  BOOST_CHECK_EQUAL(*it, 100);
  ++it;
  BOOST_CHECK_EQUAL(*it, 200);
  ++it;
  BOOST_CHECK(it == clst.cend());
}

BOOST_AUTO_TEST_CASE(bidirectional_iterator)
{
  List<int> lst;
  lst.push_back(10);
  lst.push_back(20);
  lst.push_back(30);
  auto it = lst.end();
  --it;
  BOOST_CHECK_EQUAL(*it, 30);
  --it;
  BOOST_CHECK_EQUAL(*it, 20);
  --it;
  BOOST_CHECK_EQUAL(*it, 10);
}

BOOST_AUTO_TEST_CASE(copy_assignment)
{
  List<int> lst1;
  lst1.push_back(1);
  lst1.push_back(2);
  List<int> lst2;
  lst2 = lst1;
  BOOST_CHECK_EQUAL(lst2.size(), 2);
  BOOST_CHECK_EQUAL(lst2.front(), 1);
}

BOOST_AUTO_TEST_CASE(move_assignment)
{
  List<int> lst1;
  lst1.push_back(1);
  lst1.push_back(2);
  List<int> lst2;
  lst2 = std::move(lst1);
  BOOST_CHECK(lst1.empty());
  BOOST_CHECK_EQUAL(lst2.size(), 2);
}

BOOST_AUTO_TEST_CASE(empty_list_operations)
{
  List<int> lst;
  BOOST_CHECK(lst.empty());
  lst.pop_front();
  BOOST_CHECK(lst.empty());
  lst.pop_back();
  BOOST_CHECK(lst.empty());
}

BOOST_AUTO_TEST_CASE(single_element_list)
{
  List<int> lst;
  lst.push_back(42);
  BOOST_CHECK_EQUAL(lst.size(), 1);
  BOOST_CHECK_EQUAL(lst.front(), 42);
  BOOST_CHECK_EQUAL(lst.back(), 42);
  lst.pop_front();
  BOOST_CHECK(lst.empty());
}

BOOST_AUTO_TEST_CASE(mixed_push_operations)
{
  List<int> lst;
  lst.push_back(1);
  lst.push_front(0);
  lst.push_back(2);
  lst.push_front(-1);
  BOOST_CHECK_EQUAL(lst.size(), 4);
  BOOST_CHECK_EQUAL(lst.front(), -1);
  BOOST_CHECK_EQUAL(lst.back(), 2);
}
