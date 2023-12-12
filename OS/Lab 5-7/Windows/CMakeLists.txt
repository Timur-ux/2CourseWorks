cmake_minimum_required(VERSION 3.10)

set(INCLUDE_DIR include)
set(SOURCE_DIR src)

include_directories(${INCLUDE_DIR})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES FALSE ${SOURCE_DIR}/*.cpp)

find_package(cppzmq CONFIG REQUIRED)

add_library(sources_lib STATIC ${SOURCES})
target_link_libraries(sources_lib PRIVATE cppzmq)

add_executable(ControlCenter "ControlCenter.cpp")
add_executable(CalculatingCenter "CalculatingCenter.cpp" src/Client.cpp)

target_link_libraries(ControlCenter PUBLIC sources_lib PRIVATE cppzmq)
target_link_libraries(CalculatingCenter PRIVATE cppzmq)