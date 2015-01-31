project("config file example")
configure_file(${PROJECT_SOURCE_DIR}/infile
${PROJECT_SOURCE_DIR}/outfile
@ONLY # this means process only @VARIABLES@ and not ${variables}
)