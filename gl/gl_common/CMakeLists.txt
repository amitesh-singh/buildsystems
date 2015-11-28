project("GL common")
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

set(SRC
   Shader.h
   Shader.cpp
)
add_library(glCommon SHARED
${SRC})

target_link_libraries(glCommon -lGLEW)

#add_subdirectory(test)
