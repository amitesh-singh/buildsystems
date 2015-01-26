cmake_minimum_required(VERSION 2.8)
project(HELLO)
#Declare the variable
set(HELLO_SRCS
   hello.c bye.c)
foreach(item ${HELLO_SRCS})
   message("file: ${item}.")
endforeach()
add_executable(Hello ${HELLO_SRCS})
