cmake_minimum_required(VERSION 3.10)

add_subdirectory(dll_sources)

add_executable(${PROJECT_NAME}_linkedProg linkedProg.cpp)
target_link_libraries(${PROJECT_NAME}_linkedProg
						dll_sources/${PROJECT_NAME}_dll_one
						dll_sources/${PROJECT_NAME}_dll_two
)


add_executable(${PROJECT_NAME}_dynamicProg dynamicProg.cpp)