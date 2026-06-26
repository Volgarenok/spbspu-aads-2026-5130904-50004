#define BOOST_TEST_MODULE S2
#include <boost/test/included/unit_test.hpp>

#include "stack.hpp"
#include "queue.hpp"

BOOST_AUTO_TEST_CASE(stack_test)
{
  ali::Stack< int > stack;

  stack.push(1);
  stack.push(2);

  BOOST_TEST(stack.top() == 2);

  stack.drop();

  BOOST_TEST(stack.top() == 1);
}

BOOST_AUTO_TEST_CASE(queue_test)
{
  ali::Queue< int > queue;

  queue.push(1);
  queue.push(2);

  BOOST_TEST(queue.front() == 1);

  queue.drop();

  BOOST_TEST(queue.front() == 2);
}
