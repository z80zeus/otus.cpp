cmake_minimum_required(VERSION 3.2)

# project properties
project(matrix VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

# config с++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)

configure_file(src/version.h.in version.h)

add_library(libversion STATIC src/version.cpp)

target_include_directories(libversion PRIVATE "${PROJECT_BINARY_DIR}")

add_executable(matrix main.cpp)

# Boost test
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

# Test libversion
add_executable(test_libversion test/test_libversion.cpp)
target_link_libraries(test_libversion ${Boost_LIBRARIES} libversion)
set_target_properties(test_libversion PROPERTIES COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR})

add_executable(test_idMatrix test/test_idMatrix.cpp)
target_link_libraries(test_idMatrix ${Boost_LIBRARIES})
set_target_properties(test_idMatrix PROPERTIES COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR})

enable_testing()
add_test(test_version test_libversion)
add_test(test_idMatrix test_idMatrix)

# doxygen
find_package(Doxygen REQUIRED dot)
set(DOXYGEN_PROJECT_BRIEF ${PROJECT_NAME})
set(DOXYGEN_HAVE_DOT YES)
set(DOXYGEN_EXTRACT_ALL YES)
set(DOXYGEN_OUTPUT_DIRECTORY docs)
doxygen_add_docs(doxygen src ALL)

## compiler specific options
if (MSVC)
    target_compile_options(matrix PRIVATE /W4)
    target_compile_options(libversion PRIVATE /W4)
    target_compile_options(test_libversion PRIVATE /W4)
    target_compile_options(test_idMatrix PRIVATE /W4)
else ()
    target_compile_options(matrix PRIVATE -Wall -Wextra -pedantic -Werror)
    target_compile_options(libversion PRIVATE -Wall -Wextra -pedantic -Werror)
    target_compile_options(test_libversion PRIVATE -Wall -Wextra -pedantic -Werror)
    target_compile_options(test_idMatrix PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

# which are to install
install(TARGETS matrix RUNTIME DESTINATION bin)

# package config
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT solock@mail.ru)
include(CPack)
