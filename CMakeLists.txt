cmake_minimum_required(VERSION 3.2)

project(ip_filter VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

configure_file(lib/version.h.in version.h)

add_library(libversion lib/libversion.cpp)
add_library(libIpAddr lib/libIpAddr.cpp)

add_executable(ip_filter main.cpp)
#add_executable(test_libversion test/test_libversion.cpp)
#add_executable(test_libIpAddr test/test_libIpAddr.cpp)

#set_target_properties(ip_filter libversion libIpAddr test_libversion test_libIpAddr PROPERTIES
set_target_properties(ip_filter libversion libIpAddr PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(ip_filter
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_include_directories(libversion
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_include_directories(libIpAddr
    PRIVATE "${CMAKE_BINARY_DIR}"
)

#set_target_properties(test_libversion PROPERTIES
#    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
#    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
#)

target_link_libraries(ip_filter PRIVATE
    libversion
    libIpAddr
)

#target_link_libraries(test_libversion
#    ${Boost_LIBRARIES}
#    libversion
#)

#target_link_libraries(test_libIpAddr
#    ${Boost_LIBRARIES}
#    libIpAddr
#)

if (MSVC)
    target_compile_options(ip_filter PRIVATE
        /W4
    )
    target_compile_options(libversion PRIVATE
        /W4
    )
    target_compile_options(libIpAddr PRIVATE
        /W4
    )

#    target_compile_options(test_libversion PRIVATE
#        /W4
#    )
#    target_compile_options(test_libIpAddr PRIVATE
#        /W4
#    )
else ()
    target_compile_options(ip_filter PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(libversion PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(libIpAddr PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
#    target_compile_options(test_libIpAddr PRIVATE
#        -Wall -Wextra -pedantic -Werror
#    )
#    target_compile_options(test_libversion PRIVATE
#        -Wall -Wextra -pedantic -Werror
#    )

endif()

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT solock@mail.ru)

include(CPack)

set(CMAKE_BUILD_TYPE Debug)

#enable_testing()
#add_test(test_version test_libversion)
#add_test(test_ipAddr test_libIpAddr)
