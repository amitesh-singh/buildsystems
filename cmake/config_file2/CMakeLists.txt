#Getting the project version number into the output
project("config file 2 - Real world example")

set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)

configure_file(${PROJECT_SOURCE_DIR}/config.h.in
${PROJECT_SOURCE_DIR}/config.h
@ONLY 
)