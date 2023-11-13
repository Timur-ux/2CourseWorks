cmake_minimum_required(VERSION 3.10)

add_compile_options(-g)

add_executable(${PROJECT_NAME}_main main.cpp)
add_executable(${PROJECT_NAME}_subprogram subprogram.cpp)