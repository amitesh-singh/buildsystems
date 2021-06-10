cmake_minimum_required(VERSION 3.20)
project(configexample)
configure_file(${PROJECT_SOURCE_DIR}/infile
${PROJECT_SOURCE_DIR}/outfile
@ONLY # this means process only @VARIABLES@ and not ${variables}
)
