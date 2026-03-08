#if defined(__GNUC__) || defined(__clang__)
    __attribute__((weak)) int main(int argc, char* argv[]) {
        return 0;
    }
#endif

#define BOOST_TEST_MODULE ListTests
#include <boost/test/unit_test.hpp>
#include "list.hpp"

using namespace ivantsova;

BOOST_AUTO_TEST_CASE(push_pop)
{
  List<int> list;
  BOOST_CHECK(list.empty());

  list.push_back(42);
  list.push_front(13);

  BOOST_CHECK_EQUAL(list.front(), 13);
  BOOST_CHECK_EQUAL(list.back(), 42);
  BOOST_CHECK_EQUAL(list.size(), 2);

  list.pop_front();
  BOOST_CHECK_EQUAL(list.front(), 42);
  list.pop_back();
  BOOST_CHECK(list.empty());
}

BOOST_AUTO_TEST_CASE(copy_move)
{
  List<int> list1;
  list1.push_back(7);
  list1.push_back(8);

  List<int> list2(list1);
  BOOST_CHECK_EQUAL(list2.front(), 7);
  BOOST_CHECK_EQUAL(list2.back(), 8);

  List<int> list3(std::move(list1));
  BOOST_CHECK(list1.empty());
  BOOST_CHECK_EQUAL(list3.front(), 7);
}

BOOST_AUTO_TEST_CASE(sum_overflow)
{
  unsigned long long total = 18000000000000000000ull;
  BOOST_CHECK_THROW(sum(total, 5000000000000000000ull), std::overflow_error);
}
