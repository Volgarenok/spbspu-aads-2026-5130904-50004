#define BOOST_TEST_MODULE BiListTests
#include <boost/test/included/unit_test.hpp>

#include <string>
#include <utility>

#include "BiList.hpp"

BOOST_AUTO_TEST_CASE(default_construct_empty)
{
  dolenko::BiList< int > list;
  BOOST_TEST(list.empty());
  BOOST_TEST(list.size() == 0u);
}

BOOST_AUTO_TEST_CASE(push_front_back_and_front_back_access)
{
  dolenko::BiList< int > list;

  list.push_back(2);
  list.push_front(1);
  list.push_back(3);

  BOOST_TEST(list.size() == 3u);
  BOOST_TEST(list.front() == 1);
  BOOST_TEST(list.back() == 3);
}

BOOST_AUTO_TEST_CASE(pop_front_back_and_clear)
{
  dolenko::BiList< int > list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  list.pop_front();
  BOOST_TEST(list.size() == 2u);
  BOOST_TEST(list.front() == 2);

  list.pop_back();
  BOOST_TEST(list.size() == 1u);
  BOOST_TEST(list.front() == 2);
  BOOST_TEST(list.back() == 2);

  list.clear();
  BOOST_TEST(list.empty());
  BOOST_TEST(list.size() == 0u);

  list.pop_front();
  list.pop_back();
  BOOST_TEST(list.empty());
}

BOOST_AUTO_TEST_CASE(iterator_traversal)
{
  dolenko::BiList< int > list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  int expected = 1;
  for (auto it = list.begin(); it != list.end(); ++it)
  {
    BOOST_TEST(*it == expected);
    ++expected;
  }
  BOOST_TEST(expected == 4);
}

BOOST_AUTO_TEST_CASE(const_iterator_traversal)
{
  dolenko::BiList< int > tmp;
  tmp.push_back(1);
  tmp.push_back(2);

  const dolenko::BiList< int > list(tmp);

  int sum = 0;
  for (auto it = list.begin(); it != list.end(); ++it)
  {
    sum += *it;
  }
  BOOST_TEST(sum == 3);
}

BOOST_AUTO_TEST_CASE(copy_constructor_independent)
{
  dolenko::BiList< int > a;
  a.push_back(1);
  a.push_back(2);

  dolenko::BiList< int > b(a);
  BOOST_TEST(b.size() == 2u);
  BOOST_TEST(b.front() == 1);
  BOOST_TEST(b.back() == 2);

  a.pop_front();
  BOOST_TEST(a.size() == 1u);
  BOOST_TEST(b.size() == 2u);
  BOOST_TEST(b.front() == 1);
}

BOOST_AUTO_TEST_CASE(copy_assignment)
{
  dolenko::BiList< int > a;
  a.push_back(1);
  a.push_back(2);

  dolenko::BiList< int > b;
  b.push_back(10);

  b = a;
  BOOST_TEST(b.size() == 2u);
  BOOST_TEST(b.front() == 1);
  BOOST_TEST(b.back() == 2);
}

BOOST_AUTO_TEST_CASE(move_constructor_steals)
{
  dolenko::BiList< int > a;
  a.push_back(1);
  a.push_back(2);

  dolenko::BiList< int > b(std::move(a));
  BOOST_TEST(b.size() == 2u);
  BOOST_TEST(b.front() == 1);
  BOOST_TEST(b.back() == 2);

  BOOST_TEST(a.size() == 0u);
  BOOST_TEST(a.empty());
}

BOOST_AUTO_TEST_CASE(move_assignment_steals)
{
  dolenko::BiList< int > a;
  a.push_back(1);

  dolenko::BiList< int > b;
  b.push_back(10);
  b.push_back(20);

  b = std::move(a);
  BOOST_TEST(b.size() == 1u);
  BOOST_TEST(b.front() == 1);
  BOOST_TEST(b.back() == 1);

  BOOST_TEST(a.empty());
}

BOOST_AUTO_TEST_CASE(rvalue_push_moves)
{
  using Pair = std::pair< std::string, int >;
  dolenko::BiList< Pair > list;

  std::string s = "abc";
  list.push_back(Pair(std::move(s), 42));

  BOOST_TEST(list.size() == 1u);
  BOOST_TEST(list.front().first == "abc");
  BOOST_TEST(list.front().second == 42);
}
