cmake_minimum_required(VERSION 3.2)

# project properties
project(sfinae VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

# config с++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)

configure_file(lib/version.h.in version.h)

# library
add_library(libversion lib/libversion.cpp)
target_include_directories(libversion PRIVATE "${CMAKE_BINARY_DIR}")


# executable destination
add_executable(print_ip main.cpp)
target_include_directories(print_ip PRIVATE "${CMAKE_BINARY_DIR}")
target_link_libraries(print_ip PRIVATE libversion)


# tests
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(test_libversion test/test_libversion.cpp)
target_link_libraries(test_libversion ${Boost_LIBRARIES} libversion)
set_target_properties(test_libversion PROPERTIES COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR})

add_executable(test_ip2string test/test_ip2string.cpp)
target_link_libraries(test_ip2string ${Boost_LIBRARIES})
set_target_properties(test_ip2string PROPERTIES COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR})

enable_testing()
add_test(test_version test_libversion)
add_test(test_ip2string test_ip2string)


# doxygen
find_package(Doxygen REQUIRED dot)
set(DOXYGEN_PROJECT_BRIEF print_ip)
set(DOXYGEN_HAVE_DOT YES)
set(DOXYGEN_EXTRACT_ALL YES)
set(DOXYGEN_OUTPUT_DIRECTORY docs)
doxygen_add_docs(doxygen lib ALL)


# compiler specific options
if (MSVC)
    target_compile_options(print_ip PRIVATE /W4)
    target_compile_options(libversion PRIVATE /W4)
    target_compile_options(test_libversion PRIVATE /W4)
    target_compile_options(test_ip2string PRIVATE /W4)
else ()
    target_compile_options(print_ip PRIVATE -Wall -Wextra -pedantic -Werror)
    target_compile_options(libversion PRIVATE -Wall -Wextra -pedantic -Werror)
    target_compile_options(test_libversion PRIVATE -Wall -Wextra -pedantic -Werror)
    target_compile_options(test_ip2string PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

# which are to install
install(TARGETS print_ip RUNTIME DESTINATION bin)

# package config
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT solock@mail.ru)
include(CPack)
