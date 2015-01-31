cmake_minimum_required(VERSION 3.1)
project("Detect Envioronment") #This will make a .sln file in case of visual studio

#detect the system
message(STATUS "We are on a ${CMAKE_SYSTEM_NAME} system.")
if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
	add_definitions(-DSYSTEM_LINUX) #This is our naming
endif()
if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
	add_definitions(-DSYSTEM_WINDOWS) 
endif()

message(STATUS "The host processor is ${CMAKE_HOST_SYSTEM_PROCESSOR}")