project("lib example 2")

add_executable(myprog myprog.c)
target_link_libraries(myprog mylib)
add_subdirectory(mylib)