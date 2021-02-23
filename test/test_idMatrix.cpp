#define BOOST_TEST_MODULE idMatrix

#include "../src/commandPublisher.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_idMatrix)
  BOOST_AUTO_TEST_CASE(test_create_matrix) {
    BOOST_CHECK_NO_THROW((z80::idMatrix<int,42>()));
  }

  BOOST_AUTO_TEST_CASE(test_default_value) {
    auto idMatrix = z80::idMatrix<int,42>();
    idMatrix[100][100];
    BOOST_CHECK_EQUAL(idMatrix[100][100], 42);
    BOOST_CHECK_EQUAL(idMatrix.size(), 0);
  }

  BOOST_AUTO_TEST_CASE(test_write_value) {
    auto idMatrix = z80::idMatrix<int,42>();
    BOOST_CHECK_EQUAL(idMatrix[100][100], 42);
    idMatrix[100][100] = 24;
    BOOST_CHECK_EQUAL(idMatrix[100][100], 24);
    BOOST_CHECK_EQUAL(idMatrix.size(), 1);
  }

}
