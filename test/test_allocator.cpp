#define BOOST_TEST_MODULE test_allocator

#define UNUSED(X) (void)(X)

#include <boost/test/unit_test.hpp>

#include <map>
#include <list>
#include <vector>

#include "../lib/allocator.h"

BOOST_AUTO_TEST_SUITE(not_extendable_allocator)

  constexpr auto extendable = false;

  BOOST_AUTO_TEST_CASE(construct) {
    BOOST_REQUIRE_NO_THROW((z80::allocator<long, 1, extendable>()));
    BOOST_REQUIRE_NO_THROW((z80::allocator<long, 10, extendable>()));
    BOOST_REQUIRE_NO_THROW((z80::allocator<long, 100, extendable>()));

    BOOST_REQUIRE_NO_THROW((z80::allocator<double, 1, extendable>()));
    BOOST_REQUIRE_NO_THROW((z80::allocator<double, 10, extendable>()));
    BOOST_REQUIRE_NO_THROW((z80::allocator<double, 100, extendable>()));

    BOOST_REQUIRE_NO_THROW((z80::allocator<std::string, 1, extendable>()));
    BOOST_REQUIRE_NO_THROW((z80::allocator<std::string, 10, extendable>()));
    BOOST_REQUIRE_NO_THROW((z80::allocator<std::string, 100, extendable>()));
  }

  BOOST_AUTO_TEST_CASE(allocate_1) {
    auto iAllocator = z80::allocator<long, 1, extendable>();
    decltype(iAllocator.allocate(1)) i = nullptr;

    BOOST_REQUIRE_NO_THROW(i = iAllocator.allocate(1));
    BOOST_CHECK(i != nullptr);
    BOOST_REQUIRE_THROW(iAllocator.allocate(1), std::bad_alloc);
    BOOST_REQUIRE_NO_THROW(iAllocator.deallocate(i, 1));
    BOOST_REQUIRE_NO_THROW(i = iAllocator.allocate(1));
    BOOST_CHECK(i != nullptr);
    BOOST_REQUIRE_THROW(iAllocator.allocate(1), std::bad_alloc);
    BOOST_REQUIRE_NO_THROW(iAllocator.deallocate(i, 1));
  }

  BOOST_AUTO_TEST_CASE(allocate_N) {
    constexpr size_t N = 42;
    auto iAllocator = z80::allocator<long, N, extendable>();
    decltype(iAllocator.allocate(N)) i = nullptr;

    BOOST_REQUIRE_NO_THROW(i = iAllocator.allocate(N));
    BOOST_CHECK(i != nullptr);
    BOOST_REQUIRE_THROW(iAllocator.allocate(1), std::bad_alloc);
    BOOST_REQUIRE_NO_THROW(iAllocator.deallocate(i, N));
    BOOST_REQUIRE_NO_THROW(i = iAllocator.allocate(N));
    BOOST_CHECK(i != nullptr);
    BOOST_REQUIRE_THROW(iAllocator.allocate(N), std::bad_alloc);
    BOOST_REQUIRE_NO_THROW(iAllocator.deallocate(i, N));
  }

  BOOST_AUTO_TEST_CASE(allocate_couple) {
    auto iAllocator = z80::allocator<long, 2, extendable>();
    decltype (iAllocator.allocate(1)) i1, i2;
    BOOST_REQUIRE_NO_THROW(i1 = iAllocator.allocate(1));
    BOOST_REQUIRE_NO_THROW(i2 = iAllocator.allocate(1));

    BOOST_CHECK(i1 != nullptr);
    BOOST_CHECK(i2 != nullptr);
    BOOST_CHECK(i1 != i2);

    BOOST_REQUIRE_THROW({ auto i3 = iAllocator.allocate(1); UNUSED(i3); }, std::bad_alloc);
  }

  BOOST_AUTO_TEST_CASE(list) {
    constexpr size_t N = 5;
    std::list<size_t, z80::allocator<size_t, N, extendable>> lst;
    for (size_t i = 0; i < N; ++i)
      BOOST_REQUIRE_NO_THROW(lst.push_back(i));

    BOOST_REQUIRE_THROW(lst.push_back(42), std::bad_alloc);

    auto iter = std::cbegin(lst);
    for (size_t i = 0; i < N; ++i, ++iter)
      BOOST_CHECK(*iter == i);

    auto anotherLst = lst;
    iter = std::cbegin(anotherLst);
    for (size_t i = 0; i < N; ++i, ++iter)
      BOOST_CHECK(*iter == i);

    for (auto iter1 = std::cbegin(lst), iter2 = std::cbegin(anotherLst);
          iter1 != std::cend(lst) && iter2 != std::cend(anotherLst);
          ++iter1, ++iter2)
      BOOST_CHECK(&(*iter1) != &(*iter2));
  }

  BOOST_AUTO_TEST_CASE(map) {
    constexpr size_t N = 5;
    std::map<size_t, size_t, std::less<>, z80::allocator<size_t, N, extendable>> mapa;
    for (size_t i = 0; i < N; ++i)
      BOOST_REQUIRE_NO_THROW(mapa[i] = i);

    BOOST_REQUIRE_THROW(mapa[42] = 42, std::bad_alloc);

    for (size_t i = 0; i < N; ++i)
      BOOST_CHECK(mapa[i] == i);

    auto anotherMap = mapa;
    for (size_t i = 0; i < N; ++i)
      BOOST_CHECK(anotherMap[i] == i);

    for (auto iter1 = std::cbegin(mapa), iter2 = std::cbegin(anotherMap);
          iter1 != std::cend(mapa) && iter2 != std::cend(anotherMap);
          ++iter1, ++iter2)
      BOOST_CHECK(&(*iter1) != &(*iter2));
  }

  BOOST_AUTO_TEST_CASE(vector) {
    constexpr size_t N = 5;
    std::vector<size_t, z80::allocator<size_t, N, extendable>> vec;
    vec.reserve(N);

    for (size_t i = 0; i < N; ++i)
      BOOST_REQUIRE_NO_THROW(vec.push_back(i));

    BOOST_REQUIRE_THROW(vec.push_back(42), std::bad_alloc);

    for (size_t i = 0; i < N; ++i)
      BOOST_CHECK(vec[i] == i);

    auto anotherVec = vec;
    for (size_t i = 0; i < N; ++i)
      BOOST_CHECK(anotherVec[i] == i);

    for (auto iter1 = std::cbegin(vec), iter2 = std::cbegin(anotherVec);
         iter1 != std::cend(vec) && iter2 != std::cend(anotherVec);
         ++iter1, ++iter2)
      BOOST_CHECK(&(*iter1) != &(*iter2));
  }

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(extendable_allocator)

  constexpr auto extendable = true;

  BOOST_AUTO_TEST_CASE(construct) {
    BOOST_REQUIRE_NO_THROW((z80::allocator<long, 1, extendable>()));
    BOOST_REQUIRE_NO_THROW((z80::allocator<long, 10, extendable>()));
    BOOST_REQUIRE_NO_THROW((z80::allocator<long, 100, extendable>()));

    BOOST_REQUIRE_NO_THROW((z80::allocator<double, 1, extendable>()));
    BOOST_REQUIRE_NO_THROW((z80::allocator<double, 10, extendable>()));
    BOOST_REQUIRE_NO_THROW((z80::allocator<double, 100, extendable>()));

    BOOST_REQUIRE_NO_THROW((z80::allocator<std::string, 1, extendable>()));
    BOOST_REQUIRE_NO_THROW((z80::allocator<std::string, 10, extendable>()));
    BOOST_REQUIRE_NO_THROW((z80::allocator<std::string, 100, extendable>()));
  }

  BOOST_AUTO_TEST_CASE(allocate_1) {
    auto iAllocator = z80::allocator<long, 1, extendable>();
    decltype(iAllocator.allocate(1)) i1 = nullptr;
    auto i2 = i1;

    BOOST_REQUIRE_NO_THROW(i1 = iAllocator.allocate(1));
    BOOST_CHECK(i1 != nullptr);
    BOOST_REQUIRE_NO_THROW(i2 = iAllocator.allocate(1));
    BOOST_CHECK(i2 != nullptr);
    BOOST_CHECK(i1 != i2);
    BOOST_REQUIRE_NO_THROW(iAllocator.deallocate(i1, 1));
    BOOST_REQUIRE_NO_THROW(iAllocator.deallocate(i2, 1));
  }

  BOOST_AUTO_TEST_CASE(allocate_N) {
    constexpr size_t N = 42;
    auto iAllocator = z80::allocator<long, N, extendable>();
    decltype(iAllocator.allocate(N)) i = nullptr;

    BOOST_REQUIRE_NO_THROW(i = iAllocator.allocate(N));
    BOOST_CHECK(i != nullptr);
    BOOST_REQUIRE_NO_THROW(iAllocator.allocate(2 * N));
  }

  BOOST_AUTO_TEST_CASE(allocate_couple) {
    auto iAllocator = z80::allocator<long, 2, extendable>();
    decltype (iAllocator.allocate(1)) i1, i2;
    BOOST_REQUIRE_NO_THROW(i1 = iAllocator.allocate(1));
    BOOST_REQUIRE_NO_THROW(i2 = iAllocator.allocate(1));

    BOOST_CHECK(i1 != nullptr);
    BOOST_CHECK(i2 != nullptr);
    BOOST_CHECK(i1 != i2);

    BOOST_REQUIRE_NO_THROW({ auto i3 = iAllocator.allocate(1); UNUSED(i3); });
  }

  BOOST_AUTO_TEST_CASE(list) {
    constexpr size_t N = 5;
    std::list<size_t, z80::allocator<size_t, N, extendable>> lst;
    for (size_t i = 0; i < N; ++i)
      BOOST_REQUIRE_NO_THROW(lst.push_back(i));

    BOOST_REQUIRE_NO_THROW(lst.push_back(42));
    BOOST_CHECK(lst.back() == 42);

    auto iter = std::cbegin(lst);
    for (size_t i = 0; i < N; ++i, ++iter)
      BOOST_CHECK(*iter == i);

    auto anotherLst = lst;
    iter = std::cbegin(anotherLst);
    for (size_t i = 0; i < N; ++i, ++iter)
      BOOST_CHECK(*iter == i);

    for (auto iter1 = std::cbegin(lst), iter2 = std::cbegin(anotherLst);
         iter1 != std::cend(lst) && iter2 != std::cend(anotherLst);
         ++iter1, ++iter2)
      BOOST_CHECK(&(*iter1) != &(*iter2));
  }

  BOOST_AUTO_TEST_CASE(map) {
    constexpr size_t N = 5;
    std::map<size_t, size_t, std::less<>, z80::allocator<size_t, N, extendable>> mapa;
    for (size_t i = 0; i < N; ++i)
      BOOST_REQUIRE_NO_THROW(mapa[i] = i);

    BOOST_REQUIRE_NO_THROW(mapa[42] = 42);
    BOOST_CHECK(mapa[42] == 42);

    for (size_t i = 0; i < N; ++i)
      BOOST_CHECK(mapa[i] == i);

    auto anotherMap = mapa;
    for (size_t i = 0; i < N; ++i)
      BOOST_CHECK(anotherMap[i] == i);

    for (auto iter1 = std::cbegin(mapa), iter2 = std::cbegin(anotherMap);
         iter1 != std::cend(mapa) && iter2 != std::cend(anotherMap);
         ++iter1, ++iter2)
      BOOST_CHECK(&(*iter1) != &(*iter2));
  }

  BOOST_AUTO_TEST_CASE(vector) {
    constexpr size_t N = 5;
    std::vector<size_t, z80::allocator<size_t, N, extendable>> vec;
    vec.reserve(N);

    for (size_t i = 0; i < N; ++i)
      BOOST_REQUIRE_NO_THROW(vec.push_back(i));

    BOOST_REQUIRE_NO_THROW(vec.push_back(42));
    BOOST_CHECK(vec.back() == 42);

    for (size_t i = 0; i < N; ++i)
      BOOST_CHECK(vec[i] == i);

    auto anotherVec = vec;
    for (size_t i = 0; i < N; ++i)
      BOOST_CHECK(anotherVec[i] == i);

    for (auto iter1 = std::cbegin(vec), iter2 = std::cbegin(anotherVec);
         iter1 != std::cend(vec) && iter2 != std::cend(anotherVec);
         ++iter1, ++iter2)
      BOOST_CHECK(&(*iter1) != &(*iter2));
  }

BOOST_AUTO_TEST_SUITE_END()
