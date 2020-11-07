#define BOOST_TEST_MODULE test_libIpAddr

#include "../lib/libIpAddr.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_ipAddr)

BOOST_AUTO_TEST_CASE(test_equals_operator) {
  BOOST_CHECK((ipAddr(0,0,0,0) == ipAddr(0,0,0,0)) == true);
  BOOST_CHECK((ipAddr(1,2,3,4) == ipAddr(4,3,2,1)) == false);
}

BOOST_AUTO_TEST_CASE(test_greater_operator) {
    ipAddr left(0,0,0,0);
    ipAddr right(0,0,0,0);
    // left.addr = 0; right.addr = 0;
    BOOST_CHECK((left > right) == false);

    left.addr = 10;
    BOOST_CHECK((left > right) == true);

    right.addr = 20;
    BOOST_CHECK((left > right) == false);
}

BOOST_AUTO_TEST_CASE(test_string2ip) {
  BOOST_REQUIRE_THROW(string2ip(""), std::invalid_argument);
  BOOST_REQUIRE_THROW(string2ip("a.b.c.d"), std::invalid_argument);
  BOOST_REQUIRE_THROW(string2ip("1.2.3"), std::invalid_argument);
  BOOST_REQUIRE_THROW(string2ip("1.2.3.4.5"), std::invalid_argument);
  BOOST_REQUIRE_THROW(string2ip("1.2.3.-4"), std::invalid_argument);
  BOOST_REQUIRE_THROW(string2ip("1.2.3.256"), std::invalid_argument);
  BOOST_CHECK(string2ip("1.2.3.4") == ipAddr(1, 2, 3, 4));
}

BOOST_AUTO_TEST_CASE(test_ip2stream) {
    std::ostringstream os;
    os << ipAddr (1, 2, 3, 4);
    BOOST_CHECK(os.str() == "1.2.3.4");
  }

BOOST_AUTO_TEST_CASE(test_stream2ips) {
    std::istringstream is("");
    std::vector<ipAddr> ips;
    BOOST_REQUIRE_THROW(operator>>(is,ips), std::invalid_argument);

    is.str("1.2.3.4\tbla-bla-bla\b5.6.7.8\tтырыпыры");
    BOOST_REQUIRE_NO_THROW(operator>>(is,ips));
    BOOST_CHECK(ips[0] == ipAddr(1,2,3,4));
    BOOST_CHECK(ips[1] == ipAddr(5,6,7,8));
  }

BOOST_AUTO_TEST_CASE(test_ips2stream) {
  std::vector<ipAddr> ips { ipAddr(1,2,3,4), ipAddr(5,6,7,8) };
  std::ostringstream os;
  BOOST_REQUIRE_NO_THROW(operator<<(os, ips));
  BOOST_CHECK(os.str() == "1.2.3.4\n5.6.7.8\n");
}
}
