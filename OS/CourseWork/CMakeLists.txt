cmake_minimum_required(VERSION 3.10)

project(
	bullsAndCows
	LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories("C:\\Program Files (x86)\\vcpkg\\installed\\x64-windows\\include")
link_directories("C:\\Program Files (x86)\\vcpkg\\installed\\x64-windows\\lib")

find_package(ZeroMQ CONFIG REQUIRED)
include_directories(${ZeroMQ_INCLUDE_DIR})

set(INCLUDE_DIR "include")
set(SOURCE_DIR "src")

include_directories(${INCLUDE_DIR})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES FALSE ${SOURCE_DIR}/*.cpp)

foreach(ITEM ${SOURCES}) 
	message(${ITEM}"\n")
endforeach()

add_library(main_lib STATIC ${SOURCES})

add_executable(GameHub GameHub.cpp)
target_link_libraries(GameHub 
	PUBLIC main_lib
	PRIVATE libzmq libzmq-static
)

add_executable(Game Game.cpp)
target_link_libraries(Game
	PUBLIC main_lib
	PRIVATE libzmq libzmq-static
)

add_executable(GameClient GameClient.cpp)
target_link_libraries ( GameClient
	PUBLIC main_lib
	PRIVATE libzmq libzmq-static
)

