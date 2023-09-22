cmake_minimum_required(VERSION 3.10)

project(
    Lab_2
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-g)

set(INCLUDE_DIR ./include)
include_directories(${INCLUDE_DIR})

set(SOURCE_DIR ./src)
set(TEST_DIR ./test)

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES FALSE ${SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES FALSE ${TEST_DIR}/*.cpp)

add_library(main_lib ${SOURCES})

add_executable(main main.cpp)
target_link_libraries(main main_lib)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

enable_testing()
add_executable(main_test ${TEST_SOURCES})
target_link_libraries(main_test ${GTEST_LIBRARIES} main_lib)

add_test(NAME BASIC COMMAND main_tests)