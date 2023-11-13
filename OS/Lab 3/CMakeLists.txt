cmake_minimum_required(VERSION 3.10)

project(
	03_OSLabs
	LANGUAGES CXX C
)

if(UNIX)
	add_subdirectory(Unix)
elseif(WIN32)
	add_subdirectory(Windows)
endif()