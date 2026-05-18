#define BOOST_TEST_MODULE TestList
#include <boost/test/included/unit_test.hpp>
#include "list.hpp"

BOOST_AUTO_TEST_CASE(iterator_test)
{
  ali::List< int > list;

  list.push_front(3);
  list.push_front(2);
  list.push_front(1);

  auto it = list.begin();

  BOOST_TEST(*it == 1);

  ++it;
  BOOST_TEST(*it == 2);

  ++it;
  BOOST_TEST(*it == 3);
}
BOOST_AUTO_TEST_CASE(copy_test)
{
  ali::List< int > list;
  list.push_back(1);
  list.push_back(2);

  ali::List< int > copy(list);

  auto it = copy.begin();
  BOOST_TEST(*it == 1);
  ++it;
  BOOST_TEST(*it == 2);
}
BOOST_AUTO_TEST_CASE(size_test)
{
  ali::List< int > list;

  BOOST_TEST(list.size() == 0);

  list.push_back(10);
  list.push_back(20);

  BOOST_TEST(list.size() == 2);

  list.pop_front();

  BOOST_TEST(list.size() == 1);
}
