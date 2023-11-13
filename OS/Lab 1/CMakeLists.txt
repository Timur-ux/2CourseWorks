cmake_minimum_required(VERSION 3.10)


if(UNIX)
	add_subdirectory(Unix)
elseif(WIN32)
	add_subdirectory(Windows)
endif()