#define BOOST_TEST_MODULE AppLogicTests
#include <boost/test/included/unit_test.hpp>
#include <sstream>
#include <string>
#include "code.h"

BOOST_AUTO_TEST_CASE(test_given_example) {
  std::stringstream in("first 1 1 1\nsecond 2 2 2 2\nthird\nfourth 4 4\n");
  std::stringstream out;
  std::stringstream err;

  int result = run(in, out, err);

  BOOST_CHECK_EQUAL(result, 0);
  
  std::string expected_out = 
    "first second third fourth\n"
    "1 2 4\n"
    "1 2 4\n"
    "1 2\n"
    "2\n"
    "7 7 3 2\n";
    
  BOOST_CHECK_EQUAL(out.str(), expected_out);
  BOOST_CHECK_EQUAL(err.str(), "");
}

BOOST_AUTO_TEST_CASE(test_empty_input) {
  std::stringstream in("");
  std::stringstream out;
  std::stringstream err;

  int result = run(in, out, err);

  BOOST_CHECK_EQUAL(result, 0);
  BOOST_CHECK_EQUAL(out.str(), "");
}

BOOST_AUTO_TEST_CASE(test_numeric_limit_overflow) {
  std::stringstream in("a 2147483647\nb 1\n");
  std::stringstream out;
  std::stringstream err;

  int result = run(in, out, err);

  BOOST_CHECK_EQUAL(result, 1);
  BOOST_CHECK_EQUAL(err.str(), "Error during sum processing\n");
}
