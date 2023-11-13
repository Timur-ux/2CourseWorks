cmake_minimum_required(VERSION 3.10)

if(EXISTS "OS")
	add_subdirectory(OS)
endif()

if(EXISTS "OOP")
	add_subdirectory(OOP)
endif()

if(EXISTS "FuncAndLogProg")
	add_subdirectory(FuncAndLogProg)
endif()