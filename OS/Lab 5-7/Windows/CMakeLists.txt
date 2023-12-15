cmake_minimum_required(VERSION 3.10)

set(INCLUDE_DIR include)
set(SOURCE_DIR src)

include_directories(${INCLUDE_DIR})
include_directories("C:/Program Files/boost/boost_1_82_0/")

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES FALSE ${SOURCE_DIR}/*.cpp)


include_directories("C:/Program Files(x86)/vcpkg/installed/x64-windows/include")
link_directories("C:/Program Files(x86)/vcpkg/installed/x64-windows/lib")

find_package(cppzmq CONFIG REQUIRED)

add_library(sources_lib STATIC ${SOURCES})
target_link_libraries(sources_lib PRIVATE cppzmq)

add_executable(ControlCenter "ControlCenter.cpp")
add_executable(CalculatingCenter "CalculatingCenter.cpp" src/Client.cpp)

target_link_libraries(ControlCenter PUBLIC sources_lib PRIVATE cppzmq)
target_link_libraries(CalculatingCenter PRIVATE libzmq cppzmq)