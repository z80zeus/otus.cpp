cmake_minimum_required(VERSION 3.2)

# project properties
project(async VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

# config с++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)

find_package(Threads REQUIRED)

configure_file(src/version.h.in version.h)

add_library(libversion OBJECT src/version.cpp)
target_include_directories(libversion PRIVATE "${PROJECT_BINARY_DIR}")

add_library(publisherCommandsFromStream STATIC src/publisherCommandsFromStream.cpp)
add_library(commandStateMachine STATIC src/commandStateMachine.cpp)
add_library(commandStateMachineState STATIC src/commandStateMachineState.cpp)
add_library(commandStateMachineStateIdle STATIC src/commandStateMachineStateIdle.cpp)
add_library(commandStateMachineStateStaticBlock STATIC src/commandStateMachineStateStaticBlock.cpp)
add_library(commandStateMachineStateDynamicBlock STATIC src/commandStateMachineStateDynamicBlock.cpp)
add_library(commandBlockPrinter STATIC src/commandBlockPrinter.cpp)
add_library(commandBlockFiler STATIC src/commandBlockFiler.cpp)
set_target_properties(publisherCommandsFromStream commandStateMachine
        commandStateMachineState
        commandStateMachineStateIdle commandStateMachineStateStaticBlock commandStateMachineStateDynamicBlock
        commandBlockPrinter
        commandBlockFiler
        PROPERTIES
        POSITION_INDEPENDENT_CODE True)
add_library(async SHARED src/libInterface.cpp)
target_link_libraries(async libversion publisherCommandsFromStream commandStateMachine commandStateMachineState
        commandStateMachineStateIdle commandStateMachineStateStaticBlock commandStateMachineStateDynamicBlock
        commandBlockPrinter commandBlockFiler Threads::Threads)

add_executable(bulk main.cpp)
target_include_directories(bulk PRIVATE "${PROJECT_SOURCE_DIR}/src")
target_link_libraries(bulk async)

# Boost test
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

# Test libversion
add_executable(test_libversion test/test_libversion.cpp)
target_link_libraries(test_libversion ${Boost_LIBRARIES} libversion)
set_target_properties(test_libversion PROPERTIES COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR})

add_executable(test_pcfs test/test_publisherCommandsFromStream.cpp)
target_link_libraries(test_pcfs ${Boost_LIBRARIES} publisherCommandsFromStream commandBlockPrinter commandBlockFiler)
set_target_properties(test_pcfs PROPERTIES COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR})

enable_testing()
add_test(test_version test_libversion)
add_test(test_version test_pcfs)

# doxygen
find_package(Doxygen REQUIRED dot)
set(DOXYGEN_PROJECT_BRIEF ${PROJECT_NAME})
set(DOXYGEN_HAVE_DOT YES)
set(DOXYGEN_EXTRACT_ALL YES)
set(DOXYGEN_OUTPUT_DIRECTORY docs)
doxygen_add_docs(doxygen src ALL)

# compiler specific options
#if (MSVC)
#    target_compile_options(bulk PRIVATE /W4)
#    target_compile_options(libversion PRIVATE /W4)
#    target_compile_options(test_libversion PRIVATE /W4)
#else ()
#    target_compile_options(bulk PRIVATE -Wall -Wextra -pedantic -Werror)
#    target_compile_options(libversion PRIVATE -Wall -Wextra -pedantic -Werror)
#    target_compile_options(test_libversion PRIVATE -Wall -Wextra -pedantic -Werror)
#endif()

# which are to install
install(TARGETS bulk RUNTIME DESTINATION bin)
install(TARGETS async RUNTIME DESTINATION lib)

# package config
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT solock@mail.ru)
include(CPack)
