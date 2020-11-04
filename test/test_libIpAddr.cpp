#define BOOST_TEST_MODULE test_libIpAddr

#include "../lib/libIpAddr.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_libIpAddr)

BOOST_AUTO_TEST_CASE(test_greater_operator)
{
    ipAddr left, right;
    left.addr = 0; right.addr = 0;
    BOOST_CHECK((left > right) == false);
}

}

