cmake_minimum_required(VERSION 3.10)

project(
	Lab_7
	LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_compile_options(-g)

set(INCLUDE_DIR include)
include_directories(${INCLUDE_DIR})

set(TEST_DIR test)
set(SOURCES_DIR src)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES FALSE ${TEST_DIR}/*.cpp)
file(GLOB_RECURSE SOURCES LIST_DIRECTORIES FALSE ${SOURCES_DIR}/*.cpp)

add_library(${PROJECT_NAME}_lib STATIC ${SOURCES})

add_executable(07_main main.cpp)
target_link_libraries(07_main ${PROJECT_NAME}_lib)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

enable_testing()
add_executable(07_main_test ${TEST_SOURCES})
target_link_libraries(07_main_test ${GTEST_LIBRARIES} ${PROJECT_NAME}_lib)
target_include_directories(07_main_test PUBLIC ${INCLUDE_DIR})

add_test(NAME BASIC COMMAND 07_main_tests)
