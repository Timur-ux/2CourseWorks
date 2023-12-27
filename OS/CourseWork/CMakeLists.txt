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

file(GLOB_RECURSE MESSAGES_SRC LIST_DIRECTORIES FALSE ${SOURCE_DIR}/Messages/*.cpp)
file(GLOB_RECURSE NETWORK_SRC LIST_DIRECTORIES FALSE ${SOURCE_DIR}/Network/*.cpp)
file(GLOB UTILS_SRC LIST_DIRECTORIES FALSE ${SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE GAME_SRC LIST_DIRECTORIES FALSE ${SOURCE_DIR}/Game/*.cpp)

foreach(ITEM ${NETWORK_SRC})
	message(${ITEM}"\n")
endforeach()

add_library(utils_lib STATIC ${UTILS_SRC})
add_library(game_lib STATIC ${GAME_SRC})
add_library(network_lib STATIC ${NETWORK_SRC})

add_executable(GameHub GameHub.cpp)
target_link_libraries(GameHub 
	PUBLIC network_lib 
	PUBLIC utils_lib
)

add_executable(Game Game.cpp)
target_link_libraries(Game
	PUBLIC network_lib 
	PUBLIC game_lib 
	PUBLIC utils_lib
)

add_executable(GameClient GameClient.cpp)
target_link_libraries ( GameClient
	PUBLIC network_lib
	PUBLIC game_lib
	PUBLIC utils_lib
)

