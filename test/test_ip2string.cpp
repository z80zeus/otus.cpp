#define BOOST_TEST_MODULE test_ip2string

#define UNUSED(X) (void)(X)

#include <boost/test/unit_test.hpp>

#include <list>
#include <vector>

#include "../lib/ip2string.h"

using z80::ip2string;
using std::string;
using std::vector;
using std::list;

/**
 * @brief Пребразовать строку в "IP-адрес" повторами через точку.
 * @param str Строка, из которой будет состоять IP-адрес.
 * @param num Количество повторов
 * @return Строка вида str.str.str... в которой значение параметра str будет повторено num раз через точку.
 */
auto str2ip(const string &str, size_t num) {
  string rtn;
  for (decltype(num) i = 0; i < num; ++i) rtn += str + ".";
  rtn.resize(rtn.size() - 1);
  return rtn;
}

BOOST_AUTO_TEST_SUITE(_)

  BOOST_AUTO_TEST_CASE(Integral) {
    string res, expect;

    expect = str2ip("255", sizeof(char));
    BOOST_REQUIRE_NO_THROW(res = ip2string(static_cast<char>(-1)));
    BOOST_REQUIRE_EQUAL(res, expect);

    expect = str2ip("0", sizeof(char));
    BOOST_REQUIRE_NO_THROW(res = ip2string(static_cast<char>(0)));
    BOOST_REQUIRE_EQUAL(res, expect);

    expect = str2ip("255", sizeof(int));
    BOOST_REQUIRE_NO_THROW(res = ip2string(static_cast<int>(-1)));
    BOOST_REQUIRE_EQUAL(res, expect);

    expect = str2ip("0", sizeof(int));
    BOOST_REQUIRE_NO_THROW(res = ip2string(static_cast<int>(0)));
    BOOST_REQUIRE_EQUAL(res, expect);

    expect = str2ip("255", sizeof(long));
    BOOST_REQUIRE_NO_THROW(res = ip2string(static_cast<long>(-1)));
    BOOST_REQUIRE_EQUAL(res, expect);

    expect = str2ip("0", sizeof(long));
    BOOST_REQUIRE_NO_THROW(res = ip2string(static_cast<long>(0)));
    BOOST_REQUIRE_EQUAL(res, expect);

    expect = str2ip("255", sizeof(long long));
    BOOST_REQUIRE_NO_THROW(res = ip2string(static_cast<long long>(-1)));
    BOOST_REQUIRE_EQUAL(res, expect);

    expect = str2ip("0", sizeof(long long));
    BOOST_REQUIRE_NO_THROW(res = ip2string(static_cast<long long>(0)));
    BOOST_REQUIRE_EQUAL(res, expect);
  }

  BOOST_AUTO_TEST_CASE(String) {
    string res;
    BOOST_REQUIRE_NO_THROW(res = ip2string(string("")));
    BOOST_REQUIRE_EQUAL(res, "");

    BOOST_REQUIRE_NO_THROW(res = ip2string(string("1.2.3.4")));
    BOOST_REQUIRE_EQUAL(res, "1.2.3.4");
  }

  BOOST_AUTO_TEST_CASE(Vector) {
    string res;
    BOOST_REQUIRE_NO_THROW(res = ip2string(vector<char>()));
    BOOST_REQUIRE_EQUAL(res, "");

    BOOST_REQUIRE_NO_THROW(res = ip2string(vector {1, 2, 3, 4}));
    BOOST_REQUIRE_EQUAL(res, "1.2.3.4");

    BOOST_REQUIRE_NO_THROW(res = ip2string(vector {-1, -2, -3, -4}));
    BOOST_REQUIRE_EQUAL(res, "-1.-2.-3.-4");
  }

  BOOST_AUTO_TEST_CASE(List) {
    string res;
    BOOST_REQUIRE_NO_THROW(res = ip2string(list<char>()));
    BOOST_REQUIRE_EQUAL(res, "");

    BOOST_REQUIRE_NO_THROW(res = ip2string(list {1, 2, 3, 4}));
    BOOST_REQUIRE_EQUAL(res, "1.2.3.4");

    BOOST_REQUIRE_NO_THROW(res = ip2string(list {-1, -2, -3, -4}));
    BOOST_REQUIRE_EQUAL(res, "-1.-2.-3.-4");
  }

BOOST_AUTO_TEST_SUITE_END()
