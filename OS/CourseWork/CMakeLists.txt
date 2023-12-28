cmake_minimum_required(VERSION 3.10)

project(
	bullsAndCows
	LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PACKAGES_INCLUDE_DIR "C:/Program Files (x86)/vcpkg/installed/x64-windows/include")
set(PACKAGES_LIB_DIR "C:/Program Files (x86)/vcpkg/installed/x64-windows/lib")
include_directories(${PACKAGES_INCLUDE_DIR})
link_directories(${PACKAGES_LIB_DIR})

find_package(ZeroMQ CONFIG REQUIRED)
include_directories(${ZeroMQ_INCLUDE_DIR})

set(INCLUDE_DIR "./include")
set(SOURCE_DIR "./src")

include_directories(${INCLUDE_DIR})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES FALSE ${SOURCE_DIR}/*.cpp)

add_library(main_lib STATIC ${SOURCES})
target_include_directories(main_lib PUBLIC ${PACKAGES_INCLUDE_DIR})
target_link_directories(main_lib PUBLIC ${PACKAGES_LIB_DIR})

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

