cmake_minimum_required(VERSION 3.20)
project("install")

add_executable(myapp myapp.c)
# Install binary
install(TARGETS myapp DESTINATION bin)
#Install libs
#install(TARGETS mylib_static DESTINATION lib)
#install(TARGETS mylib_shared DESTINATION lib)
#Install header files
#install(FILES ${PROJECT_SOURCE_DIR/src/mylib.h} DESTINATION include)

#$ mkdir build
#$ cd build
#$ cmake -DCMAKE_INSTALL_PREFIX=/home/user/example ..
#$ make
#$ make install