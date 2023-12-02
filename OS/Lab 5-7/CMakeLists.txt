cmake_minimum_required(VERSION 3.10)

project(
	OSLabs_5-7
	LANGUAGES CXX
)

if(WIN32)
	add_subdirectory("Windows")
elseif(UNIX)
	add_subdirectory("Unix")
endif()