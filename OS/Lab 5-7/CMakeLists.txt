cmake_minimum_required(VERSION 3.10)

project(
	OSLabs_5-7
	LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
	add_subdirectory("Windows")
elseif(UNIX)
	add_subdirectory("Unix")
endif()