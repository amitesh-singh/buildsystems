project("desktop gl")

cmake_minimum_required(VERSION 2.8)

if (MSVC)
    message(STATUS "Microsoft compiler found..")
endif()

if (MSVC)
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../dev/glew-1.11.0/include
				        ${CMAKE_CURRENT_SOURCE_DIR}/../dev/glfw-3.0.4.bin.WIN64/include
				        ${CMAKE_CURRENT_SOURCE_DIR}/../dev/glm
				        ${CMAKE_CURRENT_SOURCE_DIR}/../dev/SOIL/src)
    link_directories(
				    ${CMAKE_CURRENT_SOURCE_DIR}/../dev/glew-1.11.0/lib/Release/x64
				    ${CMAKE_CURRENT_SOURCE_DIR}/../dev/glfw-3.0.4.bin.WIN64/lib-msvc120
				    ${CMAKE_CURRENT_SOURCE_DIR}/../dev/SOIL/projects/VC9/x64/Debug)
endif()
set(glsubdir  
    basic
    triangle
    trianglestrip
    multipleVbos
    multiplevaos
    movetriangle
    animtriangle)

#set(glsubdir ${glsubdir} PARENT_SCOPE)
foreach(gldir ${glsubdir})
	add_subdirectory(${gldir})
endforeach()
