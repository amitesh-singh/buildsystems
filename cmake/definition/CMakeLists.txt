cmake_minimum_required(VERSION 2.8)
project("add definitions")
add_executable(def def.c)
# add compile options like gcc -std=c99 ....
target_compile_options(def PRIVATE -std=c99)
# link libraries.. lets link pthread?
target_link_
