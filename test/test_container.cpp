#define BOOST_TEST_MODULE test_container

#define UNUSED(X) (void)(X)

#include <boost/test/unit_test.hpp>

#include "../lib/allocator.h"
#include "../lib/container.h"

BOOST_AUTO_TEST_SUITE(std_allocator)
  BOOST_AUTO_TEST_CASE(construct) {
    BOOST_REQUIRE_NO_THROW((z80::container<long>()));
    BOOST_REQUIRE_NO_THROW((z80::container<double>()));
    BOOST_REQUIRE_NO_THROW((z80::container<std::string>()));
  }

  BOOST_AUTO_TEST_CASE(push) {
    auto container = z80::container<long>();
    BOOST_REQUIRE_NO_THROW(container.push_back(42));
    BOOST_CHECK(container[0] == 42);
    BOOST_REQUIRE_NO_THROW(container.push_back(24));
    BOOST_CHECK(container[0] == 42);
    BOOST_CHECK(container[1] == 24);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(z80_allocator)
  BOOST_AUTO_TEST_CASE(construct) {
    BOOST_REQUIRE_NO_THROW((z80::container<long, z80::allocator<long>>()));
    BOOST_REQUIRE_NO_THROW((z80::container<double, z80::allocator<double>>()));
    BOOST_REQUIRE_NO_THROW((z80::container<std::string, z80::allocator<std::string>>()));
  }

  BOOST_AUTO_TEST_CASE(push) {
    auto container = z80::container<long, z80::allocator<long>>();
    BOOST_REQUIRE_NO_THROW(container.push_back(42));
    BOOST_CHECK(container[0] == 42);
    BOOST_REQUIRE_NO_THROW(container.push_back(24));
    BOOST_CHECK(container[0] == 42);
    BOOST_CHECK(container[1] == 24);
  }

BOOST_AUTO_TEST_SUITE_END()
