cmake_minimum_required(VERSION 3.2)

# project properties
project(svg.editor VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

# config с++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)

configure_file(src/version.h.in version.h)

# make object files
add_library(version.o OBJECT src/version.h src/version.cpp)
target_include_directories(version.o PRIVATE "${CMAKE_BINARY_DIR}")
add_library(main.o OBJECT main.cpp)
add_library(application.o OBJECT src/application.h src/application.cpp)
#add_library(command.o OBJECT src/command.h)
#add_library(document.o OBJECT src/document.h)
#add_library(drawable.o OBJECT src/drawable.h)
#add_library(event.o OBJECT src/event.h src/event.cpp)
#add_library(menu.o OBJECT src/menu.h src/menu.cpp)
#add_library(svgDataSource.o OBJECT src/svgDataSource.h src/svgDataSource.cpp)
#add_library(svgEntity.o OBJECT src/svgEntity.h)
#add_library(widget.o OBJECT src/widget.h src/widget.cpp)
#add_library(window.o OBJECT src/window.h src/window.cpp)

# objects
#add_library(version.o OBJECT src/version.cpp src/version.h)
#
#add_library(application.o OBJECT src/application.cpp src/application.h)
#target_include_directories(libapplication PRIVATE "${CMAKE_BINARY_DIR}")
#
#add_library(widget.o OBJECT src/widget.cpp src/widget.h)
#target_include_directories(widget.o PRIVATE "${CMAKE_BINARY_DIR}")

# executable destination
add_executable(svg.editor version.o main.o application.o)
target_include_directories(svg.editor PRIVATE "${CMAKE_BINARY_DIR}")
#target_link_libraries(svg.editor PRIVATE version.o main.o application.o)
#        command.o document.o drawable.o event.o menu.o menuItem.o svgDataSource.o
#        svgEntity.o widget.o window.o)

# tests
##find_package(Boost COMPONENTS unit_test_framework REQUIRED)
##
##add_executable(test_libversion test/test_libversion.cpp)
##target_link_libraries(test_libversion ${Boost_LIBRARIES} libversion)
##set_target_properties(test_libversion PROPERTIES COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR})
##
##enable_testing()
##add_test(test_version test_libversion)
##
##
# doxygen
find_package(Doxygen REQUIRED dot)
set(DOXYGEN_PROJECT_BRIEF svg.editor)
set(DOXYGEN_HAVE_DOT YES)
set(DOXYGEN_EXTRACT_ALL YES)
set(DOXYGEN_OUTPUT_DIRECTORY docs)
doxygen_add_docs(doxygen src ALL)

#
## compiler specific options
#if (MSVC)
#    target_compile_options(libversion PRIVATE /W4)
#    target_compile_options(test_libversion PRIVATE /W4)
#else ()
#    target_compile_options(libversion PRIVATE -Wall -Wextra -pedantic -Werror)
#    target_compile_options(test_libversion PRIVATE -Wall -Wextra -pedantic -Werror)
#endif()
#
## which are to install
#install(TARGETS svg.editor RUNTIME DESTINATION bin)
#
## package config
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT solock@mail.ru)
include(CPack)
