cmake_minimum_required(VERSION 3.10)

set(INCLUDE_DIR include)
set(SOURCE_DIR src)

include_directories(${INCLUDE_DIR})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES FALSE ${SOURCE_DIR}/*.cpp)


add_executable(director Director_main.cpp)
add_executable(worker Worker_main.cpp)

