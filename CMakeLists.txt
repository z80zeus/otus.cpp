cmake_minimum_required(VERSION 3.2)

project(allocator VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

configure_file(lib/version.h.in version.h)

add_library(libversion lib/libversion.cpp)

add_executable(allocator main.cpp)
add_executable(test_libversion test/test_libversion.cpp)
add_executable(test_allocator test/test_allocator.cpp)
add_executable(test_container test/test_container.cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

target_include_directories(allocator
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_include_directories(libversion
    PRIVATE "${CMAKE_BINARY_DIR}"
)

set_target_properties(test_libversion PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

set_target_properties(test_allocator PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

set_target_properties(test_container PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(allocator PRIVATE
    libversion
)

target_link_libraries(test_libversion
    ${Boost_LIBRARIES}
    libversion
)

target_link_libraries(test_allocator
    ${Boost_LIBRARIES}
)

target_link_libraries(test_container
    ${Boost_LIBRARIES}
)

if (MSVC)
    target_compile_options(allocator PRIVATE
        /W4
    )
    target_compile_options(libversion PRIVATE
        /W4
    )
    target_compile_options(test_libversion PRIVATE
        /W4
    )
    target_compile_options(test_allocator PRIVATE
        /W4
    )
    target_compile_options(test_container PRIVATE
        /W4
    )
else ()
    target_compile_options(allocator PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(libversion PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(test_libversion PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(test_allocator PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(test_container PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS allocator RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT solock@mail.ru)

include(CPack)

set(CMAKE_BUILD_TYPE Debug)

enable_testing()
add_test(test_version test_libversion)
add_test(test_allocator test_allocator)
add_test(test_container test_container)
