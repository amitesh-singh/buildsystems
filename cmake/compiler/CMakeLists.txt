#
# MSVC, MSVC_IDE, MSVC60, MSVC70, MSVC71, MSVC80, CMAKE_COMPILER_2005, MSVC90, MSVC10 (Visual Studio 2010) 
#Microsoft compiler
#CMAKE_C_COMPILER_ID 
#one of "Clang", "GNU", "Intel", or "MSVC". This works even if a compiler wrapper like ccache is used.
#CMAKE_CXX_COMPILER_ID 
#one of "Clang", "GNU", "Intel", or "MSVC". This works even if a compiler wrapper like ccache is used.
#CMAKE_COMPILER_IS_GNUCC 
#+
#is TRUE if the compiler is a variant of gcc
#CMAKE_COMPILER_IS_GNUCXX 
# is TRUE if the compiler is a variant of g++
#
#
cmake_minimum_required(VERSION 3.1)
project("compiler finder")

if (UNIX)
	set(CMAKE_VERBOSE_MAKEFILE true)
endif()
if (NOT UNIX)
	message(STATUS "CMAKE_VERBOSE_MAKEFILE = ${CMAKE_VERBOSE_MAKEFILE}")
endif()

