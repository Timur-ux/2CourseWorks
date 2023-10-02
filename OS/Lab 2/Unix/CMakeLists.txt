cmake_minimum_required(VERSION 3.10)

set(INCLUDE_DIR ./include)
include_directories(${INCLUDE_DIR})

set(SOURCE_DIR ./src)

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES FALSE ${SOURCE_DIR}/*.cpp)

add_library(Lab2Main_lib ${SOURCES})

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(Lab2Main main.cpp)
target_link_libraries(Lab2Main Lab2Main_lib Threads::Threads)