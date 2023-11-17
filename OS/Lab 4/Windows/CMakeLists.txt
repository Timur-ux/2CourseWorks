cmake_minimum_required(VERSION 3.10)

add_subdirectory(dll_sources)

# linked Prog

add_executable(linkedProg linkedProg.cpp)
target_include_directories(linkedProg 
	PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/dll_sources/include"
)

target_link_directories(linkedProg PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/dll_sources/")
target_link_libraries(linkedProg PRIVATE lib_two)

file(COPY_FILE ${CMAKE_CURRENT_BINARY_DIR}/dll_sources/lib_one.dll ${CMAKE_CURRENT_BINARY_DIR}/lib_one.dll)
file(COPY_FILE ${CMAKE_CURRENT_BINARY_DIR}/dll_sources/lib_two.dll ${CMAKE_CURRENT_BINARY_DIR}/lib_two.dll)

# dynamic Prog

add_executable(dynamicProg dynamicProg.cpp)