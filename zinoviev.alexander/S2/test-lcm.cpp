#define BOOST_TEST_MODULE LcmTest
#include <boost/test/included/unit_test.hpp>
#include <cstdlib>

long long gcd(long long a, long long b)
{
  while (b)
  {
    long long t = b; b = a % b; a = t;
  }
  return a;
}

long long lcm(long long a, long long b)
{
  a = std::llabs(a); b = std::llabs(b);
  long long g = gcd(a, b);

  return g ? (a / g) * b : 0;
}

BOOST_AUTO_TEST_CASE(testLcm)
{
  BOOST_CHECK_EQUAL(lcm(2, 3), 6);
  BOOST_CHECK_EQUAL(lcm(0, 5), 0);
  BOOST_CHECK_EQUAL(lcm(-4, 6), 12);
  BOOST_CHECK_EQUAL(lcm(12, 18), 36);
}
