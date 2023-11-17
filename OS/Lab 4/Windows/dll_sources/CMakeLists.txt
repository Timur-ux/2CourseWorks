cmake_minimum_required(VERSION 3.10)

set(INCLUDE_DIR include)

# LIB_1_DLL

add_library(lib_one SHARED "src/lib1.cpp")
target_include_directories(lib_one PUBLIC ${INCLUDE_DIR})

target_compile_definitions(lib_one 
	PUBLIC LIB1_EXPORTS
)

# LIB_2_DLL

add_library(lib_two SHARED "src/lib2.cpp")
target_include_directories(lib_two PUBLIC ${INCLUDE_DIR})

target_compile_definitions(lib_two 
	PUBLIC LIB2_EXPORTS
)
