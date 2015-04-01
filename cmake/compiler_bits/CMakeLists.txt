cmake_minimum_required(VERSION 3.1)

# check the compiler VERSION
# We are interested to know which type of windows compiler we are using
# 32 bits or 64 bits
# if ${CMAKE_CL_64} is 1, it means 64 bit windows compiler
# cmake -G "Visual Studio 11 2012 Win64" --> ${CMAKE_CL_64} is true
# if ${CMAKE_CL_64} is 0, it means 32 bits windows compiler
# cmake -G "Visual Studio 11 2012" or cmake .
// (~ O'O)~ ^ |__|
message(STATUS "compiler version: ${CMAKE_CL_64}")

if (${CMAKE_CL_64})
	message(STATUS "============================Windows 64 bits compiler")
else()
	message(STATUS "===========================Windows 32 bits compiler")
endif()