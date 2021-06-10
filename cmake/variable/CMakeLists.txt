cmake_minimum_required(VERSION 3.2)
project(HELLO)
#Declare the variable
set(HELLO_SRCS
   hello.c bye.c)
foreach(item ${HELLO_SRCS})
   message("file: ${item}.")
endforeach()
add_executable(Hello ${HELLO_SRCS})
option(USE_JPEG "Do you want to use JPEG?")
if (NOT ${USE_JPEG})
   message("Yes, jpeg support added")
endif (NOT ${USE_JPEG})

# Command to output information to the console
# Useful for displaying errors, warnings, and debugging
message ("cxx Flags: " ${CMAKE_CXX_FLAGS})
#${PROJECT_SOURCE_DIR} # nearest directory where CMakeLists.txt contains
                      # the project() command
#${PROJECT_BINARY_DIR} # full path to the top level directory of your build tree
#${CMAKE_SOURCE_DIR} # top level source directory
#${CMAKE_BINARY_DIR} # top level directory of your build tree
#${CMAKE_CURRENT_SOURCE_DIR} # directory where the currently processed
                            # CMakeLists.txt is located in
#${CMAKE_CURRENT_BINARY_DIR} # directory where the compiled or generated files
                            # from the current CMakeLists.txt will go to
message("PROJECT_SOURCE_DIR " ${PROJECT_SOURCE_DIR})
message("PROJECT_BINARY_DIR " ${PROJECT_BINARY_DIR})
message("CMAKE_SOURCE_DIR " ${CMAKE_SOURCE_DIR})
message("CMAKE_BINARY_DIR" ${CMAKE_BINARY_DIR})
message("CMAKE_CURRENT_SOURCE_DIR" ${CMAKE_CURRENT_SOURCE_DIR})
message("CMAKE_CURRENT_BINARY_DIR" ${CMAKE_CURRENT_BINARY_DIR})