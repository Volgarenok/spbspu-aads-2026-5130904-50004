#define BOOST_TEST_MODULE ListTests
#include <boost/test/included/unit_test.hpp>
#include "List.h"

BOOST_AUTO_TEST_CASE (fake)
{
  alekseev::List< int > * list = alekseev::fake< int >();
  BOOST_CHECK_EQUAL(list->next, list);
  list = alekseev::insert_after(list, 10);
  BOOST_CHECK_EQUAL(list->data, 10);
  list = alekseev::insert_after(list, 20);
  BOOST_CHECK_EQUAL(list->data, 20);
  BOOST_CHECK_EQUAL(list->next->next->next, list);
  list = list->next;
  alekseev::erase_after(list);
  BOOST_CHECK_EQUAL(list->next->data, 20);
  alekseev::clear(list->next, list);
  alekseev::rmfake(list);
}
