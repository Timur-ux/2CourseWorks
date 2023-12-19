cmake_minimum_required(VERSION 3.10)

include_directories("C:\\packages\\include")
link_directories("C:\\packages\\lib")

find_package(ZeroMQ CONFIG REQUIRED)

set(INCLUDE_DIR include)
set(SOURCE_DIR src)

include_directories(${INCLUDE_DIR})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES FALSE ${SOURCE_DIR})


