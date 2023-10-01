cmake_minimum_required(VERSION 3.10)

set(INCLUDE_DIR ./include)
include_directories(${INCLUDE_DIR})

set(SOURCE_DIR ./src)

file(GLOB_RECURSE SOURSES ${SOURCE_DIR}/*.cpp)

add_library(Lab2Main_lib ${SOURCES})

add_executable(Lab2Main main.cpp)
target_link_libraries(Lab2Main Lab2Main_lib)