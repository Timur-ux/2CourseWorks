cmake_minimum_required(VERSION 3.10)

project(
    Lab_1
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-g)

set(INCLUDE_DIR ./include)
include_directories(${INCLUDE_DIR})

set(SOURCE_DIR ./src)
set(TEST_DIR ./test)

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES FALSE ${SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES FALSE ${TEST_DIR}/*.cpp)

add_library(Lab1main_lib ${SOURCES})

add_executable(Lab1main main.cpp)
target_link_libraries(Lab1main Lab1main_lib)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

enable_testing()
add_executable(Lab1main_test ${TEST_SOURCES})
target_link_libraries(Lab1main_test ${GTEST_LIBRARIES} Lab1main_lib)

add_test(NAME BASIC COMMAND Lab1main_tests)