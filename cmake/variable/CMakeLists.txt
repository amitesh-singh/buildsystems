cmake_minimum_required(VERSION 2.8)
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
