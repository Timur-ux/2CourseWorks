cmake_minimum_required(VERSION 3.10)

set(INCLUDE_DIR include)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library(${PROJECT_NAME}_dll_one SHARED src/1SinIntegral.cpp)
add_library(${PROJECT_NAME}_dll_two SHARED src/3PrimeCounter.cpp)

target_include_directories(${PROJECT_NAME}_dll_one PUBLIC ${INCLUDE_DIR})
target_include_directories(${PROJECT_NAME}_dll_two PUBLIC ${INCLUDE_DIR})
