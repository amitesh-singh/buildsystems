cmake_minimum_required(VERSION 3.2)
project("OpenGL Sample Program")
add_executable(gl opengl.cpp)
# link libraries.. 
target_link_libraries(gl -lGL -lglfw -lGLEW)
