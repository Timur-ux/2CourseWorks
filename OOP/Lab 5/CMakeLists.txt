cmake_minimum_required(VERSION 3.10)

project(
    Lab_5
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-g)

set(INCLUDE_DIR include)
include_directories(${INCLUDE_DIR})

set(TEST_DIR test)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES FALSE ${TEST_DIR}/*.cpp)

add_executable(05_main main.cpp)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

enable_testing()
add_executable(05_main_test ${TEST_SOURCES})
target_link_libraries(05_main_test ${GTEST_LIBRARIES})

add_test(NAME BASIC COMMAND 05_main_tests)