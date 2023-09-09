cmake_minimum_required(VERSION 3.10)

project(Lab_1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(main main.cpp brackets_check.cpp)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

enable_testing()
add_executable(main_tests main_tests.cpp brackets_check.cpp)
target_link_libraries(main_tests ${GTEST_LIBRARIES})

add_test(NAME BASIC COMMAND main_tests)