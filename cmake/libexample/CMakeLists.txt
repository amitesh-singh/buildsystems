project("Lib example")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(myprog
	myprog.cpp)
target_link_libraries(myprog 
		mylib)

# add_library(TARGET [STATIC  | SATIC | MODULE ] sources...)
add_library(mylib 
		mylib.h
		mylib.cpp)
