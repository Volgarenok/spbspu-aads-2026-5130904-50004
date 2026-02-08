#include <boost/test/unit_test.hpp>
#include <sstream>
#include "credentials.hpp"
BOOST_AUTO_TEST_CASE(test_test){
  std::ostringstream out;
  dobsov::out_credentials(out);
  BOOST_TEST(out.str()=="dobsov.sergey");
}
