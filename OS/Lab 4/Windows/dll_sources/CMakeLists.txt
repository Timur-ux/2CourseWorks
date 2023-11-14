cmake_minimum_required(VERSION 3.10)

set(INCLUDE_DIR include)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_compile_options(-Wl,-export-all-symbols -Wl,-subsystem,windows)

add_library(${PROJECT_NAME}_dll_one SHARED src/1SinIntegral.cpp)
add_library(${PROJECT_NAME}_dll_two SHARED src/3PrimeCounter.cpp)

target_include_directories(${PROJECT_NAME}_dll_one PUBLIC ${INCLUDE_DIR})
target_include_directories(${PROJECT_NAME}_dll_two PUBLIC ${INCLUDE_DIR})

set_target_properties(${PROJECT_NAME}_dll_one PROPERTIES ARCHIEVE_OUTPUT_NAME ${PROJECT_NAME}_dll_one)
set_target_properties(${PROJECT_NAME}_dll_one PROPERTIES IMPORT_SUFFIX ".lib")
set_target_properties(${PROJECT_NAME}_dll_two PROPERTIES ARCHIEVE_OUTPUT_NAME ${PROJECT_NAME}_dll_two)
set_target_properties(${PROJECT_NAME}_dll_two PROPERTIES IMPORT_SUFFIX ".lib")