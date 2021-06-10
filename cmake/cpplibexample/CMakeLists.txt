cmake_minimum_required(VERSION 3.20)

project(cpplib)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/lib/)
add_executable(test main.cpp)
target_link_libraries(test mylib)
add_subdirectory(lib)
